import { writable } from 'svelte/store';

export const PlayerID = writable(0);

export const usernameCheck = writable("");
// export const GameSettings = writable({ PlayerList: { Username	, Point } });
export const GameSettings = writable({ PlayerList: [], RoomID: -1 });
export const UIstate = writable(0);
export const ThisRound = writable({ timer: 30, word: "ahha", role: 0 });

export const JoinCounter = writable(0);
	// 0 is Login
	// 1 is Lobby
	// 2 is Room
	// 3 is Sign Up
	// 4 LeaderBoard