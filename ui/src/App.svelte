<script>
	// @ts-nocheck
	import Login from "./auth/Login.svelte"
	import SignUp from "./auth/SignUp.svelte";
	import Lobby from "./Lobby.svelte";
	// import Clock from "./Clock.svelte";
 // import Chat from "./chat.svelte";
	import Room from "./room/Game.svelte";
	import { PlayerID, UIstate } from './store/store.ts';
		// import { sineIn } from "svelte/easing";
		import LeaderBoard from "./LeaderBoard.svelte";

</script>

<input type="number" bind:value={$UIstate} />

{#if $UIstate == 1}
	<Lobby/>
{:else if $UIstate == 2}
	<Room/>
{:else if $UIstate == 5}
	<LeaderBoard/>
{:else}
<!-- <div class="myDiv"> -->
<div class="container mx-auto py-10 max-w-[60rem]">
	{#if $UIstate == 0}
		<div class="bg-white py-16 md:px-52 border border-primary rounded-xl">
			<Login/>
		</div>
	{:else if $UIstate == 3}
		<SignUp/>
	{/if}
</div>
<!-- </div> -->
{/if}

<style>
	/* Set the background color for the entire component */
	:global(html, body) {
		margin: 0;
		height: 100%;
	}

	:global(body) {
		background-image: url('./backgr3.png'); 
		background-size: cover;
		background-position: center;
		background-repeat: no-repeat;
	}

	/* Style for the "Hello" line */
	.Topic{
		text-align: center;
		padding: 50px; /* Adjust padding as needed */
		font-size: 50px; /* Adjust font size as needed */
		
		align-items: center;
	}
	.myDiv {
/*		width: 900px;
		height: 700px;*/
/*		background-color: rgb(242, 246, 247);*/
		border: 1px solid #ccc;
		margin: 0 auto; /* Set left and right margins to auto for horizontal centering */
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		background-position: center;
	}
/*    .myInput {
			width: 300px;
			height: 35px;
			display: flex;
				justify-content: center;
			margin-top: 10px;
			margin: 10px;
			align-items: center;
		}*/
/*    .myButton {
		/* position: absolute;
		top: 10px;
		left: 10px;
		padding: 10px; */
/*    width: 100px;
		height: 50px;*/
/*     background-color: white; 
		border: 1px solid #ccc;
		cursor: pointer;
	}*/
	.centered-input {
				display: flex;
				justify-content: center;
				align-items: center;
				/* margin-top: 10px; Adjust margin as needed */
		}
</style>