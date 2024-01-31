#include <iostream>

#include "server_lobby.hpp"
#include "room_handler.hpp"

#include <msg/msg_format.hpp>
#include <msg/msg_sendrecv.h>


#include <auth/server_auth.hpp>
#include <lobby/msg/msg_lobby.hpp>
#include <room/msg/msg_connection.hpp>
#include <timer/timer_thread.hpp>

#include <printdebug/debugging.h>

using namespace std;

bool ServerLobby::joinRoom(PlayerSession& client, BaseMsg& msg) {
	JoinRoomMsg& joinmsg = static_cast<JoinRoomMsg&>(msg);
	auto it = this->allRooms.find(joinmsg.roomID);
	if (it != this->allRooms.end()) {
		// Room exists, access the value
		joinmsg.addr = client.addr;
		joinmsg.account = &client.account;
		client.inRoom = it->second;

		return true;
	} else {
		TEST_PRINT("> Lobby: Room doesn't exist");
		return false;
	}
}

bool ServerLobby::createRoom(PlayerSession& creator, const char * in_roomName) {
	// Room count as roomID
	auto result = this->allRooms.emplace(this->roomCount, new RoomHandler(this->sockfd));
	if (result.second) {
		TEST_PRINT("> Lobby: Created room #" + to_string(result.first->first) + " successfully!");
		RoomHandler * newRoom = result.first->second;

		newRoom->roomID = this->roomCount;
		strncpy(newRoom->roomName, in_roomName, 50);

		// creator.inRoom = newRoom;
		// newRoom->addPlayer(creator.account.playerID, creator.addr, creator.account);	// Add host to room 

		this->roomCount++;
		return true;
	} else {
		DEBUG_PRINT("> Lobby: Create room failed for some reason???");
		return false;
	}	
}


void ServerLobby::LobbyHandle(MsgWrapper& wrapper, const sockaddr_in& clientAddress) {
	BaseMsg& msg = *wrapper.msg;

	auto it = sessionRoomMap.find(clientAddress);
	if (it == sessionRoomMap.end()) {
		// No such session exist yet
		if (msg.type() == MsgType::LOGIN) {
			PlayerAccount * loggedacc = authenticate(static_cast<const LoginMsg&>(msg));
			if (loggedacc != nullptr) {
				// If auth success
				this->addSession(clientAddress, *loggedacc);

				// Send success msg first
				AccountInfoMsg accmsg;
				accmsg.playerID = loggedacc->playerID;
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), accmsg);
			} else {
				// TEST_PRINT("Incorrect credentials");
				FailMsg failmsg(MsgType::LOGIN);
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), failmsg);
			}
		} else if (msg.type() == MsgType::REGISTER) {
			int playerID = registeraccount(static_cast<const RegisterMsg&>(msg));
			if (playerID > 0) {
				SuccessMsg successmsg(MsgType::REGISTER);
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);
			} else {
				FailMsg failmsg(MsgType::REGISTER);
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), failmsg);
			}
		} else {
			TEST_PRINT("Dismissing message (not registered session)");
		}
	} else {
		if (msg.type() == MsgType::LOGIN || msg.type() == MsgType::REGISTER) {
			TEST_PRINT("> Already logged in.");
			return;
		} else if (msg.type() == MsgType::LOGOUT) {
			TEST_PRINT("> Logging out...");
			this->removeSession(clientAddress);

			SuccessMsg successmsg(MsgType::LOGOUT);
			sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);
			
			return;
		}

		PlayerSession& currentClient = it->second;
		wrapper.playerID = currentClient.account.playerID;

		if (currentClient.inRoom == nullptr) {
			// In lobby
			switch (msg.type()) {
				case MsgType::GET_ROOMS: {
					// Send all room present
					for (const auto& pair : this->allRooms) {
						RoomListMsg msg;
						msg.roomID = pair.first;
						strncpy(msg.roomName, pair.second->roomName, 50);
						
						TEST_PRINT(">> RoomList | " + to_string(msg.roomID) + " | " + string(msg.roomName));
						sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), msg);
					}
					TEST_PRINT("> Lobby: Sent room list to #" + to_string(wrapper.playerID));
					break;
				}
				case MsgType::CREATE_ROOM: {
					if (createRoom(currentClient, static_cast<CreateRoomMsg&>(msg).roomName) ) {
						SuccessMsg successmsg(MsgType::CREATE_ROOM);
						sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);


						// PlayerConnectMsg thisplayermsg;
						// thisplayermsg.playerID = currentClient.account.playerID;
						// strncpy(thisplayermsg.name, currentClient.account.playerName, 50);
						// sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), thisplayermsg);
					}
					break;
				}
				case MsgType::JOIN_ROOM: {
					DEBUG_PRINT("Joining room through lobby");
					if (joinRoom(currentClient, msg)) {
						SuccessMsg successmsg(MsgType::JOIN_ROOM);
						sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);

						// currentClient.inRoom->msgQueue.push(wrapper);	
						// Also push this new thing to room	if joined success
					}
					break;
				}
				default:
					break;
			}	
		} else {
			switch(msg.type()) {
				case MsgType::DISCONNECT: {
					currentClient.inRoom->msgQueue.push(wrapper);
					currentClient.inRoom = nullptr;
					return;
				}
				case MsgType::JOIN_ROOM: {
					if (!joinRoom(currentClient, msg)) {
						TEST_PRINT("> Lobby: Aready in room! This shouldn't happen.");
						return;
					}
					// activate with defaualt
				}
				default:
					// In room/game
					currentClient.inRoom->msgQueue.push(wrapper);
					break;
			}
		}
	}
}

void ServerLobby::run() {
	// TODO: May consider moving this to somewhere defined once
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

	// INITIALIZATIONGS
	loadFromFile("txt/accounts.txt", allAccounts);
	WordHandler::loadFromFile("txt/word.txt", WordHandler::wordsGlobal);
	// DATABASE

	// HAVE A TIMER THREAD
	TimerThread lobbyTimer(&allRooms);
	// RUN UNTIL ServerLobby::run() ends;

	MsgWrapper oneWrapper;
	int timeout_counter = 0;

	while(keepAlive) {
		// - wait for client to connect
		unique_ptr<BaseMsg> testMsg;
		
		testMsg = recvMsg(sockfd, (struct sockaddr*)&clientAddress, &clientAddrLen);
		if (!testMsg) {	// nullptr
			if (errno && EAGAIN || errno && EWOULDBLOCK) {
				DEBUG_COUT("SERVER RECV TIMEOUT (" + to_string(timeout_counter) + ")\033[1A");
				timeout_counter++;
				continue;
			} else {
				DEBUG_PRINT("SERVER: Error receiving data.");
				return;
			}
		}

		oneWrapper.msg = std::move(testMsg);
		LobbyHandle(oneWrapper, clientAddress);
	}

	// Only delete if stopped
	for (const auto& pair : allRooms) {
		delete pair.second;
	}

	DEBUG_PRINT("Finish?");
}

void ServerLobby::kill() {
	keepAlive = false;
}

// Adding entries to online joined
void ServerLobby::addSession(const sockaddr_in& addr, const PlayerAccount& account) {
	PlayerSession newSession(addr, account);

	DEBUG_PRINT("Assigned address, account to new session");

	// If exist, will skip
	auto result = sessionRoomMap.emplace(addr, newSession);
	if (result.second) {
		TEST_PRINT("> Lobby: Joined successful!");
	} else {
		TEST_PRINT("(Address mapped)");
	}
}


void ServerLobby::removeSession(const sockaddr_in& addr) {
	// If exist, will skip
	auto result = sessionRoomMap.erase(addr);
	// Check if the removal was successful
	if (result == 1) {
		DEBUG_PRINT("> Lobby: Remove successful!");
	} else {
		DEBUG_PRINT("> Lobby: Remove player failed. Address not found.");
	}
}