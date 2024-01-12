<script>
	import { GameSettings, UIstate, PlayerID } from "../store/store.ts";


	// Js Call C++
	// window.requestDisconnect()
</script>

<div class="container mx-auto">

<div class="h-[5vh] text-3xl">
	<button class="btn btn-accent" type="button" on:click={() => {
		$UIstate = 2;
		window.requestDisconnect(); 
	}}>
		Exit
	</button>
</div>

<div class="grid grid-cols-4">
  <div class="h-[95vh] p-4 pr-0 col-span-1 flex flex-col">
	<div class="flex-1 overflow-y-auto border-4 border-primary rounded-xl p-4 bg-white ">
		<div class="text-neutral h-full divide-y-2 ">
			{#each $GameSettings.PlayerList as player}
				<div class="flex flex-col text-center w-full p-2">
					<strong class="text-primary brightness-75">{player.name} #{player.id}
						{#if player.id == $PlayerID}(You){/if}
					</strong>
					
					<span>{player.point} points</span>
				</div>
			{/each}
		</div>
	</div>
<!-- 	<div class="h-1/4">
	  <p>Fixed-size content at the bottom</p>
	</div> -->
  </div>
  <div class="h-[95vh] p-4 col-span-3 flex flex-col gap-4">
		<div class="h-3/4">
			<slot name="draw">
				Canvas
			</slot>
		</div>
		<div class="h-1/4 border-4 border-primary rounded-xl bg-white text-neutral">
			<slot name="interact">
				Chatting here			
			</slot>
		</div>
  </div>
</div>

</div>

