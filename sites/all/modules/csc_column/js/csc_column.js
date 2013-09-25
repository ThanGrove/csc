(function ($) {
  $(document).ready(function () {
    //create right column
    $( '#content' ).append( '<div id="csc-right" style="display: none;"><div id="csc-column-top"><h2 id="csc-column-title"></h2><div id="csc-column-close"></div></div><div id="csc-column-content"></div></div>' );
    
    //bind actions to top menu buttons
    $('#header-icons').find('a').on("click",function(e){
      if(~this.className.indexOf('noxhr')) {
        return true;
      }
      event.preventDefault();
      title = $(this).attr('alt');
      
      $('#csc-column-title').html(title);
      var ajax_url = this.href;
      
      $.ajax({
         url: ajax_url,
         success: function(res){
          $('#csc-column-content').html(res);
         }
      });
      
      $('#csc-right').show('fast');
      return false;
      
    });
    
    //bind action to close buttons
    $('#csc-column-close').on("click",function(e){
      $('#csc-right').hide('fast');
      return false; 
    });    
    
  });
})(jQuery);
