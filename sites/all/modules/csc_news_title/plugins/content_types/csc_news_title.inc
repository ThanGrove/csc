<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC News Title'),
  'description' => t('Shows author name below title'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_news_title_render',
  'admin info' => 'csc_news_title_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_news_title_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC News Title';
    $block->content = 'Shows author name below title';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_news_title_render($subtype, $conf, $panel_args, $context = NULL) {
  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  if($nodeid){
    $node = node_load($nodeid);
    $lng = $node->language;
    if($node->type == 'news' and $node->field_news_type[$lng][0]['value'] == 'Blog post' ){
      $output = '<h1 id="page-title" class="tile" style="display: block;">' . $node->title . "<br>";
      $output.= '<span class="node-author">Published by ' . $node->name . '</span></h1>';
    }else{
      $output = '<h1 id="page-title" class="tile" style="display: block;">' . $node->title . "</h1>"; 
    }
  
    $block = new stdClass();
    $block->title = '';
    $block->content = $output;
  
    return $block;  
  }

}
