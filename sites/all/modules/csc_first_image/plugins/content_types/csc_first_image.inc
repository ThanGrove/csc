<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC First Image'),
  'description' => t('Returns First node with image'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_first_image_render',
  'admin info' => 'csc_first_image_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_first_image_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC First Image';
    $block->content = 'Returns First node with image';
    return $block;
  }
}

/**
 * Needs to know what content type the View is using as filter
 * variable $GLOBALS['view_content_type'] must be set from View 
 */
function csc_first_image_render($subtype, $conf, $panel_args, $context = NULL) {

  //Nothing to do
  if(!isset($GLOBALS['view_content_type']) or $GLOBALS['view_content_type'] == '' ) return;

  $nodeid = 0;
  if (is_numeric(arg(1))) $nodeid = arg(1);
  
  if($nodeid){
    $target_filter = "AND fr.field_related_target_id=$nodeid";
  }else{
    $target_filter = '';
  }
  
  //$qry = "SELECT fm.uri, n.title, n.nid FROM {node} n, {field_data_field_featured_image} ffi, {file_managed} fm WHERE n.type='". $GLOBALS['view_content_type'] ."' AND n.status=1 AND ffi.entity_id=n.nid AND ffi.field_featured_image_fid=fm.fid ORDER BY n.nid DESC LIMIT 1";
  $qry = "SELECT fm.uri, n.title, n.nid FROM {node} n, {field_data_field_related} fr, {field_data_field_featured_image} ffi, {file_managed} fm WHERE fr.bundle = '". $GLOBALS['view_content_type'] ."' $target_filter AND n.nid=fr.entity_id AND n.nid=ffi.entity_id AND fm.fid=ffi.field_featured_image_fid LIMIT 1";
  $row = db_query($qry)->fetchObject();

  if($row){
    //$img = theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $row->uri, 'alt' => $row->title, 'title' => $row->title, 'width' => '100%', 'height' => ''  ));
    $img = '<img src="'. file_create_url($row->uri) .'" width="100%" alt="'. $row->title .'">';
    $output = '<div class="csc-first-image-wrapper">';
    $output.= $img;
    $output.= '<div class="csc-first-image-caption">'. l($row->title, 'node/' . $row->nid) .'</div>';
    $output.= "</div>\n";
    
    $block = new stdClass();
    $block->title = '';
    $block->content = $output;
    
    return $block;
  }
}
