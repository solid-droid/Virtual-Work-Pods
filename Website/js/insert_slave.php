<?php

$user='root';
$pass ='';
$db='con_serv';

$db = new mysqli('localhost',$user,$pass,$db) or die("unable to connect");
// $tag =$_POST['tag'];
// $slave =$_POST['slave'];
$tag="ccc";
$slave="test_case";
$sql="UPDATE `connect` SET  `slave` = \' . $slave . \' WHERE `tag` = \' . $tag . \'"" ;
$db->query($sql) 
   

?>