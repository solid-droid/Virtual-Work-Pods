<?php

$user='root';
$pass ='';
$db='con_serv';
$db = new mysqli('localhost',$user,$pass,$db) or die("unable to connect");
$tag =$_POST['tag'];
$master =$_POST['token'];
$sql="INSERT INTO `connect` (`tag`, `master`) VALUES ('$tag', '$master')";
$db->query($sql) 
   

?>