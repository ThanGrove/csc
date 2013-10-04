(function ($) {
  $(document).ready(function () {
    var $header_icons = $('#header-icons'),
        $wedge = $('<img src="sites/all/themes/csc/images/wedge.png" class="wedge"/>').appendTo('body'),
        active_el;

    var getRightOffset = function(el) {
      var $el = $(el);
      return $(window).width() - ($el.offset().left + $el.outerWidth()) + 26;
    };

    //create right column
    $( '#content' ).append( '<div id="csc-right"><div id="csc-column-top"><h2 id="csc-column-title"></h2><div id="csc-column-close">x</div></div><div id="csc-column-content"></div></div>' );

    //bind actions to top menu buttons
    $header_icons.find('a').on("click",function(event){
      var cls = this.className;

      if(~cls.indexOf('noxhr'))
        return true;

      event.preventDefault();

      if(!~cls.indexOf('active')) {
        this.className += ' active';
        if(active_el)
          $(active_el).removeClass('active');
        active_el = this;

        var rght = getRightOffset(this);
        $wedge.css('right', rght + 'px').show();

        title = $(this).attr('alt');

        $('#csc-column-title').html(title);
        var ajax_url = this.href;

        $.ajax({
          url: ajax_url,
          success: function(res){
            $('#csc-column-content').addClass('csc-' + title.replace(/ /g, '-').toLowerCase()).html(res);
          }
        });

        $('#csc-right').addClass('in');
      }
    });


    
    //bind action to close buttons
    $('#csc-column-close').on("click",function(e){
      $('#csc-right').removeClass('in');
      $(active_el).removeClass('active');
      active_el = null;
      $wedge.hide();
      return false; 
    });    
    
  });
})(jQuery);
