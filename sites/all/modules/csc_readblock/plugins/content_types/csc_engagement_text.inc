<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Engagement Intro Text'),
  'description' => t('Show text on Engagement nodes'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_engagement_text_render',
  'admin info' => 'csc_engagement_text_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_engagement_text_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Engagement Intro Text';
    $block->content = 'Show Engagement Text';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_engagement_text_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = '';
  
  //Load block Learning Text
  $output = csc_readblock_get(6);
  
  $block->content = '<div class="csc-engagement-intro">' . $output . "</div>";

  return $block;
}
