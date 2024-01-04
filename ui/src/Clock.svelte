<!-- <script>
	import { time, elapsed } from './store.js';

	const formatter = new Intl.DateTimeFormat(
		'en',
		{
			hour12: true,
			hour: 'numeric',
			minute: '2-digit',
			second: '2-digit'
		}
	);
</script>

<h1>The time is {formatter.format($time)}</h1>

<p>
	This page has been open for
	{$elapsed}
	{$elapsed === 1 ? 'second' : 'seconds'}
</p> -->
<script>
	import { onMount } from "svelte";
	let countdown = 10;
	let timer;
	$: {
	  if (countdown === 0) {
		if (timer) {
		  clearInterval(timer);
		  timer = null;
		}
	  }
	}
	onMount(() => {
	  timer = setInterval(() => {
		countdown -= 1;
	  }, 1000);
	});
  </script>
  
  <style>
	span {
	  display: flex;
	  justify-content: center;
	  align-items: center;
	  width: 100%;
	  height: 100vh;
	  font-family: "Courier New", Courier, monospace;
	  font-size: 100px;
	}
  </style>
  
  <span>{countdown}</span>