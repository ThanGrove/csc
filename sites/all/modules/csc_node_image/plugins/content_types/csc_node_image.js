(function ($) {

$(window).load(function() {
    var ratio = 360/480;
    
    var sw = $('.pane-csc-node-image').width();
    var sh = Math.round(sw * ratio);
    $('#csc-node-images').bjqs({
        'height' : sh,
        'width' : sw,
        'responsive' : true,
        'automatic' : false,
        'showmarkers' : false
    });
});

})(jQuery);