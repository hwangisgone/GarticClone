#include <memory>		// unique_ptr

#include "msg/msg_format.hpp"

#include "states/new/msg_auth.hpp"
#include "states/lobby/msg_lobby.hpp"
#include "states/room/msg_connection.hpp"
#include "states/room/msg_start.hpp"
#include "states/ingame/msg_next_end.hpp"
#include "states/ingame/msg_ingame.hpp"
#include "states/leaderboard/msg_leaderboard.hpp"
// TODO: This is stupid

using namespace std;

// Add to this if you want to add more type (used for deserializing / creating msg to send)
unique_ptr<BaseMsg> factoryProduceMsg(MsgType type) {
	switch(type) {
		// In game (put to first for faster retrieval)
		case MsgType::DRAW:			return make_unique<DrawMsg>();
		case MsgType::ANSWER:		return make_unique<AnswerMsg>();
		case MsgType::SCORE:		return make_unique<ScoreMsg>();
		case MsgType::NEXT_ROUND:	return make_unique<NextRoundMsg>();
		case MsgType::END_GAME:		return make_unique<EndMsg>();

		// Begin
		case MsgType::AUTH:			return make_unique<AuthMsg>();
		case MsgType::ROOM_LIST:	return make_unique<RoomListMsg>();
		// Lobby
		case MsgType::CREATE_ROOM:	return make_unique<CreateRoomMsg>();
		case MsgType::JOIN_ROOM:	return make_unique<JoinRoomMsg>();
		// Room
		case MsgType::CONNECT:		return make_unique<PlayerConnectMsg>();
		case MsgType::DISCONNECT:	return make_unique<PlayerDisconnectMsg>();
		case MsgType::START_GAME: 	return make_unique<StartMsg>();
		// Leaderboard
		// case MsgType::START_GAME: 	return make_unique<StartMsg>();
			// TODO: Should we move this to room state?
		// case MsgType::DESTROY_ROOM:	return make_unique<DestroyRoomMsg>();
			
		default:	return nullptr;
	}
}