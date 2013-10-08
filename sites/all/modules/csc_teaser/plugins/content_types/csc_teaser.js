(function ($) {
  $(document).ready(function () {
    var $teaser = $('.csc-teaser-div'),
        $body = $('.tooltip'),
        $readMore = $teaser.find('.csc-teaser-more'),
        $readLess = $body.find('.csc-teaser-less'),
        bodyShowing = 0;

    $readMore.on('click', function(){
      $teaser.hide();
      $body.show();
    });

    $readLess.on('click', function(){
      $body.hide();
      $teaser.show();
    });


    // pop-up code
    //var $overlay = $('<div/>', {class: 'overlay', id: 'teaser-overlay'}).appendTo('body'),
        //$tooltip = $('.tooltip').appendTo('body');

    //var killMe = function(){
      //$overlay.fadeOut();
      //$tooltip.removeClass('in');
    //};

    //$('.csc-teaser-more').click(function(e) {
      //$overlay.fadeIn();
      //$tooltip.addClass('in');
    //});

    //$tooltip.on('click', '.close', killMe); 
    //$overlay.on('click', killMe); 

  });
})(jQuery);
