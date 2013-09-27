<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Test Widget'),
  'description' => t('Test custom functions'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_test_render',
  'admin info' => 'csc_test_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_test_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Test Widget';
    $block->content = 'Test Custom functions';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_test_render($subtype, $conf, $panel_args, $context = NULL) {
  global $csc_var;

  //Nothing to do
  if(!isset($GLOBALS['view_content_type']) or $GLOBALS['view_content_type'] == '' ) return;
  
  $output = "Content type:" . $GLOBALS['view_content_type'];

  $block = new stdClass();
  $block->title = 'Test Widget';
  $block->content = $output;

  return $block;
}
