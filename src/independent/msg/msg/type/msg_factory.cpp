#include <memory>		// unique_ptr

#include <auth/msg/msg_auth.hpp>
#include <lobby/msg/msg_lobby.hpp>
#include <room/msg/msg_connection.hpp>
#include <room/msg/msg_start.hpp>
#include <ingame/msg/msg_next_end.hpp>
#include <ingame/msg/msg_ingame.hpp>
#include <leaderboard/msg/msg_leaderboard.hpp>
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
		case MsgType::SUCCESS:		return make_unique<SuccessMsg>();
		case MsgType::FAILURE:		return make_unique<FailMsg>();
		case MsgType::LOGIN:		return make_unique<LoginMsg>();
		case MsgType::REGISTER:		return make_unique<RegisterMsg>();
		case MsgType::LOGOUT:		return make_unique<LogoutMsg>();

		// Lobby
		case MsgType::GET_ROOMS:	return make_unique<GetRoomsMsg>();
		case MsgType::ROOM_LIST:	return make_unique<RoomListMsg>();
		case MsgType::CREATE_ROOM:	return make_unique<CreateRoomMsg>();
		case MsgType::JOIN_ROOM:	return make_unique<JoinRoomMsg>();
		// Room
		case MsgType::CONNECT:		return make_unique<PlayerConnectMsg>();
		case MsgType::DISCONNECT:	return make_unique<PlayerDisconnectMsg>();
		case MsgType::START_GAME: 	return make_unique<StartMsg>();
		// Leaderboard

		case MsgType::GET_LEADERBOARD: return make_unique<GetLeaderboardMsg>();
		case MsgType::RANKING: 		return make_unique<RankingMsg>();
		case MsgType::BACK_TO_ROOM: return make_unique<BackToRoomMsg>();
		// case MsgType::START_GAME: 	return make_unique<StartMsg>();
			// TODO: Should we move this to room state?
		// case MsgType::DESTROY_ROOM:	return make_unique<DestroyRoomMsg>();
			
		default:	return nullptr;
	}
}