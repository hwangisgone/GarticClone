<script>
// @ts-nocheck
	import Drawing from "./Drawing.svelte";
	import RoomLayout from "./RoomLayout.svelte";

	import { UIstate, GameSettings, PlayerID } from "../store/store.ts";


	
	// $GameSettings.PlayerList.push( { id: 1, name: 'Thuy Trinh', point: 100})
	// $GameSettings.PlayerList.push( { id: 2, name: 'AAAAAA', point: 60})
	// $GameSettings.PlayerList.push( { id: 3, name: 'BBBBBBBBB', point: 80})
	// $GameSettings.PlayerList.push( { id: 4, name: 'CCCCCCCCC', point: 200})
	// let i;
	// for(i = 0; i < 40; i++){
	// 	$GameSettings.PlayerList.push( {Username: 'CCCCCCCCC', Point: i * 20})
	// }




	let messages = [
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
	{name: "Thuy", answer: "what"},
		];
	let yourmsg = "";
	let correctAnswer = false;

	// Js Call C++
	// window.requestDraw(x, y, clr)
	// window.requestAnswer(answer)
	// C++ Call Js

	window.game_score = (in_id, in_score) => {
		const player = $GameSettings.PlayerList.find(p => p.id === in_id);
		if (player) {
			player.point = score;
			if (player.id == $PlayerID) {
				correctAnswer = true;
			}
		}
	}

	window.game_answer = (in_id, in_answer) => {
		const player = $GameSettings.PlayerList.find(p => p.id === in_id);

		if (player) {
			messages.push({ name: p.name, answer: in_answer });
			messages = messages;
		}
	}


	let numbers = [1, 2, 3, 4, 5 ,6 , 7, 0 ]
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

<RoomLayout>

	<div slot="draw" class="bg-white h-full rounded-xl">
		<Drawing/>
	</div>

	<div slot="interact" class="h-full flex">
		<div class="w-3/4 h-full flex flex-col border-primary border-r-2">
			<div class="p-2 px-4 grow overflow-y-scroll">
				{#each messages as mess}
					<div>{mess.name}: <span class="text-gray-500">{mess.answer}</span></div>
				{/each}
			</div>
			
			<div class="flex content-center text-white gap-2">
		  		<input placeholder={correctAnswer ? "Waiting for other players" : "Your answer"}  
		  		type="text" class="input input-bordered input-sm w-full py-0" 
		  		bind:value={yourmsg} disabled={correctAnswer}/>
		  		<button on:click={() => window.requestAnswer(yourmsg)}
		  			class="btn btn-sm"
		  			disabled={correctAnswer}
		  			>Enter</button>
			</div>		
		</div>
		<div class="w-1/4 flex items-center justify-center">
			<div class="text-6xl text-neutral">{countdown}</div>
		</div>
	</div>
</RoomLayout>





	
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