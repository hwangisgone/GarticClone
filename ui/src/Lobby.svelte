

<script>
	// @ts-nocheck  
		import { UIstate, usernameCheck, RoomList } from "./store/store.ts";
		import Game from "./room/Game.svelte"
		
		// Add rooms dynamically
		// for (let i = 1; i <= 20; i++) {
		//     RoomList.push({ RoomID: i, Players: 0 });
		// }

		// Js Call C++
		// window.requestJoinRoom(roomID)
		// window.requestCreateRoom(name)
		// C++ Call Js
		window.lobby_addRoom = (id, name) => { 
			$RoomList.push({ RoomID: id, RoomName: name });
			$RoomList = $RoomList;
		};
		window.lobby_toRoom = () => { $UIstate = 2; };	
	</script>
	
<!-- 	{#if $UIstate == 2}
		<Game/>
	{:else if $UIstate == 1} -->
		<div >
			<div class="title">
				<div>
					<button class="top-left-button" on:click={() => $UIstate = 0}> Back </button>
				</div>
				<div>
					Username {$usernameCheck} 
				</div>
				<span class="gTitle">
					<h2 class = "font-bold text-primary content-center" style = "font-size:60px; font-family: Comic Sans MS;"> LOBBY </h2>
				</span>
			</div>
	
			<div >
				<div>
					<div class="grid grid-cols-5 gap-4 rounded-box  p-4 border border-secondary bg-base-content" >
						{#each $RoomList as room}
							<div>
								<!-- <button on:click={() => EnterRoom(roomNumber.RoomID)} class=" font-semibold  btn-outline border-4  border-base-100 btn-secondary  room-button bg-base-content" style = "" > -->
									<button 
									on:click={() => { window.requestJoinRoom(room.RoomID); }} 
									class="font-semibold btn-outline btn-info border-base-100 room-button text-neutral" style = "" >
									<div>Room "{room.RoomName}"  </div>
									<div>ID: {room.RoomID}</div>
								</button>
							</div>
						{/each}
						</div>
				</div>
			</div>
		</div>
	<!-- {/if} -->
	
	<style>
		.room-button {
			width: 220px;
			height: 140px;
			/* display: flex; */
			/* flex-direction: column;
			justify-content: center;
			align-items: center;
			margin: 5px
			/* border: 1px solid #dbdee6; */
			/* background-color: #2d5653; */
			/* cursor: pointer; */
			font-family: Comic Sans MS;
			font-size: 23px;
			margin: 5px;
			 border: 5px solid #758bc6;
			/* margin: 5px */
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
	