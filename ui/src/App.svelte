<script>
	// @ts-nocheck
	import Login from "./auth/Login.svelte"
	import SignUp from "./auth/SignUp.svelte";
	import Room from "./room/Room.svelte";
	import Lobby from "./Lobby.svelte";
	// import Clock from "./Clock.svelte";
 // import Chat from "./chat.svelte";

	import { PlayerID, UIstate } from './store/store.ts';
		// import { sineIn } from "svelte/easing";
		import LeaderBoard from "./LeaderBoard.svelte";

	window.updatePlayerID = (id) => { $PlayerID = id; }
</script>

<input type="number" class="fixed" bind:value={$UIstate} />

{#if $UIstate == 2}
	<Lobby/>
{:else if $UIstate == 3 || $UIstate == 4}
	<Room/>
{:else if $UIstate == 5}
	<LeaderBoard/>
{:else}
	<div class="container h-screen mx-auto py-10 max-w-[60rem]">
		<div class="bg-gray-100 h-full shadow-2xl rounded-3xl flex justify-center text-center items-center">
			{#if $UIstate == 0}
				<Login/>
			{:else if $UIstate == 1}
				<SignUp/>
			{/if}
		</div>
	</div>
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

/*	.myDiv {
		width: 900px;
		height: 700px;*/
/*		background-color: rgb(242, 246, 247);*/
/*		border: 1px solid #ccc;
		margin: 0 auto; /* Set left and right margins to auto for horizontal centering */
/*		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		background-position: center;
	}*/
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
	/*.centered-input {
				display: flex;
				justify-content: center;
				align-items: center;
				margin-top: 10px; Adjust margin as needed 
		}*/
</style>