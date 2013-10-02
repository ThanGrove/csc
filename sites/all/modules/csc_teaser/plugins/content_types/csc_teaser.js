(function ($) {
  $(document).ready(function () {
    var $overlay = $('<div/>', {class: 'overlay', id: 'teaser-overlay'}).appendTo('body'),
        $tooltip = $('.tooltip').appendTo('body');

    $('.csc-teaser-more').click(function(e) {
      $overlay.fadeIn();
      $tooltip.addClass('in');
    });
   
    $overlay.click(function(){
      $(this).fadeOut();
      $tooltip.removeClass('in');
    });
  });
})(jQuery);
