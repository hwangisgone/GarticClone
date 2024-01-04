<script>
<<<<<<< Updated upstream
	import Login from './auth/Login.svelte'
	import Lobby from './lobby/Lobby.svelte';
	import Room from './room/Room.svelte';
=======
  // @ts-nocheck
  import SignUp from "./SignUp.svelte";
  import Lobby from "./Lobby.svelte";
  import Clock from "./Clock.svelte";
  import Chat from "./chat.svelte";
  import Game from "./room/Game.svelte";
  import { PlayerID, UIstate } from './store/store.ts';
    import { sineIn } from "svelte/easing";
  
  // TODO: Move this to Login.svelte?
  let username;
  let password;
  // let error = 0;
>>>>>>> Stashed changes

	import { PlayerID, UIstate } from './store/store.ts';
</script>

<<<<<<< Updated upstream


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
=======
{#if $UIstate == 1}
<Lobby/>
{:else if $UIstate == 3}
<SignUp/>
{:else if $UIstate == 6}
<Chat/>
{:else if $UIstate == 2}
<Game/>
{:else if $UIstate == 0}
 <div class="myDiv">
  <div class="container mx-auto">
      <div class="max-w-md mx-auto my-10">
          <div class="text-center">
              <h1 class="Topic text-neutral-content font-semibold">Sign In</h1>
              <!-- <p class="text-gray-500 dark:text-gray-400">Sign in to access your account</p> -->
          </div>
          <div class="m-7">
              <form action="">
                  <div class="mb-6">
                      <div class="flex justify-between mb-2">
                        <!-- svelte-ignore a11y-label-has-associated-control -->
                        <label class="text-sm text-neutral font-semibold">USER NAME</label>
                      </div>
                      <input bind:value={username} placeholder="Username" class="w-full px-3 py-2 placeholder-gray-300 border border-gray-300 rounded-md focus:outline-none focus:ring focus:ring-indigo-100 focus:border-indigo-300 dark:bg-gray-700 dark:text-white dark:placeholder-gray-500 dark:border-gray-600 dark:focus:ring-gray-900 dark:focus:border-gray-500" />
                  </div>
                  <div class="mb-6">
                      <div class="flex justify-between mb-2">
                          <label class="text-sm text-neutral font-semibold" style = "font-size:15px">PASSWORD</label>
                           <!-- <a href="#!" class="text-sm text-gray-400 focus:outline-none focus:text-indigo-500 hover:text-indigo-500 dark:hover:text-indigo-300">Forgot password?</a> -->
                      </div>
                      <input bind:value={password} placeholder="Your Password" class="w-full px-3 py-2 placeholder-gray-300 border border-gray-300 rounded-md focus:outline-none focus:ring focus:ring-indigo-100 focus:border-indigo-300 dark:bg-gray-700 dark:text-white dark:placeholder-gray-500 dark:border-gray-600 dark:focus:ring-gray-900 dark:focus:border-gray-500" />
                  </div>
                  <div class="mb-6">
                      <button on:click={checkSignIn(username, password)} type="button" class="w-full px-3 py-4 text-white bg-indigo-500 rounded-md focus:bg-indigo-600 focus:outline-none">Sign in</button>
                  </div>
                  <p class="text-sm text-center text-gray-400" style = "font-size:16px">Don&#x27;t have an account yet? <a href="#!" class="text-indigo-400 focus:outline-none focus:underline focus:text-indigo-500 dark:focus:border-indigo-800">Sign up</a>.</p>
              </form>
          </div>
      </div>
  </div>
</div>


>>>>>>> Stashed changes
{/if}



<<<<<<< Updated upstream


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

=======
>>>>>>> Stashed changes
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