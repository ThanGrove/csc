<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Research Intro Text'),
  'description' => t('Show text on Research nodes'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_research_text_render',
  'admin info' => 'csc_research_text_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_research_text_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Research Intro Text';
    $block->content = 'Show Research Text';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_research_text_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = '';
  
  //Load block Research Text
  $output = csc_readblock_get(4);
  
  $block->content = '<div class="csc-research-intro">' . $output . "</div>";

  return $block;
}
