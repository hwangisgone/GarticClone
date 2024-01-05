<script>
	// @ts-nocheck
		import Canvas from "./Canvas.svelte"
		import RoomLayout from "./RoomLayout.svelte";
		import Lobby from "../Lobby.svelte";
		import {UIstate, GameSettings} from "../store/store.ts";
		import LeaderBoard  from '../LeaderBoard.svelte';
		// import Room from './Room.svelte';
	
	
		export let state = 2;
		export let roomState = 1;
	
		let windowState = 0;
		// for(int i = 1; i <= 10; i++)Ơ
		
		$GameSettings.PlayerList.push( {Username: 'Thuy Trinh', Point: 100})
		$GameSettings.PlayerList.push( {Username: 'AAAAAA', Point: 60})
		$GameSettings.PlayerList.push( {Username: 'BBBBBBBBB', Point: 80})
		$GameSettings.PlayerList.push( {Username: 'CCCCCCCCC', Point: 200})
		let i;
		for(i = 0; i < 40; i++){
	
			$GameSettings.PlayerList.push( {Username: 'CCCCCCCCC', Point: i * 20})
		}
		let messages = [];
		messages.push("Hello");
		messages.push("My name is Thuy");
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
	{#if $UIstate == 1}
	 <Lobby/>
	{:else if  $UIstate == 5}
	   <LeaderBoard/>
	{:else}
	
	<!-- <button class="btn btn-accent" type="button" on:click={Back}> Back Lobby </button> -->
	<RoomLayout>
		
		<button slot="header" class="btn btn-accent" type="button" on:click={() => $UIstate = 1  }>
			Exit room
		</button>
		
	
		<div slot="players">
			<div class="text-lg content-center">
				Leaderboard
				<!-- <br/>
				Use {'{'}#each{'}'} here -->
				<div class="overflow-y-scroll bg-base-200" style="height:650px">
					 <div class = "flex flex-col items-center gap-10 p-10">
						{#each numbers as number}
	
							<div class = "flex flex-col text-center border-4 border-sky-500 rounded-full border-double " style = "width:300px" >
								
								<strong style = 'color-font: white'>Hello {number}</strong>
								<span>0 points</span>
							</div>
						{/each}
						<!-- <div class = "flex flex-col">
							<strong>Hello</strong>
							<span>0 points</span>
						</div>
						<div class = "flex flex-col">
							<strong>Hello</strong>
							<span>0 points</span>
						</div> -->
					 </div>
				  </div>
				</div>
			<button class="btn btn-accent" type="button" on:click={() => $UIstate = 1 }>
				End game
			</button>
			<button class="btn btn-accent" type="button" on:click={() => $UIstate = 5}>
				Go to LeaderBoard
			</button>
			<!-- <span></span> -->
		</div>
	

		<div slot="draw">
			<div class="h-full w-full">
<!-- 				<div class="footer fixed">
					<progress class="progress progress-accent w-full" value={countdown} max="30"></progress>
				</div> -->
				<Canvas />
			</div>
		</div>
	
		<div slot="interact" style = "background-color:aliceblue">
			<div class="overflow-y-auto h-32" style = 'height: cover'>
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
				  <input placeholder="Write a message"  type="text" class="input input-bordered w-full max-w-xs"bind:value={msg}/>
				  <button on:click={EnterChat} class = 'font-size: 15px  text-neutral'> Enter</button>
			    </div>
			
		</div>
		<div slot = "bottomright">
			<!-- {countdown} -->
			
		</div>
	</RoomLayout>
	
	{/if}
	
	
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
	  </style>