<script>
	import RoomLayout from './RoomLayout.svelte';
	import { PlayerID, UIstate } from '../store/store.ts';

	// Js Call C++
	// window.requestStart()
	// C++ Call Js

	window.room_toGame = () => { $UIstate = 4 };
</script>

<button class="btn fixed" on:click={() => window.room_toGame()}>Start</button>

<RoomLayout>
	<div slot="draw" class="bg-white h-full text-neutral rounded-xl flex items-center justify-center">
		<div class="text-gray-400 text-3xl">
			Waiting for host to start...
		</div>	
	</div>

	<div slot="interact" class="grid grid-cols-2 h-full">
		<div class="border-r-2 border-primary flex items-center justify-center">
			<button class="btn btn-primary " type="button" on:click={() => window.requestStart()}>
				Start game!
			</button>			
		</div>

		<div class="">
			
		</div>

	</div>
</RoomLayout>