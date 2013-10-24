<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Isotope Page'),
  'description' => t('Shows Isotope page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_isotope_render',
  'admin info' => 'csc_isotope_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_isotope_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Isotope Page';
    $block->content = 'CSC Isotope page widget';
    return $block;
  }
}


/**
 * Build Isotope container & childs
 */ 
function csc_isotope_render($subtype, $conf, $panel_args, $context = NULL) {
  drupal_add_css(drupal_get_path('module', 'csc_isotope') . '/css_isotope.css');
  //drupal_add_js(libraries_get_path('jquery.isotope') . '/jquery.isotope.js');
  //drupal_add_js(drupal_get_path('module', 'csc_isotope') . '/plugins/content_types/csc_isotope.js');
  //drupal_add_js("(function ($) {  $(window).load(function() { $('#iso-container').isotope({ itemSelector : '.isotope-item'}); }); })(jQuery);", 'inline');
  drupal_add_js(drupal_get_path('module', 'csc_isotope') . '/plugins/content_types/csc_home.js');

  $block = new stdClass();

  $block->title = 'Isotope Page';
  
  $qry = "SELECT n.nid, n.type, n.title, fdb.body_value as body, n.created, fm.uri
  FROM {node} n LEFT JOIN {field_data_field_featured_image} fdfi ON fdfi.entity_id=n.nid LEFT JOIN {file_managed} fm ON fdfi.field_featured_image_fid=fm.fid, {field_data_body} fdb
  WHERE n.status=1 AND n.type IN ('feature', 'news', 'initiatives')
  AND n.nid=fdb.entity_id
  ORDER BY RAND()";
  
  $output = '<div id="iso-container" class="isotope">' . "\n";
  $r = db_query($qry);
  foreach($r as $row){
    $body = strip_tags($row->body, '<br>');
    $body = substr($body, 0, 150) . '...';
    $output .= csc_isotope_item(array('title' => $row->title, 'body' => $body, 'nid' => $row->nid, 'image' => $row->uri, 'type' => $row->type, 'created' => $row->created));
    //$output .= $row->title . "<br>\n";
  }
  $output.= "</div>\n";
  
  $block->content = $output;
  
  return $block;
}

/**
 * Implements theme function
 */ 
function csc_isotope_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  $class = 'type-' . $var['type'] . ' node-' . $var['nid'];
  $date = date('d.m.y', $var['created']);
  $body = strip_tags($var['body'], '<p><br>');
  $body = $body . "...";
  //$image = ($var['image']) ? theme('image', array('path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title']  )) : '';
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';
  $output = '<div id="node-'.$var['nid'].'" class="isotope-item isotope-element '. $class .'">';
  $output .= ($image) ? '<div class="iso-image">'. $image . '</div>' : '';
  if($var['type'] <> 'initiatives') $output.= '<div class="iso-date-wrapper"><div class="iso-date">'.$date.'</div></div>';
  $output .= '
    <div class="iso-title">' . $url . '</div>  
    <div class="iso-teaser">' . $body . '</div>  
  </div>
  ';
  return $output;
}
