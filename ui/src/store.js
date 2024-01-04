import { writable, readable, derived } from 'svelte/store';

export const usernameCheck = writable('');

export const RoomID_Enter = writable(0);

export const GameSettings = writable({
	//roomID: 0,
	numRound: 5,
	timer: 10,
	PlayerList: []
});

export const time = readable(new Date(), function start(set) {
	const interval = setInterval(() => {
		set(new Date());
	}, 1000);

	return function stop() {
		clearInterval(interval);
	};
});

const start = new Date();

export const elapsed = derived(
	time,
	($time) => {}
);