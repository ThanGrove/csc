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
  drupal_add_css(drupal_get_path('module', 'csc_isotope') . '/plugins/content_types/css_isotope.css');
  drupal_add_js(drupal_get_path('module', 'csc_isotope') . '/plugins/content_types/csc_home.js');

  $block = new stdClass();

  $block->title = 'Isotope Page';

  //Get Activity nodes
  $qry = "SELECT n.nid, n.type, n.title, fst.field_small_teaser_value as body, n.created, fm.uri
    FROM node n
    LEFT JOIN field_data_field_featured_image fdfi ON fdfi.entity_id=n.nid
    LEFT JOIN file_managed fm ON fdfi.field_featured_image_fid=fm.fid
    LEFT JOIN field_data_field_small_teaser fst ON fst.entity_id=n.nid
    WHERE n.status=1 AND n.type = 'initiatives'
    ORDER BY n.created DESC";
  $r = db_query($qry);
  $act = array();
  foreach($r as $row){
    $body = strip_tags($row->body, '<br>');
    $body = substr($body, 0, 150);
    $act[] = csc_isotope_item(array('title' => $row->title, 'body' => $body, 'nid' => $row->nid, 'image' => $row->uri, 'type' => $row->type, 'created' => $row->created));
  }

  //Get Feature and news
  $qry = "SELECT n.nid, n.type, n.title, fst.field_small_teaser_value as body, n.created, fm.uri
    FROM {node} n
    LEFT JOIN {field_data_field_featured_image} fdfi ON fdfi.entity_id=n.nid
    LEFT JOIN {file_managed} fm ON fdfi.field_featured_image_fid=fm.fid
    LEFT JOIN field_data_field_small_teaser fst on fst.entity_id=n.nid
    WHERE n.status=1 AND n.type IN ('feature', 'news')
    AND n.nid=fst.entity_id
    ORDER BY n.created DESC";
  $r = db_query($qry);

  $tiles = array();
  foreach($r as $row){
    $body = strip_tags($row->body, '<br>');
    $body = substr($body, 0, 150);
    $tiles[] = csc_isotope_item(array('title' => $row->title, 'body' => $body, 'nid' => $row->nid, 'image' => $row->uri, 'type' => $row->type, 'created' => $row->created));
  }

  //Build widget content
  $nact = sizeof($act);
  $ntiles = sizeof($tiles);
  $ratio = floor($ntiles / $nact);
  $activity_order = array(0, 2, 5, 8, 10);
  $output = '<div id="iso-container" class="isotope">' . "\n";

  for( $i = $k = $l = 0; $i < ($nact + $ntiles) ; $i++ ) {
    if( in_array($i, $activity_order, true) ) {
      $output .= $act[$k++];
    } else if ($ntiles > $l) {
      $output .= $tiles[$l++];
    }
  }

  $output.= "</div>\n";

  $block->content = $output;

  return $block;
}

/**
 * Implements theme function
 */
function csc_isotope_item($var){
  $path = drupal_get_path('module', 'csc_isotope') . '/plugins/content_types/images/';
  //$url = l($var['title'], "node/" . $var['nid']);
  $class = 'type-' . $var['type'] . ' node-' . $var['nid'];
  $date = date('d M Y', $var['created']);
  $body = strip_tags($var['body'], '<p><br>');
  if($var['type'] != 'initiatives') {
    $body = '&nbsp; | &nbsp;' . $body;
  }

  $icon = '';
  if($var['type'] == 'news') $icon = '<img class="iso-icon" src="/'. $path .'icon_news.png" width=25 height=25 alt="">';
  if($var['type'] == 'feature') $icon = '<img class="iso-icon" src="/'. $path .'icon_feature.png" width=25 height=25 alt="">';

  //$image = ($var['image']) ? theme('image', array('path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title']  )) : '';
  $image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';
  $output = '<div id="node-'.$var['nid'].'" class="isotope-item isotope-element '. $class .'">';
  $outputInside = ($image) ? '<div class="iso-image">'. $image . '</div>' : '';
  $date = ($var['type'] == 'initiatives') ? '' : '<span class="iso-date">' . $date . '</span>' ;
  $outputInside .= '
    <div class="iso-text">'. $icon .'
    <div class="iso-teaser"><h3 class="iso-title">' . $var['title'] . '</h3>' . $date . $body . '</div>
    </div>
  ';
  $outputInside = l($outputInside, "node/" . $var['nid'], array('html' => true));
  $output = $output . $outputInside . '</div>';

  return $output;
}
