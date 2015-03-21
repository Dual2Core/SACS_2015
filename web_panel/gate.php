<?php

// Check if vars are set
if(isset($_GET['user']))
	include_once 'includes/sacs_conv_connect.php';
else
	die('Received not enough data!');

// Get vars
$user = $_GET['user'];

// Check for table names
$res_tables = $sacs_conv->query('SHOW TABLES LIKE "%'.$user.'%"'); // Possible to get whole data, 
if($res_tables->num_rows) // If there are results 				   // it gives nothing as long as it is encrypted
	for($s = 0; $s < $res_tables->num_rows; $s++)
	{
		$res_tables->data_seek($s);
		$convname = $res_tables->fetch_assoc(); // Fetch the result
		$convname = $convname['Tables_in_sacs_conv (%'.$user.'%)']; // Convert resource to string
		
		
		// Return only messages with unread state
		$res_messages = $sacs_conv->query('SELECT message FROM '.$convname.' WHERE user!="'.$user.'" AND readstate=0');
		if($res_messages->num_rows) // If there are results
		{
			echo '>'.$convname."<br>"; // DELETE '<br>' <-- ONLY FOR DEVELOPMENT
			for ($t = 0; $t < $res_messages->num_rows; $t++) 
			{ 
				$res_messages->data_seek($t);
				$message = $res_messages->fetch_assoc(); // Fetch the result
				$message = $message['message'];
				echo ':'.$message."<br>"; // DELETE '<br>' <-- ONLY FOR DEVELOPMENT
			}
		}
	}


?>