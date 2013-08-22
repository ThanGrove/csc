(function ($) {

  //Build tiles layout
  function home_layout(){
    //Size of container
    var cWidth = $('#iso-container').width();
    
    //tile width
    tWidth = $('.isotope-item').width();
    //number of tiles per width
    var nTiles = Math.round(cWidth/tWidth);
    
    //Var to save height of columns
    var tHeight = new Array();
    for(var i=0; i < nTiles; i++) tHeight[i] = 0;
    
    console.log('Container: ' + cWidth + ', Tile: ' + tWidth + ', No Tiles: ' + nTiles);
   
    var i = 0; posX = 0
    $('.isotope-item').each(function( index ) {
      if( !$(this).hasClass('hide-me') ){
        //Get smallest column
        minimumY = tHeight[0];   //Initialize min value
        shortCol = 0;
        for (var j=0; j < nTiles; j++) {
          if( tHeight[j] < minimumY ) { minimumY = tHeight[j]; shortCol = j; }
        }    
      
        $(this).css('left', '0px');
        $(this).css('top', '0px');
        
        //Set tiles width. Make adjustment for last tile due to rounded issues
        var w = (i == nTiles - 1) ? $('#iso-container').width() - posX: tWidth;
        $(this).css('width', w + 'px');
        //Move tiles to final position
        $(this).css('transform', 'translate('+ posX +'px,'+ tHeight[i] +'px)');
  
        //Update Column height and horizontal position
        tHeight[i] += $(this).height();
        posX += tWidth;
        
        //Reset tiles to next row
        i++;
        if(i == nTiles){
          i = 0;
          posX=0;
        }
      }  
    });
    
    //Set containter to highest height
    maxH = 0;
    for(var i=0; i < nTiles; i++) if (tHeight[i] > maxH) maxH = tHeight[i];
    $('#iso-container').css('height', maxH + 'px');
  }
  
  //Filter function
  function filter(el){
    selector = el.attr('data-filter');
    $('.isotope-item').filter(function(index){
      if( $(this).hasClass(selector) || selector == '*' )
        $(this).removeClass('hide-me');
      else
        $(this).addClass('hide-me');
    });

    home_layout();  
  }

  $(window).load(function() {    
    home_layout();
    
    //Filters
    $('#filters a').on('click', function(){
        filter( $(this) );
        return false;
    });        
  });
  
  //Resize event (only when resize ends)
  var doit;
  $(window).resize(function(){
    clearTimeout(doit);
    doit = setTimeout(home_layout, 100);
  });
  
})(jQuery);