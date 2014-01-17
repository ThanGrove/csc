<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Node Content Type'),
  'description' => t('Shows content type for a given node'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_ctype_render',
  'admin info' => 'csc_ctype_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_ctype_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Node Content Type';
    $block->content = 'Shows content type for a given node';
    return $block;
  }
}

function csc_ctype_render($subtype, $conf, $panel_args, $context = NULL) {

  if (is_numeric(arg(1)))
    $nid = arg(1);
  else
    return;
  
  $qry = "SELECT n.type, nt.name FROM {node} n, {node_type} nt WHERE n.nid=$nid AND nt.type=n.type";
  $r = db_query($qry)->fetchObject();
  
  switch ($r->type){
    case 'organization':
      $type = 'Affiliation';
      break;
    case 'people':
      $type = 'Person';
      break;
    case 'feature':
      $type = 'Featured Story';
      break;
    case 'class':
      $type = 'Instruction';
      break;
    case 'research':
    case 'learning':
    case 'engagement':
    case 'initiatives':
    case 'event':
    case 'news':
      $type = $r->name;
      break;
    default:
      $type = '';
      break;  
  }
  
  if($type){
    $output = '<span class="csc-node-content-type">' . $type . '</output>';
    
    $block = new stdClass();
    $block->title = '';
    $block->content = $output;
    
    return $block;
  }
}
