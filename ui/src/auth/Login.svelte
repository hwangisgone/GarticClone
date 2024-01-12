<script>
	// @ts-nocheck
	import { UIstate } from '../store/store.ts';
	import InputContainer from './InputContainer.svelte';
	
	let username;
	let password;
	let wrongPassword = false;

	// Js Call C++
	// window.requestLogin(1, username, password)
	// C++ Call Js
	window.auth_wrongPass = () => { wrongPassword = true; };
	window.auth_toLobby = () => { $UIstate = 2; };
</script>



<div class="w-full max-w-sm lg:max-w-md ">

<!-- 	<div class="fixed">
		<button class="btn" on:click={window.auth_toLobby}>To Lobby</button>
		<button class="btn" on:click={window.auth_wrongPass}>Wrong pass</button>
	</div> -->

	<h1 class="text-5xl lg:text-6xl text-neutral pt-24 font-semibold">Sign In</h1>
	<p class="text-gray-400 mt-1">Sign in to access your account</p>

	<div class="m-7 space-y-2 md:space-y-4">
		<InputContainer labelText="Username">
			<input bind:value={username} required
			placeholder="Your username" 
			class="w-full input lg:input-lg input-primary text-neutral-content" />		
		</InputContainer>
		<InputContainer labelText="Password">
			<input 
				bind:value={password} type="password" required
				placeholder="Your Password" 
				class="w-full input lg:input-lg input-primary text-neutral-content"/>

				<span class="label py-1 px-3 text-error">
					{#if wrongPassword}
						Wrong password
					{/if} &nbsp;
				</span>
		</InputContainer>

		<div class="grid grid-cols-3 gap-2">
				<button 
					on:click={() => window.requestLogin(0, username, password)} class="btn lg:btn-lg btn-primary w-full col-span-3">
					Sign in
				</button>
<!-- 				<button on:click={() => window.requestLogin(1, username, password)} class="btn lg:btn-lg hover:bg-secondary focus:bg-secondary w-full">
					Play as guest
				</button> -->
		</div>
		<p class="text-md text-gray-400">Don't have an account yet? 
			<a on:click|preventDefault={()=> $UIstate = 1} href="/" class="text-primary hover:underline focus:underline">Sign up</a>.</p>
	</div>
</div>