(function ($) {
  var menuToggle = 0;

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
    //Bind expand/contract effect to menus
    $('#main-menu > .expanded > a').each(function(){
      $(this).attr('href','#');
      $(this).on("click",function(e){
        $parent = $(this).parent();
        $(this).siblings('ul').toggle('fast');
        if( $parent.hasClass('expanded') ){
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
      }
    }
    //Search if current page is a sub-menu
    
    //$('#main-menu .leaf a').each(function(index){
      //found = ~url.indexOf(this.href);
      //if(found){
        //$el = $(this);
        //var $ul = $el.closest('ul');  //UL of current anchor
        ////it is a sub-menu
        //if($ul.attr('id') != 'main-menu'){
          //var li = ul.parent();
          //if(li.hasClass('expanded')){
            //li.removeClass('expanded');
            //li.addClass('contracted');
          //}
        //}  
        //return false;
      //}
    //});
    
   
    // mobile menu
    $('#header-mobile-nav').click(window.csc.toggleMenu);
  });
})(jQuery);
