(function($) {
  $(function(){
    var map = document.getElementById('map-frame'),
        src = map.src.replace('iwto=A',''),
        wto;

    $(window).resize(function(){
      clearTimeout(wto);
      wto = setTimeout(function() {
        map.src = src;
      }, 300);
    });
  });
})(jQuery);
