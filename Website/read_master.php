<?php
$user='root';
$pass ='';
$db='con_serv'; 
$tag = "check102";
// $tag =$_POST['tag'];
$conn = new mysqli('localhost',$user,$pass,$db) or die("unable to connect");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$result = mysqli_query($conn," SELECT `master` FROM `connect` WHERE `tag`= \"" . $tag . "\"");
    if (!$result) {
        echo "no result";
    }
     else {
         
        if (mysqli_num_rows($result) > 0) {
            while ($r=mysqli_fetch_assoc($result)) 
            {
                       
                echo json_encode($r["master"]);  
                             
            }
        }}
        
?>