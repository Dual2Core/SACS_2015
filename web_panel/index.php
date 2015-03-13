<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';
 
sec_session_start();
 
if (login_check($mysqli) == true) {
    $logged = 'in';
} else {
    $logged = 'out';
}
?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <title>SACS - Login</title>
        <script type="text/JavaScript" src="js/sha512.js"></script> 
        <script type="text/JavaScript" src="js/forms.js"></script> 
        <link rel="stylesheet" href="includes/dist/semantic.min.css">
        <script type="text/javascript" src="includes/dist/semantic.min.js"></script>
        <script type="text/javascript" src="js/jquery-2.1.3.min.js"></script>
        <link rel="stylesheet" href="css/authstyles.css">
    </head>
    <body>
        <?php
        if (isset($_GET['error'])) {
            echo '<div class="ui warning message">
  <i class="close icon"></i>
  <div class="header">
    Authentication process failed!
  </div>
  We have your private browser fingerprint, reconsider trying again.
</div>';
        }
        ?> 
       
        <div class="ui one column stackable center aligned page grid">
	        <div class="column twelve wide midel">
	    
	        <form action="includes/process_login.php" method="post" name="login_form">
	        

		        <h1>Secure Auth</h1>
		      
                
                <div class="ui left icon input">    
		           	<input type="text" name="email"/>
		           	<i class="at icon"></i>
		        </div>
		        <br>

		        
		      	<div class="ui left icon input">
		            <input type="password" name="password" id="password"/>
		            <i class="privacy icon"></i>
				</div>
		        <br>

		        <button class="ui button" id="hashit">
		        Login
			    </button>
			    
	        </form>

<?php
        if (login_check($mysqli) == true) {
                        echo '<p>Currently logged ' . $logged . ' as ' . htmlentities($_SESSION['username']) . '.</p>';
 
            echo '<p>Do you want to change user? <a href="includes/logout.php">Log out</a>.</p>';
        } else {
                        echo '<p>Currently logged ' . $logged . '.</p>';
                        echo "<p>If you don't have a login, please <a href='register.php'>register</a></p>";
                }
?>      
			</div>
		</div>
<script>
$('#hashit').click(function(){
    $(this).attr("class","ui loading button");
   	formhash(this.form, this.form.password);
});
$('i.close').click(function(){
    $('div.warning').slideUp("fast");
});
</script>

    </body>
</html>