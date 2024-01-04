<script>
	import RoomLayout from './RoomLayout.svelte';
	import Canvas from './Canvas.svelte';

	export let state = 2;
	export let roomState = 1;
<<<<<<< Updated upstream
=======

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
	let messReceive = [];
	messReceive.push({user: 'abssasas', mes: "kkkkkkkkkkkkkkk"});
	messReceive.push({user: 'abssasas', mes: "kkkkkkkkkkkkkkk"});
	messReceive.push({user: 'abssasas', mes: "kkkkkkkkkkkkkkk"});
	let messages = [];
    messages.push({user: 'send', mes: "kkkkkkkkkkkkkkk"});
   
    let msg;
    function EnterChat(){
        messReceive.push({user: 'Me', mes: msg});
        messReceive = messReceive;
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


>>>>>>> Stashed changes
</script>

<RoomLayout>
	<button slot="header" class="btn btn-accent" type="button" on:click={() => state = 1 }>
		Exit room
	</button>

<<<<<<< Updated upstream
	<div slot="players">
		<div>
			players and more eplayers
			<br/>
			Use {'{'}#each{'}'} here
		</div>
		<button class="btn btn-accent" type="button" on:click={() => roomState = 0 }>
=======
	<div slot="players" >
		<div class="text-lg">
			<p class = 'text-primary-content font-bold' style = 'font-size:x-large'> Leaderboard</p>
			<!-- <br/>
			Use {'{'}#each{'}'} here -->
			<div class="overflow-y-scroll h-32 " style="height:650px">
				<!-- <div class="table table-xs table-pin-rows table-pin-cols">
				  <thead style = "height:50px">
					<tr>
					  <th></th> 
					  <td style = "font-size: 25px;">UserName</td> 
					  <td style = "font-size: 25px;">Point</td> 
					  <th></th> 
					</tr>
				  </thead> 
				 <tbody>
					{#each $GameSettings.PlayerList as player}
					<tr>
					  <th></th> 
					  <td style = "font-size: 20px;">{player.Username}</td> 
					  <td style = "font-size: 20px;">{player.Point}</td>
					 
					</tr>
					{/each}
					
				  </tbody> 
				  
			     </div> -->
				 <div class = "flex flex-col items-center gap-10 p-10">
					{#each numbers as number}

					    <div class = "flex flex-col border-4 border-sky-500 rounded-full border-double bg-neutral" style = "width:300px" >
							
						    <strong>Hello {number}</strong>
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
>>>>>>> Stashed changes
			End game
		</button>
	</div>

<<<<<<< Updated upstream
	<Canvas slot="draw"/>

	<div slot="interact">
		Chatting chatty chat chat me chat with who?
=======
	<div slot="draw" >
		
		<div class="footer">
			<progress class="bg-neutral progress progress-accent w-full" value={countdown} max="30"></progress>
		</div>
		The game is fun OK!
	</div>

	<!-- <div slot = "draw" class="container">
		<div class="content">
		 
		  <p>This is the main content of the div.</p>
		</div>
		<div class="footer">
		  <p>This is the footer of the div.</p>
		</div>
	  </div> -->

	<div slot="interact" style = "background-color:aliceblue">
		<div class="overflow-y-auto h-32">
			{#each messReceive as mess}
			  <div class="chat chat-start">
				<!-- <div class="chat-image avatar">
				  <div class="w-10 rounded-full">
					<img alt="Tailwind CSS chat bubble component" src="https://daisyui.com/images/stock/photo-1534528741775-53994a69daeb.jpg" />
				  </div>
				</div> -->
				<div class="chat-header text-neutral">
					{mess.user}
					
				  </div>
				<div class="chat-bubble">{mess.mes}</div>
			  </div>
			{/each}
			<!-- {#each messages as mess}
			  <div class="chat chat-end">
				<div class="chat-image avatar">
				  <div class="w-10 rounded-full">
					<img alt="Tailwind CSS chat bubble component" src="https://daisyui.com/images/stock/photo-1534528741775-53994a69daeb.jpg" />
				  </div>
				</div>
				<div class="chat-bubble">{mess}</div>
			  </div>
			{/each} -->
		</div>
		
		
			<!-- <form > -->
			  <input placeholder="Write a message"  type="text" class="input input-bordered w-full max-w-xs"bind:value={msg}/>
			  <button on:click={EnterChat}> Enter</button>
		  <!-- </form> -->
		
	</div>
	<div slot = "bottomright">
		<!-- {countdown} -->
		
>>>>>>> Stashed changes
	</div>
</RoomLayout>





<<<<<<< Updated upstream
<!-- Add leaderboard too -->
<!-- 
<button class="btn btn-primary" type="button" on:click={ roomState = 1; }>
	Leaderboard
<button/> -->
=======
    /* Footer styling */
    .footer {
      text-align: center;
      padding: 10px;
      background-color: #1a4a82; /* Optional: Add a background color to the footer */
    }
	.chat{
		
	}
  </style>
>>>>>>> Stashed changes
