<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related People'),
  'description' => t('Shows People related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_people_render',
  'admin info' => 'csc_related_people_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_people_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related People';
    $block->content = 'CSC Related People widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */ 
function csc_related_people_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');
  
  $type = 'people';
  $nids = csc_related_get_nodes($type, 8);
  
  $output = '<div class="see-all"><a href="'. url('people/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
  foreach($nids as $nid){
    $node = node_load($nid);
    $lng = $node->language;
    $output .= theme('csc_related_people_item', array('title' => $node->title,
                                                      'body' => $node->field_small_teaser[$lng][0]['value'],
                                                      'nid' => $node->nid,
                                                      'position' => $node->field_position,
                                                      'image' => isset($node->field_featured_image[$lng][0]['uri']) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                ));
  }

  $block = new stdClass();
  $block->title = 'People'; 
  $block->content = '<div class="csc-people-container">' . $output . '</div>';
  
  return $block;
}

/**
 * Theme function
 */ 
function theme_csc_related_people_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'csc_medium','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';

  $output = '<div class="csc-people-wrapper">';
  $output.= '<div class="csc-people-detail"><div class="csc-people-text">';
  $output.= "<h2>$url</h2>";
  $output.= $var['body'];
  $output.= '</div></div>';  
  $output.= $image;
  $output.= '</div>';
  
  return $output;
}
