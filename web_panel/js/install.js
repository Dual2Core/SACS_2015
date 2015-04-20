function MakeInstall(){
	$('.log').load('../install2.php',0,
		function(){
			var status = $('#status').val();
			if(status == "success")
			{
				alert("Configuring MySQL completed!");
				var details = $('#detaals');
				details.submit();
			}
			else
			if(status == "error")
			{
				alert("Error occured!");
			}
	});
	
	
}