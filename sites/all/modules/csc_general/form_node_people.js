(function ($) {
  $(document).ready(function () {
    $('#people-node-form').submit(function(e){
      title = $('#edit-field-first-name-und-0-value').val() + ' ';
      if( $('#edit-field-middle-name-und-0-value').val() ) title += $('#edit-field-middle-name-und-0-value').val() + ' ';
      title += $('#edit-field-last-name-und-0-value').val();
      
      $('#edit-title').val(title);
    })
  });
})(jQuery);