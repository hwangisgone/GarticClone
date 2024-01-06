#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#include <server/room_handler.hpp>

#include <msg/msg_format.hpp>
#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>

using namespace std;

// vector<pair<int, Player>> sortPlayers(const unordered_map<int, Player>& players)
// {
//     // Copy elements to a vector
//     vector<pair<int, Player>> sortedPlayers(players.begin(), players.end());

//     // Sort the vector by PlayerID
//     sort(sortedPlayers.begin(), sortedPlayers.end(),
//      [](const auto& lhs, const auto& rhs) {
//         return lhs.second.currentScore < rhs.second.currentScore;
//     });

//     return sortedPlayers;
// }

Player getPlayerWin(unordered_map<int, Player>& inputMap)
{
    unordered_map<int, Player>:: iterator f = inputMap.begin();

    int s = f->second.currentScore;
    int index = f->first;

    unordered_map<int, Player>:: iterator p;
    for( p = inputMap.begin() ; p!= inputMap.end() ; p++){
        if(p->second.currentScore > s)
        {
            s = p->second.currentScore;
            index = p->first;
        }
    }
    p = inputMap.find(index);
    return p->second;
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

void updatePointToAll( unordered_map<int, Player>& inputMap){

	unordered_map<int, Player>:: iterator p;
    for( p = inputMap.begin() ; p!= inputMap.end() ; p++){
        Player player = p->second;
		//PlayerAccount& account = player.account;
		const_cast<PlayerAccount&> (player.account).totalScore = player.currentScore;
    }
}
void LeaderboardState::handle(const BaseMsg& msg, int playerID) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	unordered_map<int,Player> sort_playerMap;
	sort_playerMap = room->playerMap;

	switch (msg.type())
	{
	case MsgType::END_GAME:
		{

			Player win_p = getPlayerWin(room->playerMap);
		}
		break;
	default:
		cerr << "LEADERBOARD: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}