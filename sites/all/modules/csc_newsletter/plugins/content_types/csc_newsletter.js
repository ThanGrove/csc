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
                    if( $('#modal-form input:radio[name=newsletter]:checked').val() == 'low' )
                      f.attr('action', 'http://uvacontemplation.us5.list-manage.com/subscribe/post?u=bb09e07367e52174653ec5969&amp;id=c4f581edd0');
                    else
                      f.attr('action', 'http://uvacontemplation.us5.list-manage.com/subscribe/post?u=bb09e07367e52174653ec5969&amp;id=bee009d669');
                      
                    f.submit();
                    $(this).dialog("close");
                  }
       }
  	 });
    });
  });

})(jQuery);