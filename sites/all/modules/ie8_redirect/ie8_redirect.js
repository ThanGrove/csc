function ie8_redirect(url){
  if (/MSIE (\d+\.\d+);/.test(navigator.userAgent)){ //test for MSIE x.x;
   var ieversion=new Number(RegExp.$1) // capture x.x portion and store as a number
   if (ieversion <= 8) window.location = url;
  }
}
  