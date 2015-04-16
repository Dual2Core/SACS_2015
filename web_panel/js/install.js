function MakeInstall(){
	var sa_user = $('[name="sa_user"]').val();
	var sa_passw = $('[name="sa_passw"]').val();
	var sa_passw2 = $('[name="sa_passw2"]').val();
	$('.log').load('../install2.php',0,
		function(){
			var status = $('#status').val();
			if(status = "success")
			{
				alert("Configuring MySQL completed!");
				var details = $('#detaals');
				details.submit();
			}
			else
			if(status = "error")
			{
				alert("Error occured!");
			}
	});
	
	
}