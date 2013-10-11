(function ($) {
  window.csc = window.csc || {};

  // the key is the number of columns
  var tileData = {
    1: {order: [0, 2, 4, 6, 8], divideAfter: 0},
    2: {order: [0, 3, 4, 7, 8], divideAfter: 10},
    3: {order: [0, 2, 4, 6, 8], divideAfter: 11},
    4: {order: [0, 2, 5, 8, 10], divideAfter: 10}
  };

  var $filterTip;

  //Browser type    
  $.browser = {};
  $.browser.mozilla = /mozilla/.test(navigator.userAgent.toLowerCase()) && !/webkit/.test(navigator.userAgent.toLowerCase());
  $.browser.webkit = /webkit/.test(navigator.userAgent.toLowerCase());
  $.browser.opera = /opera/.test(navigator.userAgent.toLowerCase());
  $.browser.msie = /msie/.test(navigator.userAgent.toLowerCase());
  
  //Transform prefix
  var prefix = '';
  if($.browser.msie)    prefix = '-ms-';
  if($.browser.webkit)  prefix = '-webkit-';

  //Build tiles layout
  window.csc.home_layout = function home_layout(){
    var $supercontainer = $('#block-system-main').find('.csc-panel-container'),
        $panelLeft = $supercontainer.find('.csc-panel-col-left'),
        $panelRight = $supercontainer.find('.csc-panel-col-right'),
        height =  $(window).height() - $supercontainer.offset().top;
    
    $supercontainer.add($panelLeft).add($panelRight).height(height);
    $panelRight.width($(window).width() - $panelRight.offset().left);

    window.csc.containerHeight = height;

    //Size of container
    var $container = $('#iso-container'),
        $containerOffset = $container.offset(),
        cWidth = $container.width(),
        cHeight = $container.height() + $container.offset().top,
        nCol;
    
    //Number of tiles depending on container width
    if(cWidth >= 1400){
      nCol = 4;
    }else if(cWidth >= 1000){
      nCol = 3;
    }else if(cWidth >= 600){
      nCol = 2;
    }else{
      nCol = 1;
    }

    if( cWidth > 640 ) {
      var mobileRelics = $('#header-mobile-nav');
      if(mobileRelics.is(':visible')) mobileRelics.click();
      $('#header-icons').removeClass('mobile');
    }

    //if (nCol > 1 && cHeight < window.innerHeight) nCol = nCol - 1;
    
    var tWidth =  Math.round(cWidth/nCol);
    if (nCol == 1 && tWidth < 250) tWidth = 250;

    // tile-based responsiveness, adding classes to body based on tile size
    var mediaClass = '';
    if(tWidth > 450) {
      mediaClass = 'x-large';
    } else if(tWidth > 380) {
      mediaClass = 'large';
    } else if(tWidth > 305) {
      mediaClass = 'medium';
    } else {
      mediaClass = 'small';
    }
    $('body').removeClass(function(index, cls){ return (cls.match(/\bmedia\-\S+/g) || []).join(' '); }).addClass('media-' + mediaClass);
    
    //Var to save height of columns
    var tHeight = [];
    for(var i=0; i < nCol; i++) tHeight[i] = 0;

    // ordering tiles according to custom orders
    // TODO: better way to do this
    var $allTiles = $('.isotope-item'),
        $orgTiles = $allTiles.filter('.type-initiatives'),
        $tiles = $allTiles.not('.type-initiatives'),
        tileOrderArray = tileData[nCol].order,
        l = $allTiles.length,
        output = [],
        tileIndex = 0;
        tileOrderIndex = 0;

    //if($allTiles.length - 1 < tileData[nCol].divideAfter) 
      $('.csc-panel-separator').hide();

    for(i = 0; i < l; i++) {
      if($orgTiles.length && i == tileOrderArray[tileOrderIndex]) {
        output.push($orgTiles[tileOrderIndex++]);
      } else {
        output.push($tiles[tileIndex++]);
      }
    }

    $allTiles.parent().append(output);
    // end ordering tiles


    //*** Tiles Width ***//
    i = 0, posX = 0;
    $('.isotope-item').each(function( index ) {
      var $this = $(this);
      if( !$this.hasClass('hide-me') ){         
        $this.css('left', '0px');
        $this.css('top', '0px');
        $this.add($this.find('.iso-text')).css('width', tWidth + 'px');

        posX += tWidth;
        //Reset tiles to next row
        i++;
        if(i == nCol){
          i = 0;
          posX=0;
        }
      }  
    });
    
    //*** Tiles Height ***//
    iHeight = $('.iso-image img').height();
    if(iHeight){
      $('.isotope-item').each(function( index ) {
        if( !$(this).hasClass('hide-me') ){
          $(this).find('.iso-text').css('height', iHeight + 'px');
        }
      });
    }

    //Update Column height and horizontal position
    var sepHeight = 0,
        divideAfter = tileData[nCol].divideAfter;

    var setNextPos = function($el, height, width) {
      var newHeight = height || (tHeight[i] + $el.height()),
          newWidth = (width || posX) + tWidth;

        posX = newWidth;
        tHeight[i] = newHeight;
        i++;
        if(i >= nCol){
          i = 0;
          posX=0;
        }
    };
   
    //*** Tiles Positioning ***//
    var needSeparator = 0; //divideAfter > 0 && divideAfter < $('.isotope-item').length && !$('.isotope').find('.hide-me').length;

    i = 0, posX = 0;
    $('.isotope-item').each(function( index, el ) {
      if(needSeparator) {
        if(index == divideAfter) {
          sepHeight = tHeight[i] + $(this).height();
        } else if (index > divideAfter) {
          posX = 0;
          tHeight[i] = sepHeight + $('.csc-panel-separator').outerHeight();
        }
      }
      var $el = $(el);
      if( !$el.hasClass('hide-me') ){   
        //Move tiles to final position
        $el.css(prefix + 'transform', 'translate('+ posX +'px,'+ tHeight[i] +'px)');
        setNextPos($el);
      }  
    });

    
    //Set containter to highest height
    maxH = 0;
    var containerHeight = 0;
    for(i=0; i < nCol; i++) {
      if (tHeight[i] > maxH) maxH = tHeight[i];
    }
    containerHeight = maxH;

    if(needSeparator && sepHeight) {
      $('.csc-panel-separator').appendTo('#iso-container').css(prefix + 'transform', 'translate(0px, ' + sepHeight + 'px)').show().css('visibility', 'visible');
      containerHeight += $('.csc-panel-separator').height();
    } else {
      $('.csc-panel-separator').hide();
    }

    $container.css('height', containerHeight + 'px');
  };
  
  //Filter function
  function filter(el){
    selector = el.attr('data-filter');
    $('.isotope-item').filter(function(index){
      if( $(this).hasClass(selector) || selector == '*' )
        $(this).removeClass('hide-me');
      else
        $(this).addClass('hide-me');
    });

    window.csc.home_layout();  
  }

  function getFilterText($el) {
    var type = $el.attr('data-filter'),
        txt;

    switch( type ) {
      case 'type-feature':
        txt = 'features'; break;
      case 'type-news':
        txt = 'news'; break;
      case 'type-initiatives':
        txt = 'contexts'; break;
      default:
        txt = 'all';
    }
    return txt;
  }

  function positionFilterTip($el) {
    var offset = $el.offset();

    return $filterTip.css({
      top: offset.top + 5 + 'px',
      left: offset.left - 9 + 'px'
    });
  }

  $(window).load(function() {    
    window.csc.home_layout();
    
    //Filters
    $('#filters a').on('click', function(){
        filter( $(this) );
        return false;
    })
    .on('mouseenter', function(){
      var $this = $(this);
      if(!$filterTip) {
        $filterTip = $('<div id="filter-tip" class="filter-tip">' + getFilterText($this) + '</div>').appendTo('body');
      } else {
        $filterTip.html(getFilterText($this));
      }
      positionFilterTip($this).show();
    })
    .on('mouseleave', function(){
      $filterTip.hide();
    });
  });
  
  //Resize event (only when resize ends)
  var doit;
  $(window).resize(function(){
    clearTimeout(doit);
    doit = setTimeout(window.csc.home_layout, 300);
  });
  
})(jQuery);
