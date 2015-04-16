<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Install SACS</title>
	<link rel="stylesheet" type="text/css" href="css/install.css">
	<script type="text/javascript" src="js/jquery-2.1.3.min.js"></script>
	<script type="text/javascript" src="js/install.js"></script>
</head>
<body>
	<div class="container">
		<h1>SACS Installation</h1>

		<br><br>
		If you are doing the installation of SACS for the first time, please go <br>
		to /includes and edit psl-config.php file in order to change default MySQL settings<br>
		and avoid future sql errors.
		<br>

		
		<h2>DB Config</h2>
		<div>Done automatically after click Install.</div>

		<form id="detaals" method="post" action="register.php">
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
