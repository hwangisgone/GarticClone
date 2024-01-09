<script lang="ts">
	import Detached from './Detached.svelte';
	export let brushcolor;
	export let brushsize;

	export let clearCanvas;

	const colors = [
		'#000000',
		'#444444',
		'#F050AE',
		'#F77976',
		'#FFAB00',
		'#FDF148',
		'#FFFFFF',
		'#BBBBBB',
		'#A0E426',
		'#52E3E1',
		'#33A8C7',
		'#9336FD',
	];

	let selected = 0;
</script>

<Detached wStart=0.5 hStart=0.5>
	<div class="w-[50vw] bg-neutral p-4 ">
	<div class="max-w-64 grid grid-cols-6 gap-1 items-center justify-items-center">
		{#each colors as color, i}
		<div class="hover:border-2 border-dashed border-golden h-[5vh]  border-0 p-0 m-0 rounded-xl "
			class:border-2={selected == i}>
			<button style="background-color: {colors[i]}" 
				class="border-black border-2 h-full aspect-square square p-0 rounded-xl "
				on:click={() => { brushcolor = colors[i]; selected = i; console.log(selected, i, selected==i); }}
			>
			</button>
		</div>
		{/each}
	</div>

	<button class="btn btn-xs" on:click={clearCanvas}>
		Clear Canvas
	</button>
</div>
</Detached>

<style>
	.border-golden {
		border-color: #FF9F00;
	}
</style>