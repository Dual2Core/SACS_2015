<!-- Stats -->
<?php
include_once 'db_connect.php';
include_once 'functions.php';
sec_session_start(); // Important when using AJAX, otherwise comment this line
if (login_check($mysqli) == false)
	header("Location: ../noauth.php");
?>

<?php
include_once 'sacs_db_connect.php';
echo rand(2,80)."<br>";
echo "Stats:<br>";
$res = $sacs_db->query("SELECT COUNT(*) FROM users WHERE UNIX_TIMESTAMP(CURRENT_TIMESTAMP)-UNIX_TIMESTAMP(`lastseen`) < 30");
$res = $res->fetch_assoc();
echo "Users online:<span id='onlinecount'>".$res['COUNT(*)'].'</span>';
echo "<br>Users(last 24h):";
echo "<br>Users(last 2days):";
echo "<br><br>All users:";
?>