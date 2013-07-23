(function ($) {

var overDone = false;

function attachRollovers(){
  $('.rollover').each(function(i){
    $(this).mouseover(function() {
      if(!overDone){
        var src1= $(this).attr('src'); // initial src
        var newSrc = src1.substring(0, src1.lastIndexOf('.')); // let's get file name without extension
        $(this).attr('src', newSrc+ '_over.' + /[^.]+$/.exec(src1)); //last part is for extension
        overDone = true;
      }
    });
    $(this).mouseout(function() {
      var src = $(this).attr("src").replace("_over", "");
      $(this).attr("src", src);
      overDone = false;
    });
  
  });
}

function rollover_preload(){
  var imgs = new Array();
  $('.rollover').each(function(i){
    var src1= $(this).attr('src'); // initial src
    var newSrc = src1.substring(0, src1.lastIndexOf('.')); // let's get file name without extension
    newSrc = newSrc+ '_over.' + /[^.]+$/.exec(src1);  //Adds "_over." and extension
    imgs[i] = new Image();
    imgs[i].src = newSrc; 
  });  
}

$(window).load(function () {
  attachRollovers();
  rollover_preload();
});

})(jQuery);
