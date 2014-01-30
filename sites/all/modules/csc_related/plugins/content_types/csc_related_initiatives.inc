<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Initiatives'),
  'description' => t('Shows Initiatives related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_initiatives_render',
  'admin info' => 'csc_related_initiatives_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_initiatives_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Initiatives';
    $block->content = 'CSC Related Initiatives widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */
function csc_related_initiatives_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');

  $type = 'initiatives';
  $nids = csc_related_get_nodes($type);
  
  if($nids){
    $output = '<div class="see-all"><a href="'. url('list/initiatives/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    $class = 'csc-item-num-' . sizeof($nids);
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_initiatives_item', array('title' => $node->title,
                                                        'body' => $node->field_small_teaser[$lng][0]['value'],
                                                        'nid' => $node->nid,
                                                        'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                        'class' => $class,
                                                  ));
    }

    $block = new stdClass();
    $block->title = 'Initiatives';
    $block->content = $output;

    return $block;
  }

}

/**
 * Theme function
 */
function theme_csc_related_initiatives_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  $image = ($var['image']) ? '<img src="'. image_style_url('panopoly_image_featured', $var['image']) .'" alt = "'. $var['title'] . '" title="' . $var['title'] .'">' : '';

  $output ='<div class="csc-initiatives-item '. $var['class'] .'"><div class="csc-item-container">';
  if ($var['image']) $output .= l($image, 'node/' . $var['nid'], array('html'=>true)) . "<br>";
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= "</div></div>\n";

  return $output;
}
