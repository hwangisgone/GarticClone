<script lang="ts">
	export let wStart = 0.5;
	export let hStart = 0.8;

	let moving = false;
	$: left = window.innerWidth * wStart;
	$: top = window.innerHeight * hStart;

	function onMouseDown() {
		moving = true;
	}
	
	function onMouseMove(e) {
		if (moving) {
			left += e.movementX * 0.8;
			top += e.movementY * 0.8;
		}
	}
	
	function onMouseUp() {
		moving = false;
	}
</script>

<svelte:window on:mouseup={onMouseUp} on:mouseleave={onMouseUp} on:mousemove={onMouseMove} />

<div on:mousedown={onMouseDown}
	class="card card-compact absolute overflow-hidden z-10 border border-primary drag-mouse"
	role="application"
	style="left: {left}px; top: {top}px;"> 
	<slot />
</div>


<style>
	.drag-mouse {
		user-select: none;
		cursor: move;
	}
</style>