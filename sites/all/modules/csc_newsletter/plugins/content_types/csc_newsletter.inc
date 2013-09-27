<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Newsletter'),
  'description' => t('Newsletter subscription form'),
  'category' => t('CSC Plugins'),
//  'edit form' => 'examplemodule_twitter_timeline_edit_form',
  'render callback' => 'csc_newsletter_render',
  'admin info' => 'csc_newsletter_admin_info',
  'defaults' => array(
    'username' => 'wiifm',
    'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_newsletter_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Newsletter';
    $block->content = 'Newsletter subscription form';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_newsletter_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = 'Sign up for our Newsletter';
  
  //Load block from simplenews module
  $block = block_load('simplenews', 1);
  $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $output = render($render_array);
  
  $block->content = $output;

  return $block;
}
