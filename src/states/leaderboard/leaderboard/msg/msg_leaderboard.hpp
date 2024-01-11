#ifndef MSG_LEADERBOARD_H
#define MSG_LEADERBOARD_H

#include <msg/msg_format.hpp>

// TODO: Implement this?
// class DestroyRoomMsg : public BaseMsg {
// public:
// 	DestroyRoomMsg() : BaseMsg(MsgType::DESTROY_ROOM) {}
// };

class GetLeaderboardMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	GetLeaderboardMsg(): BaseMsg(MsgType::GET_LEADERBOARD) {}
};

class RankingMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	RankingMsg(): BaseMsg(MsgType::RANKING) {}
};

#endif