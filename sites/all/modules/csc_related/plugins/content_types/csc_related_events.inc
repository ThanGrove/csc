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

  if(sizeof($nids)){
    $output = '<div class="see-all"><a href="'. url('events/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    $class = 'csc-item-num-' . sizeof($nids);
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_events_item', array('title' => $node->title,
                                                        'body' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value']: '',
                                                        'nid' => $node->nid,
                                                        'location' => ($node->field_location) ? $node->field_location[$lng][0] : '',
                                                        'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                        'date' => isset($node->field_event_date[$lng][0]['value']) ? $node->field_event_date[$lng][0]['value'] : '',
                                                        'class' => $class,
                                                  ));
    }
  
    $block = new stdClass();
    $block->title = 'Events'; 
    $block->content = $output;
    
    return $block;
  }  
}

/**
 * Theme function
 */ 
function theme_csc_related_events_item($var){
  $url = l($var['title'], "node/" . $var['nid']);

  $when = '';
  if($var['date']){
    list($d,$t) = explode(' ', $var['date']);
    list($year, $month, $day) = explode('-', $d);
    list($h, $min, $sec) = explode(':', $t);
    $tstamp = mktime($h, $min, $sec, $month, $day, $year);
    $when = format_date($tstamp, 'small');
  }

  $image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';
  $location = ($var['location'])? $var['location']['name']: '';
  
  $output = '<div class="csc-event-item '. $var['class'] .'"><div class="csc-item-container">';
  if ($var['image']) $output .= $image . "<br>";
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= '<p><h3>WHEN</h3>' . $when  . "</p>";
  $output.= '<p><h3>WHERE</h3>' . $location . "</p>";
  $output.= "</div></div>\n";
  
  return $output;
}