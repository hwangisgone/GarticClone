#include <iostream>

#include "server_lobby.hpp"
#include "room_handler.hpp"

#include <msg/msg_format.hpp>
#include <msg/msg_sendrecv.h>

#include <auth/server_auth.hpp>
#include <debug/debugging.h>

using namespace std;

bool ServerLobby::joinRoom(PlayerSession& client, JoinRoomMsg& joinmsg) {
	auto it = this->allRooms.find(joinmsg.roomID);
	if (it != this->allRooms.end()) {
		// Room exists, access the value
		joinmsg.addr = client.addr;
		joinmsg.account = &client.account;
		client.inRoom = it->second;

		return true;
	} else {
		DEBUG_PRINT("Room doesn't exist");
		return false;
	}
}

void ServerLobby::createRoom(PlayerSession& creator) {
	// Room count as roomID
	auto result = this->allRooms.emplace(this->roomCount, new RoomHandler(this->sockfd));
	if (result.second) {
		DEBUG_PRINT("Lobby: Created room " + to_string(result.first->first) + " successfully!");
		RoomHandler * newRoom = result.first->second;

		creator.inRoom = newRoom;
		newRoom->addPlayer(creator.account.playerID, creator.addr, creator.account);	// Add host to room 
		this->roomCount++;
	} else {
		DEBUG_PRINT("Lobby: Create room failed for some reason???");
	}	
}

void ServerLobby::LobbyHandle(MsgWrapper& wrapper, const sockaddr_in& clientAddress) {
	BaseMsg& msg = *wrapper.msg;

	auto it = sessionRoomMap.find(clientAddress);
	if (it == sessionRoomMap.end()) {
		// No such session exist yet
		if (msg.type() == MsgType::AUTH) {
			// Only process AUTH, any other unauthorized session will be dismissed
			PlayerAccount * loggedacc = authenticate(static_cast<AuthMsg&>(msg));
			if (loggedacc != nullptr) {
				// If auth success
				this->addSession(clientAddress, *loggedacc);

				// Send success msg first
				AuthMsg successmsg;
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);

				// Send all room present
				for (const auto& pair : this->allRooms) {
					RoomListMsg msg;
					msg.roomID = pair.first;
					strncpy(msg.roomName, pair.second->roomName, 50);
					
					sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), msg);
				}
			} else {
				// auth fail
				DEBUG_PRINT("Incorrect credentials");
				FailMsg failmsg;
				sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), failmsg);
			}
		} else {
			DEBUG_PRINT("Dismissing message (not registered session)");
		}
	} else {
		PlayerSession& currentClient = it->second;
		wrapper.playerID = currentClient.account.playerID;

		if (currentClient.inRoom == nullptr) {
			// In lobby
			switch (msg.type()) {
				case MsgType::CREATE_ROOM: {
					createRoom(currentClient);
					break;
				}
				case MsgType::JOIN_ROOM: {
					if (joinRoom(currentClient, static_cast<JoinRoomMsg&>(msg))) {
						JoinRoomMsg successmsg;
						sendMsg(this->sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress), successmsg);

						currentClient.inRoom->msgQueue.push(wrapper);	
						// Also push this new thing to room	if joined success
					}
					break;
				}
				default:
					break;
			}	
		} else {
			// In room/game
			currentClient.inRoom->msgQueue.push(wrapper);
		}
	}
}

void ServerLobby::run() {
	// TODO: May consider moving this to somewhere defined once
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

	// Create new
	// allRooms.push_back(new RoomHandler(this->sockfd));
	// RoomHandler * theOnlyOneRoom = allRooms.back();

	// PlayerAccount oneAccount;
	// oneAccount.playerID = 1;

	MsgWrapper oneWrapper;
	int timeout_counter = 0;
				// currentClient.account = &oneAccount;
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
		DEBUG_PRINT("Lobby: Joined successful!");
	} else {
		DEBUG_PRINT("(Address mapped)");
	}
}


void ServerLobby::removeSession(const sockaddr_in& addr) {
	// If exist, will skip
	auto result = sessionRoomMap.erase(addr);
	// Check if the removal was successful
	if (result == 1) {
		DEBUG_PRINT("Lobby: Remove successful!");
	} else {
		DEBUG_PRINT("Lobby: Remove player failed. Address not found.");
	}
}