<script>
    // @ts-nocheck
        import {UIstate} from "./store/store.ts";
        import App from "./App.svelte";
        let firstname = "";
        let lastname = ""; 
        let username = "";
        let password = "";
        let email = "";
    
       // let windowState = 0;
        function createAcc(email, username){
            if( email == '1' && username == '1'){
               state = 1;
               
    
            } else {
                state = 2;
    
            }
            
        }
       function goBack(){
            windowState = 1;
       }
        let state = 0;
    
    
    </script>
    
    {#if $UIstate == 1}
        <App />
    {:else}
    <div>
        <h1> Sign Up </h1>
        <h3> First Name</h3>
        <input bind:value = {firstname} />
        <h3> Last Name</h3>
        <input bind:value = {lastname} />
        <h3> Email</h3>
        <input bind:value = {email} />
        <h3> User Name</h3>
        <input bind:value = {username} />
        <h3> Password </h3>
        <input bind:value = {password} />
    </div>  
    
    <button on:click={createAcc(username, email)}> Create </button>
    <button on:click={() => $UIstate = 1}> Back</button>
    <div>
        {#if state == 1}
      <label> Create new account successfully! </label>
    {:else if state == 2 }
     <label> Cannot create new account, duplicate email / username</label>
    {/if}
    </div>
    
    {/if}