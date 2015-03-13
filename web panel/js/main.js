// jQuery dependency
$(document).ready(function() {

	// Stats live update 5s
	function UpdateStats(){
		$('#stats').load("includes/stats.php");
		$('#onlinecount').css('color', 'green');
	}
	UpdateStats();
	setInterval(UpdateStats, 5000);
	// --------------------

	// Content load
	function LoadBasicOverviewPage(){
		$('#acontent').load("../includes/content/overview.php");
	}
	function LoadUsersPage(){
		$('#acontent').load("../includes/content/users.php");
	}
	function LoadConnectionsPage(){
		$('#acontent').load("../includes/content/connections.php");
	}
	LoadBasicOverviewPage();
	$('#basic_overview').click(LoadBasicOverviewPage);
	$('#users').click(LoadUsersPage);
	$('#connections').click(LoadConnectionsPage);

});