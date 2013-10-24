<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Next Event'),
  'description' => t('Shows next event'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_next_event_render',
  'admin info' => 'csc_next_event_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_next_event_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Next Event';
    $block->content = 'Shows Next Event';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_next_event_render($subtype, $conf, $panel_args, $context = NULL) {
  $today = date('Y-m-d H:i:s');

  $qry = "SELECT fed.entity_id FROM {field_data_field_event_date} fed, {node} n WHERE fed.field_event_date_value >= '$today' AND fed.entity_id=n.nid AND n.status=1 ORDER BY fed.field_event_date_value LIMIT 1";
  $data = db_query($qry)->fetchObject();

  if($data){
    $node = node_load($data->entity_id);
    $lng = $node->language;

    list($d,$t) = explode(' ', $node->field_event_date[$lng][0]['value']);
    list($year, $month, $day) = explode('-', $d);
    list($h, $min, $sec) = explode(':', $t);
    $tstamp = mktime($h, $min, $sec, $month, $day, $year);
    if($node->field_featured_image){
      $img = theme_image_style(array('style_name' => 'medium','path' => $node->field_featured_image[$lng][0]['uri'],'alt' => $node->title, 'title' => '', 'width' => '', 'height' => ''));
      $class = ' half';
    }else{
      $img = '';
      $class = '';
    }

    $location_name = isset($node->field_location[$lng][0]['name']) ? $node->field_location[$lng][0]['name'] : '';

    $output = '<div class="csc-item-container">';
    $output.= '<div class="csc-event-text-container'.$class.'">';
    $output.= "<h3>" . l($node->title, "node/" . $node->nid). "</h3>";
    $output.= '<span class="when">WHEN:</span> ' . format_date($tstamp, 'small') . "<br>";
    $output.= '<span class="when">WHERE: </span>' . $location_name . "<br>";
    $output.= '<div class="event-desc">' . $node->field_teaser[$lng][0]['value'] . "</div>";
    $output.= '<p>' . l('CONTINUE READING', "node/" . $node->nid, array('attributes' => array('class' => 'white-link')))  . '</p>';
    $output.= '</div>';

    if($img){
      $output.= '<div class="csc-event-image">';
      $output.= $img;
      $output.= '</div>';
    }
    $output.= "</div>\n";


    $block = new stdClass();
    $block->title = 'Next Event';
    $block->content = $output;

    return $block;
  }
}
