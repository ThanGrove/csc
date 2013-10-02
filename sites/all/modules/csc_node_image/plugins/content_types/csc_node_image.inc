<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Node Image'),
  'description' => t('Widget to show image or images on a widget'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_node_image_render',
  'admin info' => 'csc_node_image_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_node_image_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Node Image';
    $block->content = 'Show node image(s)';
    return $block;
  }
}


function csc_node_image_render($subtype, $conf, $panel_args, $context = NULL) {
  $path = drupal_get_path('module', 'csc_node_image');
  drupal_add_css($path . '/plugins/content_types/bjqs.css');
  drupal_add_js($path . '/plugins/content_types/responsiveslides.js');
  drupal_add_js($path . '/plugins/content_types/csc_node_image.js');

  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  if($nodeid){
    $node = node_load($nodeid);
    $lng = $node->language;

    if($node->field_featured_image){
      $li = '';
      foreach($node->field_featured_image[$lng] as $img){
        $caption = (isset($img['image_field_caption']['value'])) ? $img['image_field_caption']['value'] : '';
        $image = theme_image_style(array('style_name' => 'panopoly_image_full','path' => $img['uri'], 'alt' => '', 'title' => $caption, 'width' => '', 'height' => ''  ));
        $li .= "<li>$image" . ($caption != '' ? "<p>$caption</p>" : '') . "</li>";
      }

      $output = '<div id="csc-node-images"><ul class="bjqs rslides">';
      $output.= $li;
      $output.= "</ul></div>\n";

      $block = new stdClass();
      $block->title = '';
      $block->content = $output;

      return $block;
    }
  }

}
