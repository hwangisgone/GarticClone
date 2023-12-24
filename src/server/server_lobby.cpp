#include <iostream>

#include "server_lobby.hpp"

// TODO: Temp:
#include "states/lobby/msg_lobby.hpp"

#include "room_handler.hpp"
#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"
#include "debugging.h"

using namespace std;

void ServerLobby::createRoom(PlayerSession& creator, const sockaddr_in& addr) {
	// Room count as roomID
	auto result = this->allRooms.emplace(this->roomCount, new RoomHandler(this->sockfd));
	if (result.second) {
		DEBUG_PRINT("Lobby: Created room " + to_string(result.first->first) + " successfully!");
		RoomHandler * newRoom = result.first->second;

		creator.inRoom = newRoom;
		newRoom->addPlayer(creator.account->playerID, creator.account->playerName, addr);	// Add host to room 
		this->roomCount++;
	} else {
		DEBUG_PRINT("Lobby: Create room failed for some reason???");
	}	
}

void ServerLobby::LobbyHandle(MsgWrapper& wrapper, sockaddr_in& clientAddress) {
	BaseMsg& msg = *wrapper.msg;

	auto it = sessionRoomMap.find(clientAddress);
	if (it == sessionRoomMap.end()) {
		// No such session exist yet
		if (msg.type() == MsgType::AUTH) {
			// Only process AUTH, any other unauthorized session will be dismissed
			authorize(); // addSession(clientAddress); currentClient.account
			//  = sessionRoomMap.at(clientAddress);
		} else {
			PRINT_ERROR("Dismissing message (not registered session)");
		}
	} else {
		PlayerSession& currentClient = it->second;
		oneWrapper.playerID = currentClient.account->playerID;

		if (currentClient.inRoom == nullptr) {
			// In lobby

		} else {
			// In room/game
			currentClient.inRoom->msgQueue.push(oneWrapper);
		}
	}


	BaseMsg& msg = *wrapper.msg;


	switch (msg.type()) {
		case MsgType::AUTH: 
			// currentClient.account = &oneAccount;
			// authorize();
			break;
		case MsgType::JOIN_ROOM:
		{
			JoinRoomMsg& joinmsg = static_cast<JoinRoomMsg&>(msg);
			joinmsg.addr = clientAddress;

			auto it = this->allRooms.find(joinmsg.roomID);
			if (it != this->allRooms.end()) {
				// Room exists, access the value
				currentClient.inRoom = it->second;
				joinmsg.addr = clientAddress;
				joinmsg.name = currentClient.account->name;

				currentClient.inRoom->msgQueue.push(wrapper);	// Also push this new thing to room
			} else {
				DEBUG_PRINT("Room doesn't exist");
			}
			break;
		}
		case MsgType::CREATE_ROOM:
		{
			createRoom(currentClient, clientAddress);
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