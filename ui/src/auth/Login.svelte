<script>
	// @ts-nocheck
	import { PlayerID, UIstate } from '../store/store.ts';
	
	let username;
	let password;
	let wrongPassword = false;

	// Js Call C++
	// window.requestLogin(1, username, password)
	// C++ Call Js
	window.auth_wrongPass = () => { wrongPassword = true; };
	window.auth_toLobby = () => { $UIstate = 1; };
</script>



<div class="w-full max-w-sm lg:max-w-md ">

	<div class="fixed">
		<button class="btn" on:click={window.auth_toLobby}>To Lobby</button>
		<button class="btn" on:click={window.auth_wrongPass}>Wrong pass</button>
	</div>

	<h1 class="text-5xl lg:text-6xl text-neutral pt-24 font-semibold">Sign In {$UIstate}</h1>
	<p class="text-gray-400 mt-1">Sign in to access your account</p>

	<div class="m-7 space-y-6">
		<div>
			<div class="flex justify-between mb-1">
				<!-- svelte-ignore a11y-label-has-associated-control -->
				<label class="text-gray-500 font-semibold">Username</label>
			</div>
			<input bind:value={username} required
				placeholder="Your username" 
				class="w-full input lg:input-lg input-primary text-neutral-content" />
		</div>
		<div>
			<div class="flex justify-between mb-1">
				<label class="text-gray-500 font-semibold">Password</label>
			</div>
			<input 
				bind:value={password} type="password" required
				placeholder="Your Password" 
				class="w-full input lg:input-lg input-primary text-neutral-content"/>
			{#if wrongPassword}
				<span class="text-error">Wrong password</span>
			{/if}
		</div>

		<div class="grid grid-cols-3 gap-2">
				<button 
					on:click={() => window.requestLogin(1, username, password)} class="btn lg:btn-lg btn-primary w-full col-span-2">
					Sign in
				</button>
				<button on:click={() => window.requestLogin(1, username, password)} class="btn lg:btn-lg hover:bg-secondary focus:bg-secondary w-full">
					Play as guest
				</button>
		</div>
		<p class="text-md text-gray-400">Don't have an account yet? 
			<a on:click|preventDefault={()=> $UIstate = 3} href="/" class="text-primary hover:underline focus:underline">Sign up</a>.</p>
	</div>
</div>