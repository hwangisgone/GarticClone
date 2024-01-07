<script>
	export let labelText = "Label text"
</script>

<div><label>
	<span class="label text-gray-500 font-semibold">{labelText}</span>
	<slot />
</label></div>