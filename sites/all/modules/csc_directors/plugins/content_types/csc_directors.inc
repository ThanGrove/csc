<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Directors'),
  'description' => t('Shows CSC Directors'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_directors_render',
  'admin info' => 'csc_directors_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_directors_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'The CSC Directorate';
    $block->content = 'CSC Directors Widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */
function csc_directors_render($subtype, $conf, $panel_args, $context = NULL) {

  $qry = "SELECT n.nid FROM {node} n, {field_data_field_csc_director} fsd WHERE n.status=1 AND n.type = 'people' AND n.nid = fsd.entity_id AND fsd.field_csc_director_value=1";
  $r = db_query($qry);

  $output = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $output.= theme('csc_directors_item', array('title' => $node->title,
                                                'nid' => $node->nid,
                                                'position' => isset($node->field_position[$lng][0]['value']) ? $node->field_position[$lng][0]['value'] : '',
                                                'image' => isset($node->field_featured_image[$lng][1]['uri'])? $node->field_featured_image[$lng][1]['uri'] : '',
                                                ));
  }

  $block = new stdClass();
  $block->title = 'The CSC Directorate';
  $block->content = '<div class="csc-directors-container">' . $output . '</div>';

  return $block;
}

/**
 * Theme function
 */
function theme_csc_directors_item($var){
  //$url = l($var['title'], "node/" . $var['nid']);
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'csc_medium','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';

  $output = '<div class="csc-directors-wrapper">';
  $outputInside = '<div class="csc-directors-detail">';
  $outputInside.= $image;
  $outputInside.= '<div class="csc-director-text">';
  $outputInside.= "<h2>" . $var['title'] . "</h2>";
  $outputInside.= $var['position'];
  $outputInside.= '</div></div>';
  $output.= l($outputInside, "node/" . $var['nid'], array('html' => true)) . '</div>';

  return $output;
}
