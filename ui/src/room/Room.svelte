<script>
	import Game from './Game.svelte';
	import GetReady from './GetReady.svelte';
	// "export let state" allows everything outside to bind to this value
	export let state = 2;
	// 0 is Login
	// 1 is Lobby
	// 2 is Room


	let roomState = 0;
	// 0 is Room (get ready)
	// 1 is Game
	// 2 is leaderboard
</script>



{#if roomState == 0}
	<GetReady bind:state bind:roomState />
{:else}
	<Game bind:state bind:roomState />
{/if}
	