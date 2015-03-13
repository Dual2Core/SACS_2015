<!-- Header -->
<?php
include_once 'db_connect.php';
include_once 'functions.php';

if (login_check($mysqli) == false)
	header("Location: ../noauth.php");
?>
<div class="ui segment menu">
	<div class="header item">
		<?php echo "SACS Control Panel";?>
	</div>
	<a class="item" href="../main.php">
		Basic Overview
	</a>
	<a class="item">
		Users
	</a>
	<a class="item">
		Connections
	</a>

	<div class="right menu">
		<div class="item">
			Welcome <?php echo $_SESSION['username']; ?>!
		</div>
		<a class="item" href="includes/logout.php">
			Log Out
		</a>
	</div>
</div>