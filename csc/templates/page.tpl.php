<header>
<div id="header-logo"><a href="/"><?php echo print_image('logo.gif', 453, 50, "Comtemplative Scinces Center");?></a></div>
<div id="header-icons">
  <ul>
    <li><a href="#"><?php echo print_image('explore_icon.png', 48, 48, "Explore CSC", 'class="top-icons" id="explore-icon"');?></a></li>
    <li><a href="#"><?php echo print_image('contact_icon.png', 48, 48, "Contact", 'class="top-icons" id="contact-icon"');?></a></li>
    <li><a href="#"><?php echo print_image('login_icon.png', 48, 48, "Login", 'class="top-icons" id="login-icon"');?></a></li>
    <li><a href="#"><?php echo print_image('search.png', 48, 48, "Search", 'class="top-icons" id="search-icon"');?></a></li>
  </ul>
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
