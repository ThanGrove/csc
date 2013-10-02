(function ($) {

$(window).load(function() {
    //var ratio = 720/960;
    
    //var sw = $('.pane-csc-node-image').width();
    //var sh = Math.round(sw * ratio);
    //$('#csc-node-images').bjqs({
        //'height' : sh,
        //'width' : sw,
        ////'responsive' : true,
        //'automatic' : false,
        //'showmarkers' : false,
        //'animtype' : 'slide'
    //});
  //
    $('#csc-node-images').find('.rslides').responsiveSlides({
      auto: false,
      nav: true,
      pager: false,
      namespace: 'large-btns'
    });
});

})(jQuery);
