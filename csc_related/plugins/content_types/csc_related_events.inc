<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Events'),
  'description' => t('Shows Event related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_events_render',
  'admin info' => 'csc_related_events_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_events_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Events';
    $block->content = 'CSC Related events widget';
    return $block;
  }
}

/**
 * Build blocks for Related events
 */ 
function csc_related_events_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');
  
  $type = 'event';
  $nids = csc_related_get_nodes($type);
  
  $output = '';
  $class = 'csc-item-num-' . sizeof($nids);
  foreach($nids as $nid){
    $node = node_load($nid);
    $lng = $node->language;
    $output .= theme('csc_related_events_item', array('title' => $node->title,
                                                      'body' => $node->field_small_teaser[$lng][0]['value'],
                                                      'nid' => $node->nid,
                                                      'location' => $node->field_location[$lng][0],
                                                      'image' => $node->field_featured_image,
                                                      'date' => $node->field_event_date[$lng][0]['value'],
                                                      'class' => $class,
                                                ));
  }

  $block = new stdClass();
  $block->title = 'Events'; 
  $block->content = $output;
  
  return $block;
}

/**
 * Theme function
 */ 
function theme_csc_related_events_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  list($d,$t) = explode(' ', $var['date']);
  list($year, $month, $day) = explode('-', $d);
  list($h, $min, $sec) = explode(':', $t);
  $tstamp = mktime($h, $min, $sec, $month, $day, $year);
  
  $output ='<div class="csc-event-item '. $var['class'] .'"><div class="csc-item-container">';
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= '<p><h3>WHEN</h3>' . format_date($tstamp, 'small')  . "</p>";
  $output.= '<p><h3>WHERE</h3>' . $var['location']['name'] . "</p>";
  $output.= "</div></div>\n";
  
  return $output;
}