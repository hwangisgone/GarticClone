<script>
	import RoomLayout from './RoomLayout.svelte';

	export let state = 2;
	export let roomState = 1;

</script>

<RoomLayout>
	<button slot="header" class="btn btn-accent" type="button" on:click={() => state = 1 }>
		Exit room
	</button>

	<div slot="interact">
		Chatting here
		<button class="btn btn-primary" type="button" on:click={() => roomState = 1 }>
			Start game!
		</button>
	</div>
</RoomLayout>