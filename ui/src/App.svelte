<script>
  // @ts-nocheck
  import SignUp from "./SignUp.svelte";
  import Lobby from "./Lobby.svelte";
  import Clock from "./Clock.svelte";
  import Chat from "./chat.svelte";
  import Room from "./room/Game.svelte";
  import { PlayerID, UIstate } from './store/store.ts';
    import { sineIn } from "svelte/easing";
    import LeaderBoard from "./LeaderBoard.svelte";
  
  // TODO: Move this to Login.svelte?
  let username;
  let password;
  // let error = 0;

  function checkSignIn(username, password) {
    if (username == '1' && password == '1') {
      $UIstate = 1;
     // console.log(windowState)
      //$usernameCheck = username;
    } else {
      error = 1;
    }
  }
</script>
{#if $UIstate == 3}
<SignUp/>
{:else if $UIstate == 1}
<Lobby/>
{:else if $UIstate == 5}
<LeaderBoard/>
{:else if $UIstate == 4}
<Room/>
{:else if $UIstate == 0 }
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
                      <button on:click={checkSignIn(username, password)} class="w-full px-3 py-4 text-white bg-indigo-500 rounded-md focus:bg-indigo-600 focus:outline-none">Sign in</button>
                  </div>
                  <p class="text-sm text-center text-gray-400" style = "font-size:16px">Don&#x27;t have an account yet? <a on:click={()=> $UIstate = 3}  href="#!" class="text-indigo-400 focus:outline-none focus:underline focus:text-indigo-500 dark:focus:border-indigo-800">Sign up</a>.</p>
              </form>
          </div>
      </div>
  </div>
</div>
{/if}

<style>
  /* Set the background color for the entire component */
  :global(body) {
    margin: 0;

    background-image: url('./backgr3.png'); 
    background-size: cover;
    background-position: center;
    background-repeat: no-repeat;
  
  }

  /* Style for the "Hello" line */
  .Topic{
    text-align: center;
    padding: 50px; /* Adjust padding as needed */
    font-size: 50px; /* Adjust font size as needed */
    
    align-items: center;
  }
  .myDiv {
      width: 900px; /* Set the width of the div */
      height: 700px; /* Set the height of the div */
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