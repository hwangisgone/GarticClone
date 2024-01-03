<script>
// @ts-nocheck

	import Game from './Game.svelte';
	import GetReady from './GetReady.svelte';

	let roomState = 1;
	// 0 is Room (get ready)
	// 1 is Game
	// 2 is leaderboard
</script>



{#if roomState == 0}
	<GetReady bind:roomState />
{:else}
	<Game bind:roomState />
{/if}
	