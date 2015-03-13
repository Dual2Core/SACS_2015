<?php

// Check if vars are set
if(isset($_GET['user']) && isset($_GET['message']) && isset($_GET['target']))
	include_once '/includes/sacs_conv_connect.php';
else
	die("Received not enough data!");

// Get vars
$user = $_GET['user'];
$message = $_GET['message'];
$target = $_GET['target'];

// Determine conversation table name
if($user < $target)
	$convname = $user.$target;
else
	$convname = $target.$user;

// Check if conversation table exists
$res = $sacs_conv->query('SHOW TABLES LIKE "'.$convname.'"');
switch($res->num_rows)
{	
	case false:
		$sacs_conv->query('CREATE TABLE `'.$convname.'` (
		`user` varchar(32) NOT NULL,
  		`message` varchar(255) NOT NULL,
  		`time` timestamp(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  		`readstate` BOOLEAN
		) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;');
	case true:
	$sacs_conv->query('INSERT INTO '.$convname.' (user,message) VALUES ("'.$user.'","'.$message.'")');
}

?>