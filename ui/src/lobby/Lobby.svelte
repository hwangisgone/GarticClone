<script>
	// "export let state" allows everything outside to bind to this value
	export let state = 1;

	import { PlayerID } from '../store/store.ts';
	// 0 is Login
	// 1 is Lobby
	// 2 is Room
</script>


<button class="btn btn-accent" type="button" on:click={ () => state = 0 }>
	Back {$PlayerID}
</button>

<div>
	Something something something
</div>

<div>
	This is the lobby
</div>


<button class="btn btn-secondary" type="button" on:click={ () => { /*window.getInRoom(roomID);*/ state = 2; } }>
	Go to a room
</button>