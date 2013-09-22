(function ($) {
  $(document).ready(function () {
    $('#filters a').click(function(){
      var selector = $(this).attr('data-filter');
      $('#iso-container').isotope({ filter: selector });
      return false;
    });
  });
})(jQuery);