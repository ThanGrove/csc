<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC People Title'),
  'description' => t('Shows first name, middle name and last name as title'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_people_title_render',
  'admin info' => 'csc_people_title_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_people_title_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC People Title';
    $block->content = 'Shows first name, middle name and last name as title';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_people_title_render($subtype, $conf, $panel_args, $context = NULL) {
  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  if($nodeid){
    $node = node_load($nodeid);
    $lng = $node->language;
    
    $lastname = $node->title;
    $firstname = $node->field_first_name[$lng][0]['value'];
    $middlename = $node->field_middle_name[$lng][0]['value'];
    
    $title =  "$firstname ";
    if($middlename) $title .= "$middlename ";
    $title .= $lastname;
    
    $output = '<h1 id="page-title" class="tile" style="display: block;">' . $title . "</h1>"; 
  
    $block = new stdClass();
    $block->title = '';
    $block->content = $output;
  
    return $block;  
  }

}
