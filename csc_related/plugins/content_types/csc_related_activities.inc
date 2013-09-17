<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Activities'),
  'description' => t('Shows Activities related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_activities_render',
  'admin info' => 'csc_related_activities_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_activities_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Activities';
    $block->content = 'CSC Related Activities widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */ 
function csc_related_activities_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');
  
  $type = 'activities';
  $nids = csc_related_get_nodes($type);
  
  $output = '';
  foreach($nids as $nid){
    $node = node_load($nid);
    $lng = $node->language;
    $output .= theme('csc_related_activities_item', array('title' => $node->title,
                                                      'body' => $node->field_small_teaser[$lng][0]['value'],
                                                      'nid' => $node->nid,
                                                      'image' => $node->field_featured_image,
                                                ));
  }

  $block = new stdClass();
  $block->title = 'Activities'; 
  $block->content = $output;
  
  return $block;
}

/**
 * Theme function
 */ 
function theme_csc_related_activities_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  
  $output ='<div class="csc-activities-item"><div class="csc-item-container">';
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= "</div></div>\n";
  
  return $output;
}
