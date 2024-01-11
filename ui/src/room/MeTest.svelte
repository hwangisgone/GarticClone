<script>
  import { Canvas } from 'svelte-canvas';
  import Balls from './Balls.svelte';

  let balls = [
    { color: 'tomato', x: 0.5, y: 0.333 },
    { color: 'goldenrod', x: 0.333, y: 0.625 },
    { color: 'mediumturquoise', x: 0.667, y: 0.625 },
  ];

  const reorder = (color) => {
    balls = balls
      .filter((c) => c.color !== color)
      .concat(balls.filter((c) => c.color === color));
  };


  const setUp = (context) => {
    if (canvas) {
      context.strokeStyle = '#000'
    }

    console.log("Triggerd setUp");
    return canvas?.getContext();
  }
  // Drawing code
  let canvas;
  $: context = canvas?.getContext();

  $: if(context) {

    context.strokeStyle = '#000'  
  }

  let start
  let t, l;
  let isDrawing = false;

  const handleStart = ({ offsetX: x, offsetY: y }) => { 
    // if(color === background) {
    //   context.clearRect(0, 0, width, height)
    // } else {
      isDrawing = true
      start = { x, y }
    // }
  };
  
  const handleEnd = () => { isDrawing = false };
  const handleMove = ({ offsetX: x1, offsetY: y1 }) => {
    if(!isDrawing) return;
    
    const { x, y } = start;
    context.beginPath();
    context.moveTo(x, y);
    context.lineTo(x1, y1);
    context.stroke();
    
    start = { x: x1, y: y1 };
  };
</script>

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
>
  {#each balls as { color, x, y } (color)}
    <Balls
      {color}
      {x}
      {y}
      on:mousedown={() => reorder(color)}
      on:touchstart={() => reorder(color)}
    />
  {/each}
</Canvas>
