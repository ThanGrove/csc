<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Important Dates'),
  'description' => t('Show Important Dates'),
  'category' => t('CSC Plugins Half'),
  'render callback' => 'csc_important_dates_render',
  'admin info' => 'csc_important_dates_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_important_dates_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Important Dates';
    $block->content = 'Show Important Dates';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_important_dates_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = 'Important Facts';

  //Load block Important Dates
  $output = csc_readblock_get(1);

  $block->content = '<div class="add-scroll csc-important-dates-scroll">' . $output . "</div>";

  return $block;
}
