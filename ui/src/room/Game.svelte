<script>
	import RoomLayout from './RoomLayout.svelte';

	export let state = 2;
	export let roomState = 1;

</script>

<RoomLayout>
	<button slot="header" class="btn btn-accent" type="button" on:click={() => state = 1 }>
		Exit room
	</button>

	<div slot="players">
		<div>
			players and more eplayers
			<br/>
			Use {'{'}#each{'}'} here
		</div>
		<button class="btn btn-accent" type="button" on:click={() => roomState = 0 }>
			End game
		</button>
	</div>

	<div slot="draw">
		<div>The game is fun!</div>
	</div>

	<div slot="interact">
		Chatting chatty chat chat me chat with who?
	</div>
</RoomLayout>





<!-- Add leaderboard too -->
<!-- 
<button class="btn btn-primary" type="button" on:click={ roomState = 1; }>
	Leaderboard
<button/> -->