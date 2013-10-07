<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Classes'),
  'description' => t('Shows Classes related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_classes_render',
  'admin info' => 'csc_related_classes_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_classes_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Classes';
    $block->content = 'CSC Related Classes widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */
function csc_related_classes_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');

  $type = 'class';
  $nids = csc_related_get_nodes($type);
  
  if(sizeof($nids)){
    $output = '<div class="see-all"><a href="'. url('classes/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_classes_item', array('title' => $node->title,
                                                        'body' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                                        'nid' => $node->nid,
                                                  ));
    }
  
    $block = new stdClass();
    $block->title = 'Classes';
    $block->content = $output;
  
    return $block;
  }
}

/**
 * Theme function
 */
function theme_csc_related_classes_item($var){
  $url = l($var['title'], "node/" . $var['nid']);

  $output ='<div class="csc-classes-item"><div class="csc-item-container">';
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= "</div></div>\n";

  return $output;
}
