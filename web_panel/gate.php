<?php

// Check if vars are set
if(isset($_GET['user']))
{
	include_once 'includes/sacs_conv_connect.php';
	include_once 'includes/sacs_db_connect.php';
}
else
	die('Received not enough data!');

// Get vars
$user = $_GET['user'];
$sacs_db->query('DELETE FROM `users` WHERE `lastseen`< NOW() - INTERVAL 10 SECOND');

// Show online users
if(isset($_GET['whoisonline']))
{
	$result = $sacs_db->query('SELECT `nickname` FROM users ORDER BY `nickname` ASC');
	if($result->num_rows)
	{
		for ($i=0; $i < $result->num_rows; $i++) 
		{ 
			$result->data_seek($i);
			$nick = $result->fetch_assoc();
			$nick = $nick['nickname'];
			echo $nick."\n";
		}
	}
	goto end;
}


// Maintain user presence
if(isset($_GET['keepalive']))
{
	$result = $sacs_db->query('SELECT nickname FROM users WHERE nickname="'.$user.'"');
	$client_ip = $_SERVER['REMOTE_ADDR'];
	if(!$result->num_rows)
	{
		$sacs_db->query('INSERT INTO `users`(`nickname`, `client_ip`) VALUES ("'.$user.'", "'.$client_ip.'")');
	}
	else
	{
		$sacs_db->query('UPDATE `users` SET `lastseen`=CURRENT_TIMESTAMP(0) WHERE nickname="'.$user.'"');
	}
	die("Done!");
}

// Check for unread messages
$res_tables = $sacs_conv->query('SHOW TABLES LIKE "%'.$user.'%"'); // Possible to get whole data, 
if($res_tables->num_rows) // If there are results 				   // it gives nothing as long as it is encrypted
	for($s = 0; $s < $res_tables->num_rows; $s++)
	{
		$res_tables->data_seek($s);
		$convname = $res_tables->fetch_assoc(); // Fetch the result
		$convname = $convname['Tables_in_sacs_conv (%'.$user.'%)']; // Convert resource to string
		
		
		// Return only messages with unread state
		$res_messages = $sacs_conv->query('SELECT message,time FROM '.$convname.' WHERE user!="'.$user.'" AND readstate=0');
		if($res_messages->num_rows) // If there are results
		{
			echo $convname."\n";
			for ($t = 0; $t < $res_messages->num_rows; $t++) 
			{ 
				$res_messages->data_seek($t);
				$message = $res_messages->fetch_assoc(); // Fetch the result
				$date = $message['time'];
				$message = $message['message'];
				echo $date."\n".$message."\n";
			}
		}
	}
	end:
?>