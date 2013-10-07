<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Events Calendar'),
  'description' => t('Show events calendar'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_events_calendar_render',
  'admin info' => 'csc_events_calendar_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_events_calendar_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Events Calendar';
    $block->content = 'Show events_calendar';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_events_calendar_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = '';
  
  //Load block Grants Buttons
  $output = csc_readblock_get('event_calendar-block_1', 'views');
  
  $block->content = '<div class="csc-events-calendar">' . $output . "</div>";

  return $block;
}
