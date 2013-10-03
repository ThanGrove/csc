<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Grants Buttons'),
  'description' => t('Show Grants Buttons'),
  'category' => t('CSC Plugins Half'),
  'render callback' => 'csc_grants_buttons_render',
  'admin info' => 'csc_grants_buttons_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_grants_buttons_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Grant Buttons';
    $block->content = 'Show Grant Buttons';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_grants_buttons_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = '';
  
  //Load block Grants Buttons
  $block = block_load('block', 2);
  $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $output = render($render_array);
  
  $block->content = '<div class="add-scroll csc-grants-buttons-scroll">' . $output . "</div>";

  return $block;
}
