(function ($) {
  var menuToggle = 0,
      $content, $header, $cols;

  window.csc = window.csc || {};

  window.csc.toggleMenu = function(){
    var css, clsFn;
    
    if( menuToggle ) {
      css =  {left: '0px'}; 
      menuToggle = 0;
      if(!window.csc.menuToggleListener)
        window.csc.menuToggleListener = (menuToggleListener)();
    } else {
      css = {left: '150px', top: '0px'};
      menuToggle = 1;
      $('html,body').animate({scrollTop:0}, 0);
    }
    $('.csc-panel-col-left, .csc-3col-col-fixed').toggle();
    $('#header-icons').toggle();
    $('.csc-panel-col-right').css(css);

    if(!menuToggle && window.csc.home_layout) {
      window.csc.home_layout();
    }
  };

  window.csc.maximize = function(){
    var h, w;
    if($cols.length) {
      w = $(window).width();
      if(w > 640) {
        h = $(window).height() - $header.outerHeight();
        $content.add($cols).height(h);
      } else {
        $content.add($cols).height('');
      }
    }
  };

  var wto;
  var menuToggleListener = function(){
    $(window).resize(function(){
      clearTimeout(wto);
      wto = setTimeout(function() {
        var ww = $(window).width();
        if((!menuToggle && ww > 640) || menuToggle && ww < 641) {
          window.csc.toggleMenu();
        } 
      }, 150);
    });
  };


  $(document).ready(function () {

    if(!$content) {
      $content = $('#content');
      $header = $('header');
      $cols = $('.csc-3col-col-fluid');
      window.csc.maximize();
    }

    //Bind expand/contract effect to menus
    $('#main-menu > .expanded > a').each(function(){
      $(this).attr('href','#');
      $(this).on("click",function(e){
        $parent = $(this).parent();
        $(this).siblings('ul').slideToggle('fast');
        if( $parent.hasClass('expanded') ){
          $('#main-menu').find('.contracted').removeClass('contracted').addClass('expanded').find('ul').slideUp('fast');
          $parent.removeClass('expanded');
          $parent.addClass('contracted');
        }else{
          $parent.removeClass('contracted');
          $parent.addClass('expanded');
        }
        return false;
      });
    });

    //Auto expand for active sub-menus
    var url = location.href.split('/').slice(3).join('/'),
        $el = $('#main-menu').find('a[href*=\"' + url + '\"]'),
        $li;

    if($el.length == 1) {
      $li = $el.closest('li.expanded');
      if ($li.length) {
        $li.removeClass('expanded').addClass('contracted');
        $li.closest('ul').show();
        $el.addClass('active');
        
        var lid = $el.parent().attr('id');
        $.cookie('expanded', lid); 
      }
    }
    
    //if mlid of a give li is saved, expand that branch
    if($.cookie('expanded')){
      elid = $.cookie('expanded');
      $el = $('#' + elid);
      $parent = $el.parent().parent();
      $parent.removeClass('expanded').addClass('contracted');

      $el.addClass('active');
      $el.children('a').addClass('active');
    }
    
    //Reset cookie
    $("#m-1008 > a, #anchor-about, #header-logo > a").bind('click', function(e){
      $.removeCookie('expanded');
    });

    $(window).resize(function(){
      window.csc.maximize();
    });

    // mobile menu
    $('#header-mobile-nav').click(window.csc.toggleMenu);
  });
})(jQuery);
