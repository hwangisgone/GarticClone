#include "serialize.h"


// DrawMsg: [x 2|y 2|clr 4 (rgba)]
// AnswerMsg: [user 100|message 900]
// ScoreMsg: [user 100|score 4]




void handleMsg(AppMsg * msg) {
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