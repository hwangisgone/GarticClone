import { writable } from 'svelte/store';

export const PlayerID = writable("");


export const UIstate = writable(0);
	// 0 is Login
	// 1 is Lobby
	// 2 is Room
export const PlayerList = writable([]);

export const drawSettings = writable({ color: '#000000', size: 4 });