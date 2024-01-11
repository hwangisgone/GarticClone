import { writable } from 'svelte/store';

export const PlayerID = writable("");

export const usernameCheck = writable("");
// export const GameSettings = writable({ PlayerList: { Username	, Point } });
export const GameSettings = writable({ PlayerList: [] });
export const UIstate = writable(2);
	// 0 is Login
	// 1 is Lobby
	// 2 is Room
	// 3 is Sign Up
	// 4 LeaderBoard