<header>
<div id="header-logo"><?php echo print_image('logo.gif', 453, 50, "Comtemplative Scinces Center");?></div>
<div id="header-icons">
  <?php echo print_image('search_icon.png', 35, 35, "Search");?>
  <a href="#"><?php echo print_image('uva_icon.png', 35, 35, "Uva Rotunda", 'class="rollover"');?></a>
</div>
</header>
<?php if ($messages): ?>
  <div id="messages"><div class="section clearfix">
    <?php print $messages; ?>
  </div></div> <!-- /.section, /#messages -->
<?php endif; ?>

<div id="content" class="column"><div class="section">
  <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
  <a id="main-content"></a>
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h1 class="title" id="page-title">
      <?php print $title; ?>
    </h1>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($tabs): ?>
    <div class="tabs">
      <?php print render($tabs); ?>
    </div>
  <?php endif; ?>
  <?php print render($page['help']); ?>
  <?php if ($action_links): ?>
    <ul class="action-links">
      <?php print render($action_links); ?>
    </ul>
  <?php endif; ?>
  <?php print render($page['content']); ?>
  <?php print $feed_icons; ?>

</div></div> <!-- /.section, /#content -->
<script>
(function ($) {
  $('#main-menu > .expanded > a').each(function(){
    $(this).attr('href','#');
    $(this).on("click",function(e){
      $(this).siblings('ul').toggle('fast');
    });
  });
})(jQuery);
</script>
