<script>
	import { onMount } from "svelte";
	import toast from 'svelte-french-toast';

	import Game from './Game.svelte';
	import GetReady from './GetReady.svelte';
	import LeaderBoard from '../LeaderBoard.svelte';

	import { UIstate, GameSettings, ThisRound, JoinCounter } from "../store/store.ts";

	onMount(() => {
		try {
			window.requestJoinRoom($GameSettings.RoomID); 
		} catch (e) {
			toast.error(e.message);
		}
		$JoinCounter++;
		// Join but this time handled by room state
	});

	let roomState = 1;
	// 0 is Room (get ready)
	// 1 is Game
	// 2 is leaderboard

	// Js Call C++
	// C++ Call Js

	window.room_addPlayer = (playerid, playername) => { 
		$GameSettings.PlayerList.push( { id: playerid, name: playername, point: 0})
		$GameSettings.PlayerList = $GameSettings.PlayerList;
	};
	window.room_removePlayer = (playerid) => { 
		$GameSettings.PlayerList = $GameSettings.PlayerList.filter(p => p.id != playerid);
		console.log("Removed?", playerid);
	};
	window.game_nextRound = (role, timer, word) => {
		$ThisRound.role = role;
		$ThisRound.timer = timer;
		$ThisRound.word = word;
	}
</script>


	<div class="fixed left-1/2">
		<input class="input" type="number" on:change={e => window.room_removePlayer(e.target.value)} />
		<button class="btn" on:click={() => window.room_addPlayer(1, "hehe")} >Add player</button>
		<button class="btn" on:click={window.requestDisconnect} >
			Disconnect (Joined: {$JoinCounter})
		</button>
	</div>

{#if $UIstate == 3}
	<GetReady />
{:else}
	<Game />
{/if}
	