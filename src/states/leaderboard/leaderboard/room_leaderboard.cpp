#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#include <server/room_handler.hpp>

#include <msg/msg_format.hpp>
#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>

using namespace std;

// bool comparePlayers( pair<int, Player>& a, pair<int, Player>& b) {
//     return a.second.currentScore > b.second.currentScore;
// }

// unordered_map<int, Player> getSortedPlayerMap(unordered_map<int, Player>& inputMap) {
//     // Convert input map to a vector of pairs for sorting
//     vector<pair<int, Player>> playerVector(inputMap.begin(), inputMap.end());

//     // Sort the vector using the custom comparator
//     sort(playerVector.begin(), playerVector.end(), comparePlayers);

//     return inputMap;
// }

// Player getPlayerWin(unordered_map<int, Player>& inputMap){

// 	unordered_map<int, Player> map_sort = getSortedPlayerMap(inputMap);
// 	auto first_one = map_sort.begin();
// 	return first_one->second;
// }

// // for saving player (account) statistic point
// int getPlayerPoint(unordered_map<int, Player>& inputMap, int playerID){
// 	for (auto& pair : inputMap) {
//         if( pair.first == playerID){
// 			Player& player = pair.second;
// 			return player.currentScore;
// 		}
// 		else{
// 			// no find this playerID
// 		}
// 	}
// 	return 0;
// }

// int plusPlayerPoint(unordered_map<int, Player>& inputMap, int playerID, int plusPoint){
// 	for (auto& pair : inputMap) {
//         if( pair.first == playerID){
// 			Player& player = pair.second;
// 			player.currentScore += plusPoint;
// 			return plusPoint;
// 		}
// 		else{
// 			// no find this playerID
// 		}
// 	}
// 	return 0;
// }

void LeaderboardState::handle(const BaseMsg& msg, int playerID) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	//unordered_map<int,Player> sort_playerMap;
	// sort_playerMap = room->playerMap;

	switch (msg.type())
	{
	case MsgType::END_GAME:
		//sort_playerMap = getSortedPlayerMap(sort_playerMap);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}