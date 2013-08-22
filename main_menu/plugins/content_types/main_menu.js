(function ($) {
  $(document).ready(function () {
    $('#main-menu > .expanded > a').each(function(){
      $(this).attr('href','#');
      $(this).on("click",function(e){
        $(this).siblings('ul').toggle('fast');
      });
    });
  });
})(jQuery);