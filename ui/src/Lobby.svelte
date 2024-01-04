<!-- <script>
    const array = [
        { id: 1, name: "Room 1", settings: 0 },
        { id: 2, name: "Room 2", settings: 0 },
        { id: 3, name: "Room 3", settings: 0 },
        { id: 4, name: "Final room", settings: 0 }
    ];

</script> -->
<!-- 
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
</div> -->

<!-- <div>header</div>

<div class="overflow-auto">
    roomsize
{#each array as room (room.id) }
    <div>
        <span>{room.name}</span>
        <span>{room.settings}</span>
        <button></button>
    </div>
{/each}
</div> -->
<!-- Make scrollable -->

<!-- <div>footer</div>

<p> Lobby here</p> -->
<!-- <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Resizable Rows</title>
    <style>
        body {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        .row {
            width: 100%;
            height: 100px; /* Default height, you can modify this */
            background-color: #f0f0f0;
            border: 1px solid #ccc;
            display: flex;
            align-items: center;
            justify-content: center;
            margin-bottom: 10px; /* Adjust margin as needed */
        }
    </style>
</head>
<body> -->
    <!-- <body>
        <div class="row"> -->
            <!-- <div class="column" id="row1col1">Row 1, Column 1</div>
            <div class="column" id="row1col2">Row 1, Column 2</div>
            <div class="column" id="row1col3">Row 1, Column 3</div> -->
        <!-- </div>
        <div class="row"> -->
            <!-- <div class="column" id="row2col1">Row 2, Column 1</div>
            <div class="column" id="row2col2">Row 2, Column 2</div>
            <div class="column" id="row2col3">Row 2, Column 3</div> -->
        <!-- </div>
        <div class="row"> -->
            <!-- <div class="column" id="row3col1">Row 3, Column 1</div>
            <div class="column" id="row3col2">Row 3, Column 2</div>
            <div class="column" id="row3col3">Row 3, Column 3</div> -->
        <!-- </div>
    </body> -->



<!-- <script>
    import App from "./App.svelte"
    import Room from "./Room.svelte"
    let windowState = 0;

    function Back(){
        windowState = 1;
    }
</script>
{#if windowState == 1}
    <Room />
{:else}
<div>
    <div class = "title">
        <div>
            <button class = "back" on:click={Back}> Back </button>
        </div>
        <span class = "gTitle">
            <h2> Các phòng </h2>
        </span>
    </div>

    <div class = "content of room">
        <div>
            <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">
                <li><button on:click={Back}>Item 1</button></li>
                <li><button on:click={Back}>Item 2</button></li>
                <li><button on:click={Back}>Item 3</button></li>
                <li><button on:click={Back}>Item 4</button></li>
                <li><button on:click={Back}>Item 5</button></li>
            </ul>
        </div>
        <div>
            <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">        
                <li><button on:click={Back}>Item 6</button></li>
                <li><button on:click={Back}>Item 7</button></li>
                <li><button on:click={Back}>Item 8</button></li>  
                <li><button on:click={Back}>Item 9</button></li>
                <li><button on:click={Back}>Item 10</button></li>   
            </ul>
        </div>
        <div>
            <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">        
                <li><button on:click={Back}>Item 11</button></li>
                <li><button on:click={Back}>Item 12</button></li>
                <li><button on:click={Back}>Item 13</button></li>  
                <li><button on:click={Back}>Item 14</button></li>
                <li><button on:click={Back}>Item 15</button></li>   
            </ul>
        </div>
        <div>
            <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">        
                <li><button on:click={Back}>Item 16</button></li>
                <li><button on:click={Back}>Item 17</button></li>
                <li><button on:click={Back}>Item 18</button></li>  
                <li><button on:click={Back}>Item 19</button></li>
                <li><button on:click={Back}>Item 20 </button></li>   
            </ul>
        </div>
    </div>
</div>
{/if}
 -->


 <script>
    import App from "./App.svelte"
    import Room from "./Room.svelte"

    let windowState = 0;

    function Back() {
        windowState = 1;
    }
</script>

{#if windowState == 1}
    <Room />
{:else}
    <div>
        <div class="title">
            <div>
                <button class="back" on:click={Back}> Back </button>
            </div>
            <span class="gTitle">
                <h2> Các phòng </h2>
            </span>
        </div>

        <div class="content of room">
            <div>
                <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">
                    {#each Array.from({ length: 5 }, (_, i) => i + 1) as roomNumber}
                        <li>
                            <button on:click={Back} class="room-button">
                                <div>{roomNumber}</div>
                                <div>Players: 0</div>
                            </button>
                        </li>
                    {/each}
                </ul>
            </div>
            <div>
                <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">
                    {#each Array.from({ length: 5 }, (_, i) => i + 6) as roomNumber}
                        <li>
                            <button on:click={Back} class="room-button">
                                <div>{roomNumber}</div>
                                <div>Players: 0</div>
                            </button>
                        </li>
                    {/each}
                </ul>
            </div>
            <div>
                <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">
                    {#each Array.from({ length: 5 }, (_, i) => i + 11) as roomNumber}
                        <li>
                            <button on:click={Back} class="room-button">
                                <div>{roomNumber}</div>
                                <div>Players: 0</div>
                            </button>
                        </li>
                    {/each}
                </ul>
            </div>
            <div>
                <ul class="menu menu-horizontal lg:menu-horizontal bg-base-200 rounded-box">
                    {#each Array.from({ length: 5 }, (_, i) => i + 16) as roomNumber}
                        <li>
                            <button on:click={Back} class="room-button">
                                <div>{roomNumber} Hello </div>
                                <div>Players: 0</div>
                            </button>
                        </li>
                    {/each}
                </ul>
            </div>
        </div>
    </div>
{/if}

<style>
    .room-button {
        width: 100px;
        height: 100px;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        margin: 10px;
        border: 1px solid #ccc;
        background-color: #FFCCFF;
        cursor: pointer;
    }
</style>

