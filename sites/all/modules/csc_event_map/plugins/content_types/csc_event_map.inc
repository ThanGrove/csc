<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Event Map'),
  'description' => t('Shows Event Map'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_event_map_render',
  'admin info' => 'csc_event_map_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_event_map_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Event Map';
    $block->content = 'Shows Event Map';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_event_map_render($subtype, $conf, $panel_args, $context = NULL) {
  $path = drupal_get_path('module', 'csc_event_map');
  drupal_add_js($path . '/csc_event_map.js');

  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  if($nodeid){
    $node = node_load($nodeid);
    $lng = $node->language;

    if($node->field_location){
      $street = ($node->field_location[$lng][0]['street']) ? $node->field_location[$lng][0]['street'] : '';
      $city = ($node->field_location[$lng][0]['city']) ? $node->field_location[$lng][0]['city'] : '';
      $zip = ($node->field_location[$lng][0]['postal_code']) ? $node->field_location[$lng][0]['postal_code'] : '';
      $country = ($node->field_location[$lng][0]['country']) ? $node->field_location[$lng][0]['country'] : '';

      if($street or $city or $zip){
        $src = "http://maps.google.com/?q=$street,$city,$zip,$country";
        $near = "$street,$city,$zip";

        $output = '<div class="csc-map-wrapper">';
        $output.= '<iframe id="map-frame" width="100%" height="400" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="'. $src .'&amp;ie=UTF8&amp;hq=&amp;hnear='. $near .'&amp;t=m&amp;z=14&amp;iwloc=A&amp;output=embed"></iframe>';
        $output.= "</div>\n";

        $block = new stdClass();
        $block->content = $output;

        return $block;
      }
    }
  }
}
