<?php
$user='root';
$pass ='';
$db='con_serv'; 
$key =$_POST['key'];

$conn = new mysqli('localhost',$user,$pass,$db) or die("unable to connect");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);

}

$result = mysqli_query($conn," SELECT `value_dat` FROM `connect` WHERE `key_dat`= \"" . $key . "\"");

    if (!$result) {
        echo "no result";
    }
     else {
         
        if (mysqli_num_rows($result) > 0) {
            while ($r=mysqli_fetch_assoc($result)) 
            {
                       
                echo json_encode($r["value_dat"]);  
                             
            }
        }}
        
?>