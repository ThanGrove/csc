(function ($) {
  $(document).ready(function () {
    var $overlay = $('<div/>', {class: 'overlay', id: 'teaser-overlay'}).appendTo('body'),
        $tooltip = $('.tooltip').appendTo('body');

    var killMe = function(){
      $overlay.fadeOut();
      $tooltip.removeClass('in');
    };

    $('.csc-teaser-more').click(function(e) {
      $overlay.fadeIn();
      $tooltip.addClass('in');
    });

    $tooltip.on('click', '.close', killMe); 
    $overlay.on('click', killMe); 

  });
})(jQuery);
