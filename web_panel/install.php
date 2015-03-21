<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Install SACS</title>
	<script type="text/javascript" src="js/sha512.js"></script>
	<script type="text/javascript" src="js/forms.js"></script>
	<link rel="stylesheet" type="text/css" href="css/install.css">
	<script type="text/javascript" src="js/jquery-2.1.3.min.js"></script>
	<script type="text/javascript" src="js/install.js"></script>
</head>
<body>
	<div class="container">
		<h1>SACS Installation</h1>

		<br><br>

		<h2>DB Config</h2>
		Username:<input type="text" name="db_user" size="20"><br><br>
		Password:<input type="text" name="db_passw" size="20"><br><br>
		Re-Passw:<input type="text" name="db_passw2" size="20"><br><br>
		
		<form method="post" action="register.php">
		<h2>Server Admin</h2>
		Username:<input type="text" name="sa_user" size="20"><br><br>
		Password:<input type="text" name="sa_passw" size="20"><br><br>
		Re-Passw:<input type="text" name="sa_passw2" size="20"><br><br>
		<input type="button" id="inst" value="Install" onclick="MakeInstall();">
		</form>


		<br><br>
		Logs goes here:<br>
		<div class="log">
			
		</div>
	</div>
</body>
</html>