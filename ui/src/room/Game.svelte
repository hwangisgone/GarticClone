<script>
// @ts-nocheck
	import Drawing from "./Drawing.svelte";
	import RoomLayout from "./RoomLayout.svelte";

	import { UIstate, GameSettings } from "../store/store.ts";


	
	$GameSettings.PlayerList.push( { id: 1, name: 'Thuy Trinh', point: 100})
	$GameSettings.PlayerList.push( { id: 2, name: 'AAAAAA', point: 60})
	$GameSettings.PlayerList.push( { id: 3, name: 'BBBBBBBBB', point: 80})
	$GameSettings.PlayerList.push( { id: 4, name: 'CCCCCCCCC', point: 200})
	// let i;
	// for(i = 0; i < 40; i++){
	// 	$GameSettings.PlayerList.push( {Username: 'CCCCCCCCC', Point: i * 20})
	// }

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

	<div slot="interact" class="h-full">
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
			
			
		<div class='content-center'>
		  <input placeholder="Write a message"  type="text" class="input input-bordered max-w-xs"bind:value={msg}/>
		  <button on:click={EnterChat} class = 'font-size: 15px  text-neutral'> Enter</button>
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