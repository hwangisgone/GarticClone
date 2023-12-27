<script>
	import Register from './Register.svelte';

	// "export let state" allows everything outside to bind to this value
	export let state = 0;
	// 0 is Login
	// 1 is Lobby
	// 2 is Room

	function toLobby() {
		state = 1;
	}

	let loginState = 0;
	// 0 for default login
	// 1 for register
</script>

<div class="h-screen flex flex-col gap-4 items-center justify-center">

	{#if loginState == 0}
		<div>You are trying to login</div>
		<!-- on:click makes the button do something everytime the button is clicked -->
		<button class="btn btn-primary" type="button" on:click={toLobby}>
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