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
export const RoomList = writable([
	{RoomID: 1, RoomName: "Me room"},
	{RoomID: 2, RoomName: "You room"},
	{RoomID: 3, RoomName: "Us room"},

	]);

export const drawSettings = writable({ color: '#000000', size: 4 });