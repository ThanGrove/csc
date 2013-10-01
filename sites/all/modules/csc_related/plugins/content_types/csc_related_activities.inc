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

  $output = '<div class="see-all"><a href="'. url('activities/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
  foreach($nids as $nid){
    $node = node_load($nid);
    $lng = $node->language;
    $output .= theme('csc_related_activities_item', array('title' => $node->title,
                                                      'body' => $node->field_small_teaser[$lng][0]['value'],
                                                      'nid' => $node->nid,
                                                      'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
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
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';

  $output ='<div class="csc-activities-item"><div class="csc-item-container">';
  if ($var['image']) $output .= $image . "<br>";
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= "</div></div>\n";

  return $output;
}
