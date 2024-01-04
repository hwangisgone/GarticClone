<script>

    let username = 'Trinh Thuy';
    let messages = [];
    messages.push("Hello");
    messages.push("My name is Thuy");
    messages.push("My name is Thuy");
    messages.push("My name is Thuy");
    messages.push("My name is Thuy");
    messages.push("My name is Thuy");
    messages.push("My name is Thuy");
    let msg;
    function EnterChat(){
        messages.push(msg);
        messages = messages;
    }
</script>
<div class="overflow-y-scroll h-32 ">
  
    {#each messages as mess}
      <div class="chat chat-start">
        <div class="chat-image avatar">
          <div class="w-10 rounded-full">
            <img alt="Tailwind CSS chat bubble component" src="https://daisyui.com/images/stock/photo-1534528741775-53994a69daeb.jpg" />
          </div>
        </div>
        <div class="chat-bubble">{mess}</div>
      </div>
    {/each}
</div>


    <!-- <form > -->
      <input placeholder="Write a message" bind:value={msg}/>
      <button on:click={EnterChat}> Enter</button>
  <!-- </form> -->

<style>
    .ChatBox{
        height:fit-content 50px;
    }
</style>

<!-- <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Scrollable Frame</title>
    <style>
        .scroll-frame {
            width: 300px; /* Set the width of your frame */
            height: 200px; /* Set the height of your frame */
            overflow: auto; /* Add scrollbars when content overflows */
            border: 1px solid #ccc; /* Optional: Add a border for styling */
        }

        /* Optional: Add some content for demonstration purposes */
        .content {
            padding: 10px;
            line-height: 1.5;
        }
    </style>
</head>
<body>
    <div class="scroll-frame">
        <div class="content">
            <h2>Scrollable Frame Content</h2>
            <p>This is some example content inside a scrollable frame. You can add more content here, and scrollbars will appear when the content exceeds the frame dimensions.</p>
            Add your actual content here -->
        <!-- </div>
    </div>
</body>
</html> -->
