<script>
	import { Canvas } from 'svelte-canvas';
	import Palette from './detached/Palette.svelte'

	import { ThisRound } from "../store/store.ts";

	const setUp = (canvas) => {
		const context = canvas?.getContext();

		if (context) {
			context.strokeStyle = brushcolor;
			context.lineWidth = brushsize;

			console.log("Triggeredd setUp. Brush size: ", brushsize);
		} else {
			console.log("setUp Failed");
		}

		return context;
	}

	let brushcolor = '#000000';
	let brushsize = 5;

	const changeBrush = (color, size) => {
		if(context) {
			console.log("Change Brush success");
			context.strokeStyle = color;
			context.lineWidth = size;
		} else {
			console.log("changeBrush failed")
		}
	}

	// Drawing code
	let canvas;
	$: context = setUp(canvas);
	$: changeBrush(brushcolor, brushsize);

	let start;
	let t, l;
	let isDrawing = false;

	const clearCanvas = () => { 
		const { width, height } = canvas.getCanvas();
		context.clearRect(0, 0, width, height); 
		console.log("FUCK");
	}

	const handleStart = ({ offsetX: x, offsetY: y }) => { 
		// if(color === background) {
		//   
		// } else {
			isDrawing = true
			start = { x, y }
			window.requestDraw(x, y, brushcolor, brushsize, 1);
		// }
	};
	
	const handleEnd = () => { isDrawing = false };
	const handleMove = ({ offsetX: x1, offsetY: y1 }) => {
		if(!isDrawing) return;
		
		const { x, y } = start;
		context.lineCap = 'round';
    	context.beginPath();
		context.moveTo(x, y);
		context.lineTo(x1, y1);
		context.stroke();
		
		start = { x: x1, y: y1 };

		window.requestDraw(x, y, brushcolor, brushsize, 0);
	};

	let timer;
	window.game_draw = (x, y, clr, size, start) => {
		changeBrush(clr, size);
		if (start == 1) {
			handleStart({ offsetX: x, offsetY: y});
		} else {
			handleMove({ offsetX: x, offsetY: y});
		}
		// isDrawing = true;
		// timer = setInterval(() => {
	  	// 	countdown -= 1;
		// }, 100);
	}
</script>


{#if $ThisRound.role == 1}
<Palette bind:brushcolor bind:brushsize {clearCanvas}/>
<Canvas bind:this={canvas}
	on:mousedown={handleStart}  
	on:mouseup={handleEnd}
	on:mouseleave={handleEnd}
	on:mousemove={handleMove}

	on:touchstart={e => {
		const { clientX, clientY } = e.touches[0]
		handleStart({
			offsetX: clientX - l,
			offsetY: clientY - t
		})
	}}
	on:touchmove={e => {
		const { clientX, clientY } = e.touches[0]
		handleMove({
			offsetX: clientX - l,
			offsetY: clientY - t
		})
	}}
	on:touchend={handleEnd}
/>
{:else}
<Canvas bind:this={canvas}/>
{/if}
