<script>
	import { UIstate } from '../store/store.ts';

	import Register from './Register.svelte';

	let notitext = "";

	function wrongPass() {
		notitext = "Wrong password";
		setTimeout(function() {
			notitext = "";
		}, 5000);
	}
	function toLobby() {
		$UIstate = 1;
	}
	
	window.auth_toLobby = toLobby;	// Assign 1;
	window.auth_wrongPass = wrongPass;

	let loginState = 0;
	// 0 for default login
	// 1 for register

	let username = "";
	let password = "";
</script>

<div class="h-screen flex flex-col gap-4 items-center justify-center">

	{#if loginState == 0}
		<div>You are trying to login</div>
		<!-- on:click makes the button do something everytime the button is clicked -->

		<h3> Username {notitext} </h3>
		<input type="text" class="input input-bordered" bind:value = {username} />
		<h3> Password</h3>
		<input type="password" class="input input-bordered" bind:value = {password} />

		<span>{notitext}</span>

		<button class="btn btn-primary" type="button" on:click={() => window.requestLogin(1, username, password)}>
			Login (go to Lobby)
		</button>

		<!-- Change loginState with an inline function "(argument) => do something" -->
		<!-- This is a javascript feature -->
		<button class="btn btn-accent btn-xs" type="button" on:click={() => loginState = 1 }>
			Don't have an account?
		</button>

	{:else if loginState == 1}
		<!-- Make sure the name is the same in both .svelte files (components) -->
		<Register bind:loginState />	
	{/if}

</div>