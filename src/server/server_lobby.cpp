#include <iostream>

#include "server_lobby.hpp"

// TODO: Temp:
#include "states/lobby/msg_lobby.hpp"

#include "room_handler.hpp"
#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"
#include "debugging.h"

using namespace std;

void ServerLobby::run() {
	// TODO: May consider moving this to somewhere defined once
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

	// Create new
	allRooms.push_back(new RoomHandler(sockfd));
	RoomHandler * theOnlyOneRoom = allRooms.back();

	PlayerAccount oneAccount;
	oneAccount.playerID = 1;

	// while(keepAlive) {
		// - wait for client to connect
		MsgWrapper oneWrapper;
		unique_ptr<BaseMsg> testMsg;
		
		testMsg = recvMsg(sockfd, (struct sockaddr*)&clientAddress, &clientAddrLen);
		if (!testMsg) {	// nullptr
			cerr << "SERVER: Error receiving data" << endl;
			return;
		}
		if (testMsg->type() == MsgType::JOIN_ROOM) {
			static_cast<JoinRoomMsg&>(*testMsg).addr = clientAddress;	// Add a field not normally included in payload
		}
		oneWrapper.msg = std::move(testMsg);

		addSession(clientAddress);
		PlayerSession& currentClient = sessionRoomMap.at(clientAddress);
		if (currentClient.inRoom == nullptr) {
			currentClient.account = &oneAccount;
			currentClient.inRoom = theOnlyOneRoom;
		}

		oneWrapper.playerID = currentClient.account->playerID;
		currentClient.inRoom->msgQueue.push(oneWrapper);
	// }
		oneWrapper.msg = factoryProduceMsg(MsgType::DISCONNECT);
		currentClient.inRoom->msgQueue.push(oneWrapper);

	// Only delete if stopped
	for (RoomHandler* ptr : allRooms) {
		delete ptr;
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
		std::cout << "Lobby: Joined failed. Address already exists." << std::endl;
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