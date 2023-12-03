void broadCaster(sockaddr_in clientAddr, AppMsg * msg) {
	ssize_t clientAddrLen = sizeof(clientAddr);

	for (const auto& client : clients) {
		// Except the current one
		if (compareAddresses(client, clientAddr)) { break; }

		if (sendMsg(serverSocket, (struct sockaddr*)&client, &clientAddrLen) == -1) {
			return -1; // Error (keep propagating upward??? or straight up crashing the app)
		}
	}
}

void handleDraw(sockaddr_in clientAddr, AppMsg * msg) {
	// Broadcast to all clients except the sender
	broadCaster(clientAddr, msg);
}

//
// handleMsg -> changeState / handle
// handleDraw
//

void handleMsg(AppMsg * msg) { // Filter out the type
	switch (msg->type) {
		case CONNECT:
			if (currentState == STATE_LOBBY) { stateChange(STATE_ROOM); }
			break;
		case DISCONNECT:
			if (currentState == STATE_ROOM) { stateChange(STATE_LOBBY); }
			break;

		case START:
			if (currentState == STATE_ROOM) { stateChange(STATE_GAME); }
			break;
		case END:
			if (currentState == STATE_GAME) { stateChange(STATE_LEADERBOARD); }
			break;
		case LOBBY:
			if (currentState == STATE_LEADERBOARD) { stateChange(STATE_ROOM); }
			break;

		case NEXT_ROUND:
			if (currentState == STATE_GAME) { stateChange(STATE_NEW_ROUND); }
			break;


		case DRAW:
			if (currentState == STATE_GAME) { handleDraw(msg); }
			break;
		case ANSWER:
			if (currentState == STATE_GAME) { handleAnswer(msg); }
			break;
		case SCORE:
			if (currentState == STATE_GAME) { handleScore(msg); } // else ???? maybe using a map would be cleaner
			break;

		default:
			perror("Incorrect state message: ");
			printMsg(msg);
			break;
	}
}