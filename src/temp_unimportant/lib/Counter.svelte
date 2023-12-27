<script>
  let count = 0
  const increment = () => {
    count += 1
  }

  window.increment = increment;
</script>

<button on:click={increment}>
  count is {count}
</button>
