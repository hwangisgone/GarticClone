<script>
// @ts-nocheck
	import { Canvas } from 'svelte-canvas';
	import DrawingLayer from "./DrawingLayer.svelte";
	import MeTest from "./MeTest.svelte";

	import RoomLayout from "./RoomLayout.svelte";
	import Lobby from "../Lobby.svelte";
	import {UIstate, GameSettings} from "../store/store.ts";
	import LeaderBoard  from '../LeaderBoard.svelte';
	// import Room from './Room.svelte';


	let windowState = 0;
	// for(int i = 1; i <= 10; i++)
	
	$GameSettings.PlayerList.push( { id: 1, name: 'Thuy Trinh', point: 100})
	$GameSettings.PlayerList.push( { id: 2, name: 'AAAAAA', point: 60})
	$GameSettings.PlayerList.push( { id: 3, name: 'BBBBBBBBB', point: 80})
	$GameSettings.PlayerList.push( { id: 4, name: 'CCCCCCCCC', point: 200})
	// let i;
	// for(i = 0; i < 40; i++){
	// 	$GameSettings.PlayerList.push( {Username: 'CCCCCCCCC', Point: i * 20})
	// }

	// Js Call C++
	// window.requestDisconnect()
	// window.requestStartGame()
	// window.request
	// C++ Call Js
	window.room_addPlayer = (playerid, playername) => { 
		$GameSettings.PlayerList.push( { id: playerid, name: playername, point: 100})
		$GameSettings.PlayerList = $GameSettings.PlayerList;
	};
	window.room_removePlayer = (playerid) => { 
		$GameSettings.PlayerList = $GameSettings.PlayerList.filter(p => p.id != playerid);
		console.log("Removed?", playerid);
	};


	let messages = [];

	messages.push("Hello");
	messages.push("My name is Thuy");
	messages.push("My name is Thuy");
	messages.push("My name is Thuy");
	messages.push("My name is Thuy");
	messages.push("My name is Thuy");

	let msg;
	function EnterChat(){
		messages.push(msg);
		messages = messages;
	}

	// let RoomList = [];
	// let PlayerList = [];
	
	// Add rooms dynamically
	// for (let i = 1; i <= 20; i++) {
	//     RoomList.push({ RoomID: i, PlayerList: [] });
	// }
	// // automatic add a new username when enter to the room
	// RoomList[$RoomID_Enter].PlayerList.push({Username: $usernameCheck, Point: 0 })
	let numbers = [1, 2, 3, 4, 5 ,6 , 7, 0 ]
	function Back(){
		windowState = 1;
	}
	// count down time 
	import { onMount } from "svelte";
	let countdown = 30;
	let timer;
  $: {
	if (countdown === 0) {
	  if (timer) {
		clearInterval(timer);
		timer = null;
	  }
	}
  }
  onMount(() => {
	timer = setInterval(() => {
	  countdown -= 1;
	}, 1000);
  });
  // countdown time 


</script>



	<div class="fixed left-1/2">
		<input class="input" type="number" on:change={e => window.room_removePlayer(e.target.value)} />
		<button class="btn" on:click={() => window.room_addPlayer(1, "hehe")} >Add player</button>
		<button class="btn" on:click={window.requestDisconnect} >Disconnect</button>
	<!-- <button class="btn btn-accent" type="button" on:click={Back}> Back Lobby </button> -->
		</div>

<div class="grid h-screen grid-cols-4">
  <div class="col-span-1 flex flex-col border-r border-gray-300 overflow-hidden">
	<div class="flex-1 overflow-y-auto p-4">
	  <!-- Your expandable content goes here -->
				{#each $GameSettings.PlayerList as player}

					<div class = "flex flex-col text-center border-4 border-sky-500 rounded-full border-double w-full">
						
						<strong style = 'color-font: white'>{player.name} {player.id}</strong>
						<span>{player.point} points</span>
					</div>
				{/each}


	</div>
	<div class="h-1/4 bg-blue-200 flex items-center justify-center">
	  <!-- Your fixed-size bottom content goes here -->
	  <p>Fixed-size content at the bottom</p>
	  <!-- ... -->
	</div>
  </div>
  <div class="col-span-3 flex flex-col h-screen">
	<div class="flex-1 bg-white h-3/4">
		<MeTest/>
	</div>
	<div class="h-1/4">
	<div class="h-3/4 overflow-y-auto">
		{#each messages as mess}
		  <div class="chat chat-start">
			<div class="chat-image avatar">
			  <div class="w-10 rounded-full">
				<img alt="Tailwind CSS chat bubble component" src="https://daisyui.com/images/stock/photo-1534528741775-53994a69daeb.jpg" />
			  </div>
			</div>
			<div class="chat-bubble">{mess}</div>
		  </div>
		{/each}
	</div>
		
		
			<div class = 'content-center'>
			  <input placeholder="Write a message"  type="text" class="input input-bordered max-w-xs"bind:value={msg}/>
			  <button on:click={EnterChat} class = 'font-size: 15px  text-neutral'> Enter</button>
			</div>
	</div>
  </div>
</div>
	
	
	<!-- 
	<style>
		/* Apply a bottom border to the element with the class "bottom-line" */
		.container {
		  position: relative;
		  border: 1px solid #ccc; /* Optional: Add a border for visibility */
		  display: flex;
		  flex-direction: column;
		  min-height: 70vh; /* Set a minimum height to ensure the footer stays at the bottom */
		}
	
		/* Content styling (adjust as needed) */
		.content {
		  flex: 1; /* Allow content to grow and take remaining space */
		  padding: 10px;
		}
	
		/* Footer styling */
		.footer {
		  text-align: center;
		  padding: 10px;
		  background-color: #f0f0f0; /* Optional: Add a background color to the footer */
		}
		.chat{
			
		}
	  </style> -->