<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';
 
sec_session_start();
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Securely Authenticated Communication System</title>
        <link rel="stylesheet" href="includes/dist/semantic.min.css">
        <link rel="stylesheet" href="css/main.css" />
        <script type="text/javascript" src="includes/dist/semantic.min.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
        <script type="text/javascript" src="js/main.js"></script>
<?php
if (login_check($mysqli) == true){
// PHP User Interface Includes
	$ertsdifug=324;
}else{
	header("Location: ../noauth.php");
}
?>
    </head>
    

    <body>
    <div class="container">
    	<div class="ui top segment menu">
			<div class="header item">
				<?php echo "SACS Control Panel";?>
			</div>
			<a class="item" id="basic_overview">
				Basic Overview
			</a>
			<a class="item" id="users">
				Users
			</a>
			<a class="item" id="connections">
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
    	

    	<div class="ui segment pushable">
		    <div class="ui visible inverted left vertical sidebar menu">
		      <div class="item" id="stats">
		        jQuery AJAX is not working!		        
		      </div>  
		    </div>
		    
		    <div class="pusher">
		      <div class="ui basic segment" id="acontent">
		        Column 2		       
		      </div>
		    </div>
  		</div>

  	</div>

    </body>
</html>