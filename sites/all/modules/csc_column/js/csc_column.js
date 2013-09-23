(function ($) {
  $(document).ready(function () {
    //create right column
    $( '#content' ).append( '<div id="csc-right" style="display: none;"><div id="csc-column-top"><h2 id="csc-column-title"></h2><div id="csc-column-close"></div></div><div id="csc-column-content"></div></div>' );
    
    //bind actions to top menu buttons
    $('.top-icons').on("click",function(e){
      title = $(this).attr('alt');
      id = $(this).attr('id');
      
      $('#csc-column-title').html(title);
      var ajax_url;
      switch(id){
        case 'explore-icon':
          ajax_url = 'csc_column/explore';
          break;
        case 'contact-icon':
          ajax_url = 'csc_column/contact';
          break;
        case 'login-icon':
          ajax_url = 'csc_column/login';
          break;
        default:
          ajax_url = 'csc_column/search';
          break;
      }
      
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
