$('#hashit').click(function(){
    	$(this).attr("class","ui loading button");
    	formhash(this.form, this.form.password);
    });