<script>
// @ts-nocheck

	import { onMount } from "svelte";

	import { drawSettings } from '../store/store.ts';

	export function clear() {
		context.clearRect(0, 0, canvas.width, canvas.height);
	}

	let canvas;
	let context;

	function get_coords(e) {
		const { clientX, clientY } = e;
		const { left, top } = canvas.getBoundingClientRect();
		const x = clientX - left;
		const y = clientY - top;
		return { x, y };
	}

	function draw_circle(x, y, size, clr) {
			context.fillStyle = clr;
			context.beginPath();
			context.arc(x, y, size, 0, 2 * Math.PI);
			context.fill();
	}
	window.ingame_draw_circle = draw_circle;	// Assign 4

	onMount(() => {
		context = canvas.getContext('2d');

		function resize() {
			canvas.width = canvas.parentElement.clientWidth - 32;
			canvas.height = canvas.parentElement.clientHeight - 32;
		}

		window.canvas = canvas;

		window.addEventListener('resize', resize);

		setTimeout(() => {
			resize();
		}, 1000);
		

		return () => {
			window.removeEventListener('resize', resize);
		};
	});

	let holding;
	let canvasDisabled = false;
</script>



<canvas
	width="15" height="10"
	bind:this={canvas}
	on:pointerdown={(e) => {
		holding = true;
	}}
	on:pointerleave={() => {
		holding = false;
	}}
	on:pointerup={() => {
		holding = false;
	}}
	on:pointermove={(e) => {
		if (holding && !canvasDisabled) {
			const coords = get_coords(e);
			draw_circle(coords.x, coords.y, $drawSettings.size, $drawSettings.color);
			window.requestDraw(coords.x, coords.y, $drawSettings.size, $drawSettings.color);
		}

		// if (e.buttons === 1) {
		// 	e.preventDefault();

		// 	context.strokeStyle = color;
		// 	context.lineWidth = size;
		// 	context.lineCap = 'round';
		// 	context.beginPath();
		// 	context.moveTo(previous.x, previous.y);
		// 	context.lineTo(coords.x, coords.y);
		// 	context.stroke();
		// }
	}}
/>

<!-- {#if previous}
	<div
		class="preview"
		style="--color: {color}; --size: {size}px; --x: {previous.x}px; --y: {previous.y}px" 
	/>
{/if} -->

<!-- <style>
	canvas {
		position: absolute;
		left: 0;
		top: 0;
		width: 100%;
		height: 100%;
	}

	.preview {
		position: absolute;
		left: var(--x);
		top: var(--y);
		width: var(--size);
		height: var(--size);
		transform: translate(-50%, -50%);
		background: var(--color);
		border-radius: 50%;
		opacity: 0.5;
		pointer-events: none;
	}
</style> -->