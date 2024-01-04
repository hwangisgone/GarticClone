<script>
	import Login from './auth/Login.svelte'
	import Lobby from './lobby/Lobby.svelte';
	import Room from './room/Room.svelte';

	import { PlayerID, UIstate } from './store/store.ts';
</script>



{#if $UIstate == 0}
	<!-- "bind:state" allows Login to change the state (of App) -->
	<!-- <input type="number" bind:value={$PlayerID} > -->
	<Login />  
{:else if $UIstate == 1}
	<Lobby />
{:else if $UIstate == 2}
	<Room />
{:else}
	<!-- LOADING SCREEN -->
{/if}





<!-- 
<script>
	import svelteLogo from './assets/svelte.svg'
	import viteLogo from './assets/vite.svg'
	import Counter from './lib/Counter.svelte'
	import "./app.css";

	let num = 0;
	let num2 = 0;

	function getFucked() {
		window.fuckaround().then(result => {
			num = result.count;
		});
	}

	function fuckSomething() {
		window.fuckaround().then(result => {
			num2 = result.count;
		});
	}

	let resole = 0;

	function callme() {
		window.compute(num, num2).then(result => {
			resole = result;
		})
	}
</script>

<main>
	<div>
		<a href="https://vitejs.dev" target="_blank" rel="noreferrer">
			<img src={viteLogo} class="logo" alt="Vite Logo" />
		</a>
		<a href="https://svelte.dev" target="_blank" rel="noreferrer">
			<img src={svelteLogo} class="logo svelte" alt="Svelte Logo" />
		</a>
	</div>
	<button class="btn btn-primary">Vite + Svelte</button>

	<div class="card">
		<Counter />
	</div>

	<p>
		Check out <a href="https://github.com/sveltejs/kit#readme" target="_blank" rel="noreferrer">SvelteKit</a>, the official Svelte app framework powered by Vite!
	</p>

	<p class="read-the-docs">
		Click on the Vite and Svelte logos to learn more 
	</p>
	<span>{num} x {num2} = {resole}</span>
	<button on:click={getFucked}>Whoah there</button>
	<button on:click={fuckSomething}>Hey no</button>
	<button on:click={callme}>Calculate</button>
</main>

<style>
	.logo {
		height: 6em;
		padding: 1.5em;
		will-change: filter;
		transition: filter 300ms;
	}
	.logo:hover {
		filter: drop-shadow(0 0 2em #646cffaa);
	}
	.logo.svelte:hover {
		filter: drop-shadow(0 0 2em #ff3e00aa);
	}
	.read-the-docs {
		color: #888;
	}
</style>
 -->