<script>
  import { RoomID_Enter, GameSettings} from "./store.js";
    // # Your list of dictionaries

    // let PlayerList = [
    //     {Player: 'A', Point : 0},
    //     {Player: 'B', Point : 0},
    //     {Player: 'C', Point : 20},
    //     {Player: 'D', Point : 40},
    //     {Player: 'E', Point : 15}
    // ]

    function sortByPoints() {
      $GameSettings.PlayerList = $GameSettings.PlayerList.slice().sort((a, b) => b.Point - a.Point);
  }

    // Call the function to sort PlayerList based on "Point"
    sortByPoints();



</script>
<body>

  <div class="rank-container">
    <!-- Display ranks with the highest rank centered -->
    <!-- <div class="rank">2</div> -->
    <div class="rank" >{$GameSettings.PlayerList[2].Username}</div>
    <div class="rank highest-rank">{$GameSettings.PlayerList[0].Username}</div>
    <div class="rank">{$GameSettings.PlayerList[1].Username}</div>
    <!-- <div class="rank">5</div> -->
  </div>
  <div>

  </div>

</body>

<style>
    /* Apply styles to the container */
    .rank-container {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh; /* Set height to full viewport height */
      color:rgb(26, 44, 44);
    }

    /* Styling for each rank */
    .rank {
      font-size: 30px;
      font-weight: bold;
      padding: 10px;
      margin: 0 10px; /* Adjust the margin between ranks */
      color:rgb(26, 44, 44);
    }

    /* Styling for the highest rank */
    .highest-rank {
      background-color: #ffcc00; /* Highlight the highest rank with a background color */
      margin-top: -100px; 
    }
  </style>