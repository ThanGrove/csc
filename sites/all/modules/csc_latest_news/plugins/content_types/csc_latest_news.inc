<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Latest News'),
  'description' => t('Shows latest news'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_latest_news_render',
  'admin info' => 'csc_latest_news_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_latest_news_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Latest News';
    $block->content = 'Shows Latest News';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_latest_news_render($subtype, $conf, $panel_args, $context = NULL) {
  $qry = "SELECT n.nid, n.title, fst.field_small_teaser_value FROM {node} n LEFT JOIN {field_data_field_small_teaser} fst ON fst.entity_id=n.nid WHERE n.type='news' AND n.status=1 ORDER BY n.nid DESC LIMIT 1";
  $data = db_query($qry)->fetchObject();

  $output = '<div class="csc-block">';
  $output.= '<h3>' . l($data->title, 'node/' . $data->nid) . '</h3>';
  $output.= '<p>'. $data->field_small_teaser_value .'</p>';
  $output.= '<p>' . l('<img src="' . base_path() . path_to_theme() . '/images/rounded_black_arrow.png" width=16 height=16 alt="">', 'node/' . $data->nid, array('html' => true) ) . '</p>';
  $output.= '</div>';

  $block = new stdClass();
  $block->title = 'Latest News';
  $block->content = $output;

  return $block;
}
