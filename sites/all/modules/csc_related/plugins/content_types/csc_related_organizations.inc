<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Organizations'),
  'description' => t('Shows Organizational Units related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_organizations_render',
  'admin info' => 'csc_related_organizations_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_organizations_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Organizational Units';
    $block->content = 'CSC Related Organizations widget';
    return $block;
  }
}


/**
 * Build blocks for Related events
 */ 
function csc_related_organizations_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');
  
  $type = 'organization';
  $nids = csc_related_get_nodes($type);
  
  if($nids){
    $output = '<div class="see-all"><a href="'. url('organizations/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    $class = 'csc-item-num-' . sizeof($nids);
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_organizations_item', array('title' => $node->title,
                                                        'body' => $node->field_small_teaser[$lng][0]['value'],
                                                        'nid' => $node->nid,
                                                        'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                        'class' => $class,
                                                  ));
    }
    
    switch($node->type){
      case 'initiatives':
      case 'research':
      case 'learning':
      case 'engagement':
        $title = 'Partners';
        break;
      default:
        $title = 'Affiliations';
        break;
    }
  
    $block = new stdClass();
    $block->title = $title; 
    $block->content = $output;
    
    return $block;  
  }

}

/**
 * Theme function
 */ 
function theme_csc_related_organizations_item($var){
  $url = l($var['title'], "node/" . $var['nid']);
  //$image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';
  $image = ($var['image']) ? '<img src="'. image_style_url('panopoly_image_featured', $var['image']) .'" alt = "'. $var['title'] . '" title="' . $var['title'] .'">' : '';
  
  $output ='<div class="csc-organization-item '. $var['class'] .'"><div class="csc-item-container">';
  if ($var['image']) $output .= $image . "<br>";
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= "</div></div>\n";
  
  return $output;
}
