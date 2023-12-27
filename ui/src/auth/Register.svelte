<script>
	export let loginState = 1;
	// 0 for default login
	// 1 for register
</script>

<!-- on:click makes the button execute a function everytime the button is clicked -->
<button class="btn btn-accent" type="button" on:click={() => loginState = 0 }>
	Back
</button>

<div>Register your account here </div>

