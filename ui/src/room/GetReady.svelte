<script>
	import RoomLayout from './RoomLayout.svelte';
	import { PlayerID, UIstate, PlayerList } from '../store/store.ts';

	export let roomState = 1;


	function toLobby() {
		$UIstate = 1;
	}

	function addPlayer(id, name) {
		$PlayerList.push({playerID: id, playerName: name});
	}

	function removePlayer(id) {
		$PlayerList = $PlayerList.filter(p => p.playerID != id);
	}


	window.room_addPlayer = addPlayer;
	window.room_removePlayer = removePlayer;
</script>

<RoomLayout>
	<button slot="header" class="btn btn-accent" type="button" on:click={() => $UIstate = 1 }>
		Exit room
	</button>

	<div slot="interact">
		Chatting here
		<button class="btn btn-primary" type="button" on:click={() => roomState = 1 }>
			Start game!
		</button>
	</div>
</RoomLayout>