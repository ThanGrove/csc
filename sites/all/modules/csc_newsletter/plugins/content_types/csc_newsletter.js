(function ($) {

  $(document).ready(function () {
    $('.mce-button').on("click",function(e){
  	 var f = $(this).closest("form");
     e.preventDefault();
     $( "#dialog-modal" ).dialog({
  		 height: 250,
       width: 370,
  		 modal: true,
       buttons: {
        "Close": function() { $(this).dialog("close");},
        "Accept": function(){
                    if( $('#news-1').prop('checked') ) 
                      $('#mce-group-16045-0').prop('checked', true );
                    else
                      $('#mce-group-16045-0').prop('checked', false);

                    if( $('#modal-form #news-2').prop('checked') ) 
                      $('#mce-group-16045-1').prop('checked', true);
                    else
                      $('#mce-group-16045-1').prop('checked', false);
                      
                    f.submit();
                    $(this).dialog("close");
                  }
       }
  	 });
    });
  });

})(jQuery);