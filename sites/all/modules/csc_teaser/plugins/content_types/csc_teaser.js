(function ($) {
  $(document).ready(function () {
    var $overlay = $('<div/>', {class: 'overlay', id: 'teaser-overlay'}).appendTo('body');
    $('.csc-teaser-more').click(function(e) {
      $overlay.fadeIn();
      $('.tooltip').addClass('in');
      //$('#csc-teaser-body').lightbox_me({
        //appearEffect: 'show',
        //lightboxSpeed: 0,
        //overlaySpeed: 0,
        //className: 'in'
      //});
    });
   
    $overlay.click(function(){
      $(this).fadeOut();
      $('.tooltip').removeClass('in');
    });
  });
})(jQuery);
