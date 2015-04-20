<?php
include_once 'includes/psl-config.php';

$success = 'Success!<br><input type="hidden" id="status" value="success">';
function error($msg){
	die('Error: '.$msg.'<br><input type="hidden" id="status" value="error">');
}


$mysqli = mysqli_connect(HOST, USER, PASSWORD);
// Connection test
if (!$mysqli) {
    error(mysqli_connect_error());
}

// Create databases
if(!mysqli_query($mysqli,"CREATE DATABASE `sacs_conv`") ||
	!mysqli_query($mysqli,"CREATE DATABASE `sacs_db`") ||
	!mysqli_query($mysqli,"CREATE DATABASE `secure_login`"))
	error("Could not create Databases! Maybe it already exist?");
else
	echo "[+] Databases created successfully!<br>";

// Create tables
if(!mysqli_select_db($mysqli,"sacs_db"))
	error("Could not select 'sacs_db'!");
if(!mysqli_query($mysqli,'CREATE TABLE IF NOT EXISTS `users` (
`id` int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `nickname` varchar(32) DEFAULT NULL,
  `client_ip` varchar(15) DEFAULT NULL,
  `lastseen` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;'))
	error("Could not create table 'users'!");

if(!mysqli_select_db($mysqli,"secure_login"))
	error("Could not select 'secure_login'!");
if(!mysqli_query($mysqli,'CREATE TABLE `secure_login`.`members` (
    `id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `username` VARCHAR(30) NOT NULL,
    `email` VARCHAR(50) NOT NULL,
    `password` CHAR(128) NOT NULL,
    `salt` CHAR(128) NOT NULL 
) ENGINE = InnoDB;'))
	error("Could not create table 'members'!");
if(!mysqli_query($mysqli,'CREATE TABLE `secure_login`.`login_attempts` (
    `user_id` INT(11) NOT NULL,
    `time` VARCHAR(30) NOT NULL
) ENGINE=InnoDB'))
	error("Could not create table 'login_attempts'!");
else
	echo "[+] Tables created successfully!";
	
echo $success;
mysqli_close($mysqli);
?>