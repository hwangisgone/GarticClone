# Get all files with names starting with "msg_" recursively
$msgFiles = Get-ChildItem -Path "D:\,DOWNLOADS\NEtworkGame\qt\GarticClone\src\states" -Filter "msg_*" -Recurse

# Iterate through each file and open it
foreach ($file in $msgFiles) {
    Invoke-Item $file.FullName
}