(function ($) {
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
    var el = false;
    var url = String(location);
    //Search if current page is a sub-menu
    $('ul.menu > li > a').each(function(index){
      hr = $(this).attr('href'); console.log(hr);
      found = url.search(hr);
      if(found > 0){
        el = $(this);
      }  
    });
    
    if(el){
      var ul = el.parent().parent();  //UL of current anchor
      //it is a sub-menu
      if(ul.attr('id') != 'main-menu'){
        var li = ul.parent();
        if(li.hasClass('expanded')){
          li.removeClass('expanded');
          li.addClass('contracted');
        }
      }
    }    
    
  });
})(jQuery);