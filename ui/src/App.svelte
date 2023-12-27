<!-- <script>
  import svelteLogo from './assets/svelte.svg'
  import viteLogo from './assets/vite.svg'
  import Counter from './lib/Counter.svelte'

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


  
  let state = 0;
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
  <h1>Vite + Svelte</h1>

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
</style> -->
<script>
// @ts-nocheck


import SignUp from "./SignUp.svelte";
import Lobby from "./Lobby.svelte";
// @ts-nocheck
  //export let state = 0;
  let username;
  let password;
  let error = 0;
  function checkSignIn(username, password){
    if ( username == '1' && password == '1') {
      windowState = 1;
    }
    else{
      error = 1;
    }
  }
  function checkSignUp(){
    windowState = 2;
  }

  let windowState = 0;
</script>

{#if windowState == 1}
  <Lobby />
{:else if windowState == 0}
  <div class="grid items-center h-100 ">
    <h1> Sign up</h1>
    <h3> Username </h3>

    <input bind:value = {username} />
    <h3> Password </h3>
    <input bind:value = {password} />
  </div>
  <div>
    <button on:click={checkSignIn(username, password)}>
      Play
    </button>
  
    <button on:click={checkSignUp}> 
      Sign Up
    </button>
  </div>
  {#if error == 1}
    <label> Incorrect account </label>
  {/if}
  
{:else}
  <SignUp />
{/if}




<style>
	main {
		/* display: grid; */
		/* place-items: center; */
		height: 100%;
		background: url(./wood.svg);
	}
</style>