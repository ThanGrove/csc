<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Teaser'),
  'description' => t('Shows node teaser'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_teaser_render',
  'admin info' => 'csc_teaser_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_teaser_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Teaser';
    $block->content = 'Shows node Teaser';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_teaser_render($subtype, $conf, $panel_args, $context = NULL) {
  //drupal_add_js(drupal_get_path('module', 'csc_teaser') . '/plugins/content_types/jquery.lightbox_me.js');
  drupal_add_js(drupal_get_path('module', 'csc_teaser') . '/plugins/content_types/csc_teaser.js');

  $block = new stdClass();

  //Current node's id
  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  //$qry = "SELECT fdt.field_teaser_value, fdb.body_value FROM {field_data_field_teaser} fdt, {field_data_body} fdb WHERE fdt.entity_id=$nodeid AND fdb.entity_id=$nodeid";
  //$qry = "SELECT fdt.field_teaser_value, fdb.body_value FROM {field_data_body} fdb LEFT JOIN {field_data_field_teaser} fdt ON fdt.entity_id=$nodeid WHERE fdb.entity_id=$nodeid";
  $qry = "SELECT fdt.field_teaser_value, fdb.body_value FROM {field_data_field_teaser} fdt LEFT JOIN  {field_data_body} fdb ON fdt.entity_id=fdb.entity_id WHERE fdt.entity_id=$nodeid";
  $data = db_query($qry)->fetchObject();
  $content = '';
  if($nodeid) $content = $data->body_value;

  $output = '<div class="csc-teaser-div">';
  $output .= isset($data->field_teaser_value) ? $data->field_teaser_value : '';

  if(isset($data->body_value) && $data->body_value <> ''){
    $output.= '<div class="csc-teaser-more">read full description</div>';
    $output.= '</div>'; // closes csc-teaser-div above
    $output.= '<div id="csc-teaser-body" class="tooltip"><div class="tooltip-content">'. render($content) .'</div><div class="csc-teaser-less">read summary</div></div>';
  } else {
    $output.= '</div>'; // closes csc-teaser-div above
  }

  $block->title = 'Teaser';
  $block->content = $output;

  return $block;
}
