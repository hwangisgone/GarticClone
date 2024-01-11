<script>
// @ts-nocheck  
	import { UIstate, usernameCheck } from "./store/store.ts";
	import { onMount } from "svelte";

	onMount(() => {
		window.requestGetRooms();
	});

	let RoomList = [
		{RoomID: 1, RoomName: "Me room"},
		{RoomID: 2, RoomName: "You room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},

		{RoomID: 3, RoomName: "Us room"},
		{RoomID: 3, RoomName: "Us room"},

];
	// Js Call C++
	// window.requestGetRooms()
	// window.requestJoinRoom(roomID)
	// window.requestCreateRoom(name)

	// C++ Call Js
	window.lobby_addRoom = (id, name) => { 
		RoomList.push({ RoomID: id, RoomName: name });
		RoomList = RoomList;
	};
	window.lobby_toRoom = () => { $UIstate = 2; };	
</script>
<!-- 		<div class="title">
		<div>
			<button class="top-left-button" on:click={() => $UIstate = 0}> Logout </button>
		</div>
		<div>
			Username {$usernameCheck} 
		</div>
	</div> -->

<div class="mx-auto container px-12 h-screen flex items-center justify-center">


	<div class="bg-white p-4 rounded-xl flex flex-col items-center justify-content">
		<span class="gTitle">
			<h2 class = "font-bold text-primary content-center" style = "font-size:60px; font-family: Comic Sans MS;"> LOBBY </h2>
		</span>
		<div class=" h-[60vh] w-[70vw] rounded-box p-4 bg-gray-600 border border-neutral overflow-y-scroll " >
	<div class="h-full grid grid-cols-5 gap-4">
		{#each RoomList as room}
			<div class="aspect-square ">
				<button 
					on:click={() => { window.requestJoinRoom(room.RoomID); }} 
					class="hover:border-8 border-info rounded-2xl bg-white h-full w-full rounded-2xl text-neutral ">
					<strong class="font-bold text-xl ">{room.RoomName}</strong>
					<span class="text-gray-500">#{room.RoomID}</span>
				</button>
			</div>
		{/each}
	</div>
		{#if RoomList.length == 0}
			<div class="text-gray-500 text-xl">No room created yet...</div>
		{/if}
		</div>		
	</div>
	
</div>
	
	<style>
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
	