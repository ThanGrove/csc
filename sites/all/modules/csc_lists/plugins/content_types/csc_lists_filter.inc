<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC List Nodes Filter'),
  'description' => t('Filter/Sort List of nodes'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_lists_filter_render',
  'admin info' => 'csc_lists_filter_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_lists_filter_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC List Nodes Filter';
    $block->content = 'Filter/Sort List of nodes';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */
function csc_lists_filter_render($subtype, $conf, $panel_args, $context = NULL) {

  $type = arg(1);
  $output = '';
  
  switch($type){
    case 'people':
      $sort = array('name_asc' => 'Name: Ascending', 'name_desc' => 'Name: Descending', 'date_desc' => 'Date added: Newest First', 'date_asc' => 'Date added: Oldest First');
      $filter = array();
      break;
    case 'class':
      $sort = array('title_asc' => 'Title: Ascending', 'title_desc' => 'Title: Descending', 'date_desc' => 'Date added: Newest First', 'date_asc' => 'Date added: Oldest First', 'school' => 'School');
      $filter = array('upcoming' => 'Upcoming', 'ongoing' => 'Ongoing', 'past' => 'Past');
      break;
    case 'organization':
      $sort = array('title_asc' => 'Title: Ascending', 'title_desc' => 'Title: Descending', 'date_desc' => 'Date added: Newest First', 'date_asc' => 'Date added: Oldest First');
      $filter = array();
      break;
    case 'research':
    case 'learning':
    case 'engagement':
      $sort = array('title_asc' => 'Title: Ascending', 'title_desc' => 'Title: Descending', 'date_desc' => 'Date added: Newest First', 'date_asc' => 'Date added: Oldest First', 'year_asc' => 'Year: Ascending', 'year_desc' => 'Year: Descending');
      $filter = array();
      break;
    case 'feature':
      $sort = array('date_desc' => 'Date: Newest First', 'date_asc' => 'Date: Oldest First');
      $filter = array();
      break;
    //Default News
    default:
      $sort = array('date_desc' => 'Date: Newest First', 'date_asc' => 'Date: Oldest First');
      $filter = array();
      break;
  }

  if(sizeof($sort)){
    $output .= '<h2>Sort by</h2>';
    $output.= '<ul class="list-sort">';
    foreach($sort as $k => $v){
      $output .= '<li><a href="'. url('list/' . $type, array('query' => array('sort' => $k))) .'">' . $v . '</a></li>';
    }
    $output.= "</ul>\n";
  }
  
  if(sizeof($filter)){
    $output .= '<h2>Filter by</h2>';
    $output.= '<ul class="list-filter">';
    foreach($filter as $k => $v){
      $output .= '<li><a href="'. url('list/' . $type, array('query' => array('filter' => $k))) .'">' . $v . '</a></li>';
    }
    $output.= "</ul>\n";
  }

  if(!$output) return;

  $block = new stdClass();
  $block->title = '';
  $block->content = $output;

  return $block;
}
