(function($){
    $(window).load(function(){
        $(".add-scroll").mCustomScrollbar();
        
      	$("#calendar-link").fancybox({
      		ajax : {
      		    type	: "GET"
      		}
      	});

        //$('.csc-directors-wrapper').on('click', function(){
          //$(this).find('a').click();
        //});
    });          
})(jQuery);
