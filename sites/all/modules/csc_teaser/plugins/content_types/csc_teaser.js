(function ($) {
  $(document).ready(function () {
    $('.csc-teaser-more').click(function(e) {
      $('#csc-teaser-body').lightbox_me({centered: true});
      e.preventDefault();
    });
   
    $('.close').click(function(e) {
  		$(this).parent().trigger('close');
  	});
  });
})(jQuery);