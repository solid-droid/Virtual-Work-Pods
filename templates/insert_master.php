<?php

$user='root';
$pass ='';
$db='con_serv';
$db = new mysqli('localhost',$user,$pass,$db) or die("unable to connect");
$key =$_POST['key'];
$val =$_POST['v'];
$sql="INSERT INTO `connect` (`key_dat`, `value_dat`) VALUES ('$key', '$val')";
$db->query($sql) 
   

?>