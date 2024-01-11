<script>
	import { Canvas } from 'svelte-canvas';
	import Palette from './detached/Palette.svelte'


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

	let brushcolor = '#000';
	let brushsize = 5;

	const changeBrush = (color, size) => {
		if(context) {
			console.log("Change Brush success");
			context.strokeStyle = brushcolor;
			context.lineWidth = brushsize;
		} else {
			console.log("changeBrush failed")
		}
	}

	// Drawing code
	let canvas;
	$: context = setUp(canvas);
	$: changeBrush(brushcolor, brushsize);

	let start
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
	};
</script>

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
