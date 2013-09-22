<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Bottom Links'),
  'description' => t('Show links to social networks'),
  'category' => t('CSC Plugins'),
  'render callback' => 'bottom_links_render',
  'admin info' => 'bottom_links_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function bottom_links_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Bottom Links';
    $block->content = 'Show a block with links to social networks';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function bottom_links_render($subtype, $conf, $panel_args, $context = NULL) {
  $path = drupal_get_path('module', 'bottom_links');
  drupal_add_css($path .'/plugins/content_types/bottom_links.css');
  
  $block = new stdClass();

  // initial content is blank
  $block->title = 'Bottom Links';
  $block->content = '
  <div class="bottom-links">
  <a href="#"><img src="/'.$path.'/images/twitter_icon.gif" width="19" height="19" alt="Twitter"></a>
  <a href="#"><img src="/'.$path.'/images/facebook_icon.gif" width="19" height="19" alt="Facebook"></a>
  <a href="#"><img src="/'.$path.'/images/user_icon.gif" width="19" height="19" alt="Profile"></a>
  </div>';

  return $block;
}
