<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Custom Clock</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }

        #clock {
            font-size: 2em;
        }
    </style>    
</head>
<body>
    <div id="clock"></div>

    <script>
        function updateClock() {
            const currentTime = new Date();
            const hours = currentTime.getHours();
            const minutes = currentTime.getMinutes();
            const seconds = currentTime.getSeconds();

            const formattedTime = `${padZero(hours)}:${padZero(minutes)}:${padZero(seconds)}`;
            document.getElementById('clock').innerText = formattedTime;
        }

        function padZero(number) {
            return number < 10 ? `0${number}` : number;
        }

        // Set the time you want the clock to start
        const customTime = new Date(); // Current time
        customTime.setHours(12); // Set hours (24-hour format)
        customTime.setMinutes(30); // Set minutes
        customTime.setSeconds(0); // Set seconds

        // Uncomment the line below if you want to set a custom time
        // const currentTime = customTime;

        // Update the clock every second
        setInterval(updateClock, 1000);

        // Initial update
        updateClock();
    </script>
</body>
</html>
