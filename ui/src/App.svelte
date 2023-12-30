<script>
  // @ts-nocheck
  import SignUp from "./SignUp.svelte";
  import Lobby from "./Lobby.svelte";
  import Clock from "./Clock.svelte";
  import { usernameCheck } from "./store.js";
  import Chat from "./chat.svelte";

  import Game from "./Room/Game.svelte";
  let username;
  let password;
  let error = 0;

  function checkSignIn(username, password) {
    if (username == '1' && password == '1') {
      windowState = 1;
      console.log(windowState)
      $usernameCheck = username;
    } else {
      error = 1;
    }
  }

  function checkSignUp() {
    windowState = 2;
  }
 

  let windowState = 0 ;
  
</script>

<!-- <style>
  /* Add this style block to set the background color */
  body {
    background-color: pink;
  }
</style> -->

{#if windowState == 1}
  <Lobby />
{:else if windowState == 7}
<Chat/>
{:else if windowState == 5}
  <Chat/>
{:else if windowState == 0}
  
  <div class = "myDiv "  >
    <div class="grid items-center h-200 " >
      <!-- <h class = "font-bold pb-10 " style = "font-size: px; color:darkcyan "> Welcome to Gartic Game</h> -->
      <h1 class = "font-sans font-semibold pb-10 text-primary-content" style = "font-size: 55px; "> Sign up</h1>
      
      <h3 class="font-sans font-semibold text-secondary-content" style="font-size: 22px; "> Username </h3>
      <div class = "font-sans centered-input font-semibold "><input bind:value={username} class = "myInput border-4 border-neutral bg-info-content text-primary-content"/></div>
  
      <h3 class="font-sans font-semibold text-secondary" style="font-size: 22px; color:darkcyan"> Password </h3>
      <div class = "font-sans centered-input font-semibold"> <input bind:value={password} class = "myInput border-4 border-neutral bg-info-content text-primary-content"  /></div>
    </div>
    <div >
      <button class = "myButton btn btn-outline bg-accent text-secondary-content "  on:click={() => checkSignIn(username, password)}>
        Play
        <svg xmlns="http://www.w3.org/2000/svg" class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" /></svg>
      </button>
  
      <button class = "myButton btn btn-outline bg-secondary text-secondary-content"  on:click={checkSignUp}>
        Sign Up
        <!-- <svg xmlns="http://www.w3.org/2000/svg" class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" /></svg> -->
      </button>
      <!-- <button class = "myButton btn btn-outline btn-accent" style="background-color:chocolate;color:white" on:click={() => windowState = 5}>
        Chat
        <svg xmlns="http://www.w3.org/2000/svg" class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" /></svg>
      </button> -->
    </div> 
  
 

{#if error == 1}
    <label class = "text-lime-900" style="font-size:15px"> Incorrect account </label>
  {/if}
</div>
{:else}
  <SignUp />
{/if}


<style>
  /* Set the background color for the entire component */
  :global(body) {
    margin: 0;
    /* background-color: rgb(151, 112, 157); */
    background-image: url('./backgr3.png'); 
    background-size: cover;
    background-position: center;
    background-repeat: no-repeat;
  
  }

  /* Style for the "Hello" line */
  .Topic{
    text-align: center;
    padding: 50px; /* Adjust padding as needed */
    font-size: 30px; /* Adjust font size as needed */
    color: white; /* Text color */
  }
  .myDiv {
      width: 700px; /* Set the width of the div */
      height: 400px; /* Set the height of the div */
      background-color: rgb(242, 246, 247); /* Set the background color */
      border: 1px solid #ccc; /* Add a border for better visibility */
    }
    .myInput {
      /* background-color: rgb(102, 88, 105); */
      /* padding: 7px; */
      width: 300px; /* Set the width of the input */
      height: 35px; /* Set the height of the input */
      display: flex;
        justify-content: center;
      /* align-items: center; */
      margin-top: 10px; /* Adjust margin as needed */
      margin: 10px;
      align-items: center;
    }
    .myButton {
    /* position: absolute;
    top: 10px;
    left: 10px;
    padding: 10px; */
    width: 100px;
    height: 50px;
    /* background-color: white; */
    border: 1px solid #ccc;
    cursor: pointer;
  }
  .centered-input {
        display: flex;
        justify-content: center;
        align-items: center;
        /* margin-top: 10px; Adjust margin as needed */
    }
</style>