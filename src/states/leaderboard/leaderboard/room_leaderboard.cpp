#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#include <server/room_handler.hpp>

#include <msg/msg_format.hpp>
#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>

using namespace std;

vector<pair<int, Player>> sortPlayers(const unordered_map<int, Player>& players)
{
    // Copy elements to a vector
    vector<pair<int, Player>> sortedPlayers(players.begin(), players.end());

    // Sort the vector by PlayerID
    sort(sortedPlayers.begin(), sortedPlayers.end(),
     [](const auto& lhs, const auto& rhs) {
        return lhs.second.currentScore < rhs.second.currentScore;
    });

    return sortedPlayers;
}


Player getPlayerWin(unordered_map<int, Player>& inputMap){

	vector<pair<int, Player>> sortedVec = sortPlayers(players);

    pair<int, Player> p_win = sortedVec.back();

	return p_win.second;
}

// // for saving player (account) statistic point
int getPlayerPoint(unordered_map<int, Player>& inputMap, int playerID){
	for (auto& pair : inputMap) {
        if( pair.first == playerID){
			Player& player = pair.second;
			return player.currentScore;
		}
		else{
			// no find this playerID
		}
	}
	return 0;
}

int plusPlayerPoint(unordered_map<int, Player>& inputMap, int playerID, int plusPoint){
	for (auto& pair : inputMap) {
        if( pair.first == playerID){
			Player& player = pair.second;
			player.currentScore += plusPoint;
			return plusPoint;
		}
		else{
			// no find this playerID
		}
	}
	return 0;
}

void LeaderboardState::handle(const BaseMsg& msg, int playerID) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	unordered_map<int,Player> sort_playerMap;
	sort_playerMap = room->playerMap;

	switch (msg.type())
	{
	case MsgType::END_GAME:
		//sort_playerMap = getSortedPlayerMap(sort_playerMap);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}