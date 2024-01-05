<script>
	// @ts-nocheck
	import { PlayerID, UIstate } from '../store/store.ts';
	
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


				<div class="text-center ">
						<h1 class="text-5xl text-neutral pt-24 font-semibold">Sign In</h1>
						<!-- <p class="text-gray-500 dark:text-gray-400">Sign in to access your account</p> -->
				</div>
				<div class="m-7">
					<div class="mb-6">
						<div class="flex justify-between mb-2">
							<!-- svelte-ignore a11y-label-has-associated-control -->
							<label class="text-sm text-neutral font-semibold">USER NAME</label>
						</div>
						<input bind:value={username} placeholder="Username" class="w-full input input-primary" />
					</div>
					<div class="mb-6">
							<div class="flex justify-between mb-2">
									<label class="text-sm text-neutral font-semibold" style = "font-size:15px">PASSWORD</label>
									 <!-- <a href="#!" class="text-sm text-gray-400 focus:outline-none focus:text-indigo-500 hover:text-indigo-500 dark:hover:text-indigo-300">Forgot password?</a> -->
							</div>
							<input bind:value={password} placeholder="Your Password" class="w-full input input-primary"/>
					</div>
					<div class="mb-6">
							<button on:click={checkSignIn(username, password)} class="w-full btn btn-primary">Sign in</button>
					</div>
					<p class="text-sm text-center text-gray-400" style = "font-size:16px">Don&#x27;t have an account yet? <a on:click={()=> $UIstate = 3}  href="#!" class="text-primary focus:underline ">Sign up</a>.</p>
				</div>
