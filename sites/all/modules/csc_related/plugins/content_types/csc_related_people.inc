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

  if(sizeof($nids)){
    $output = '<div class="see-all"><a href="'. url('people/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_people_item', array('title' => $node->title,
                                                        'body' => $node->field_small_teaser[$lng][0]['value'],
                                                        'nid' => $node->nid,
                                                        'position' => $node->field_position[$lng][0]['value'],
                                                        'image' => isset($node->field_featured_image[$lng][1]['uri']) ? $node->field_featured_image[$lng][1]['uri'] : ''
                                                  ));
    }

    $block = new stdClass();
    $block->title = 'People';
    $block->content = '<div class="csc-people-container">' . $output . '</div>';

    return $block;
  }
}

/**
 * Theme function
 */
function theme_csc_related_people_item($var){
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'csc_medium','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';

  $output = '<div class="csc-people-wrapper">';
  $outputInner = '<div class="csc-people-detail"><div class="csc-people-text">';
  $outputInner.= "<h2>" . $var['title'] . "</h2>";
  $outputInner.= $var['position'];
  $outputInner.= '</div></div>';
  $outputInner.= $image;
  $url = l($outputInner, "node/" . $var['nid'], array('html' => true));
  $output.= $url . '</div>';

  return $output;
}
