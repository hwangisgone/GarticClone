<script>
	import { PlayerID, UIstate } from '../store/store.ts';
	// 0 is Login
	// 1 is Lobby
	// 2 is Room

	let RoomList = [
		{roomID: 1, roomName: "holy" },
		{roomID: 2, roomName: "holybeetch" },
		{roomID: 3, roomName: "fuck" },
		{roomID: 4, roomName: "fuck1" },
		{roomID: 5, roomName: "fuck2" },
		{roomID: 6, roomName: "fuck3" },
		{roomID: 7, roomName: "fuck4" },
		{roomID: 8, roomName: "fuck" },
	];

	function addRoom(id, name) {
		RoomList.push({roomID: id, roomName: name})
	}
	
	function createRoom() {

	}

	function toRoom(id) {
		$UIstate = 2;
	}

	window.lobby_addRoom = addRoom;			// Assign 2;
	window.lobby_createRoom = createRoom;	// Assign 3;
	window.lobby_toRoom = toRoom;		// Assign 4;
</script>


<button class="btn btn-accent" type="button" on:click={ () => state = 0 }>
	Back {$PlayerID}
</button>

<div>
	Something something something
</div>

<div>
	This is the lobby
</div>

<div class="grid grid-cols-4 gap-4 p-4">
	{#each RoomList as room (room.roomID)}
		<div class="border border-accent p-4 flex flex-col items-center">
			<span class="text-lg p-4">{room.roomName}</span>
			<button class="btn btn-secondary btn-xs" on:click={() => window.requestJoinRoom(room.roomID) } >
				Join room
			</button>
		</div>
	{/each}
</div>


<button class="btn btn-secondary" type="button" on:click={ () => { /*window.getInRoom(roomID);*/ state = 2; } }>
	Go to a room
</button>