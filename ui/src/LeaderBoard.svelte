<script>
	// @ts-nocheck
	
		import Lobby from "./Lobby.svelte";
		import Game from "./room/Game.svelte";
	import {GameSettings, UIstate} from "./store/store.ts";
			// # Your list of dictionaries
	
			// let PlayerList = [
			//     {Player: 'A', Point : 0},
			//     {Player: 'B', Point : 0},
			//     {Player: 'C', Point : 20},
			//     {Player: 'D', Point : 40},
			//     {Player: 'E', Point : 15}
			// ]
	
			function sortByPoints() {
				$GameSettings.PlayerList = $GameSettings.PlayerList.slice().sort((a, b) => b.Point - a.Point);
		}
	
			// Call the function to sort PlayerList based on "Point"
			sortByPoints();
	
	
	
	</script>
	
	{#if $UIstate == 1}
	<Lobby/>
	{:else if $UIstate == 4}
	<Game/>
	{:else}
	<div >
			<!-- <div class = 'title'>
				<button class="top-left-button" on:click={() => $UIstate = 1}> Back Lobby</button>
			</div> -->
			<div class = 'title font-bold text-success' style = 'font-size:xx-large'> Rank</div>
			<div class="rank-container bg-base-content ">
				<!-- Display ranks with the highest rank centered -->
				<!-- <div class="rank">2</div> -->
				<div class="rank" >{$GameSettings.PlayerList[2].Username}</div>
				<div class="rank highest-rank">{$GameSettings.PlayerList[0].Username}</div>
				<div class="rank">{$GameSettings.PlayerList[1].Username}</div>
				<!-- <div class="rank">5</div> -->
			</div>
			<div class = 'title'>
				<button class="" on:click={() => $UIstate = 1}> End Game</button>
				<button class="" on:click={() => $UIstate = 4}> Continue</button>
			</div>
		</div>
		
	
	{/if}
	
	<style>
			/* Apply styles to the container */
			.rank-container {
				display: flex;
				justify-content: center;
				align-items: center;
				height: 300px; /* Set height to full viewport height */
				color:rgb(26, 44, 44);
			}
	
			/* Styling for each rank */
			.rank {
				font-size: 30px;
				font-weight: bold;
				padding: 10px;
				margin: 0 10px; /* Adjust the margin between ranks */
				color:rgb(26, 44, 44);
			}
	
			/* Styling for the highest rank */
			.highest-rank {
				background-color: #ffcc00; /* Highlight the highest rank with a background color */
				margin-top: -100px; 
			}
	
			.top-left-button {
			width: 100px;
			position: absolute;
			top: 10px;
			left: 10px;
			padding: 10px;
			/* background-color: white;
			border: 1px solid #ccc; */
			cursor: pointer;
			background-color:rgb(46, 80, 81)
		}
	</style>
