<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Research'),
  'description' => t('Shows Research, Learning and Engagement related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_research_render',
  'admin info' => 'csc_related_research_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_research_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Research';
    $block->content = 'CSC Related Research widget';
    return $block;
  }
}


/**
 * Build blocks for Related Research
 */ 
function csc_related_research_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');
  
  $res = array();
  $types = array('research', 'learning', 'engagement');  
  foreach($types as $type){
    $nids = csc_related_get_nodes($type);
    if($nids) $res[] = array('type' => $type, 'nid' => $nids[0]);  
  }
  
  $output = '';
  $class = 'csc-item-num-' . sizeof($res);
  foreach($res as $n){
    $nid = $n['nid'];
    $node = node_load($nid);
    $lng = $node->language;
    $output .= theme('csc_related_research_item', array('title' => $node->title,
                                                        'body' => $node->field_small_teaser[$lng][0]['value'],
                                                        'nid' => $node->nid,
                                                        'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                        'type' => $n['type'],
                                                        'class' => $class,
                                                ));
  }

  $block = new stdClass();
  $block->title = 'Research'; 
  $block->content = $output;
  
  return $block;
}

/**
 * Theme function
 */ 
function theme_csc_related_research_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  $title = ucfirst($var['type']);
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';

  $output = '<div class="csc-research-item '. $var['class'] .'"><div class="csc-item-container">';
  $output.= '<h3 class="csc-research-title">' . $title . '</h3>';
  if ($var['image']) $output .= $image . "<br>";
  $output.= "<h2>$url</h2>";
  $output.= $var['body'];
  $output.= '<div class="see-all-research"><a href="'. url($var['type'] . '/' . csc_related_current_nid()) .'">SEE ALL '. strtoupper($var['type']) .'</a></div>';
  $output.= '</div>';  
  $output.= '</div>';
  
  return $output;
}
