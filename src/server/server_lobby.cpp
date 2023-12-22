#include <iostream>

#include "server_lobby.hpp"

// TODO: Temp:
#include "states/lobby/msg_lobby.hpp"

#include "room_handler.hpp"
#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"
#include "debugging.h"

using namespace std;

void ServerLobby::LobbyHandle(PlayerSession& currentClient, BaseMsg& msg) {
	DEBUG_PRINT("  (Lobby) " + msg.toString());

	switch (msg.type()) {
		case MsgType::AUTH: 
			// currentClient.account = &oneAccount;
			// authorize();
			break;
		case MsgType::JOIN_ROOM:
			{
				int joiningRoom = static_cast<JoinRoomMsg&>(msg).roomID;

				auto it = allRooms.find(joiningRoom);
			    if (it != allRooms.end()) {
			        // Key exists, access the value
			        currentClient.inRoom = it->second;
			        // TODO: broadcast, conenct it to room???
			    } else {
			    	DEBUG_PRINT("Room doesn't exist");
			    }
				break;
			}
		case MsgType::CREATE_ROOM:
			{	// Room count as roomID
				auto result = this->allRooms.emplace(this->roomCount, new RoomHandler(this->sockfd));
				if (result.second) {
					DEBUG_PRINT("Lobby: Joined successful!");
					RoomHandler * newRoom = result.first->second;
					currentClient.inRoom = newRoom;
					newRoom->host = currentClient.account->playerID;	// Add host to room 
					this->roomCount++;
				} else {
					DEBUG_PRINT("Lobby: Create room failed for some reason???");
				}
				break;
			}
		default:
			break;
	}
}

void ServerLobby::run() {
	// TODO: May consider moving this to somewhere defined once
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

	// Create new
	// allRooms.push_back(new RoomHandler(this->sockfd));
	// RoomHandler * theOnlyOneRoom = allRooms.back();

	PlayerAccount oneAccount;
	oneAccount.playerID = 1;

	int timeout_counter = 0;
				// currentClient.account = &oneAccount;
	while(keepAlive) {
		// - wait for client to connect
		MsgWrapper oneWrapper;
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

		if (testMsg->type() == MsgType::JOIN_ROOM) {
			static_cast<JoinRoomMsg&>(*testMsg).addr = clientAddress;	// Add a field not normally included in payload
		}
		oneWrapper.msg = std::move(testMsg);

		addSession(clientAddress);
		PlayerSession& currentClient = sessionRoomMap.at(clientAddress);

		if (currentClient.inRoom != nullptr) { 
			// Only push to room if is in room
			oneWrapper.playerID = currentClient.account->playerID;
			currentClient.inRoom->msgQueue.push(oneWrapper);
		} else {
			// Else handle with lobby state
			LobbyHandle(currentClient, *oneWrapper.msg);
		}
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
void ServerLobby::addSession(const sockaddr_in& addr) {
	PlayerSession newSession;

	// If exist, will skip
	auto result = sessionRoomMap.emplace(addr, newSession);
	if (result.second) {
		std::cout << "Lobby: Joined successful!" << std::endl;
	} else {
		std::cout << "(Address mapped)" << std::endl;
	}
}


void ServerLobby::removeSession(const sockaddr_in& addr) {
	// If exist, will skip
	auto result = sessionRoomMap.erase(addr);
	// Check if the removal was successful
	if (result == 1) {
		std::cout << "Lobby: Remove successful!" << std::endl;
	} else {
		std::cout << "Lobby: Remove player failed. Address not found." << std::endl;
	}
}