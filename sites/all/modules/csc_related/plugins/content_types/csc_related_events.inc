<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Related Events'),
  'description' => t('Shows Event related to current page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_related_events_render',
  'admin info' => 'csc_related_events_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_related_events_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Related Events';
    $block->content = 'CSC Related events widget';
    return $block;
  }
}

/**
 * Build blocks for Related events
 */
function csc_related_events_render($subtype, $conf, $panel_args, $context = NULL) {
  module_load_include('inc', 'csc_related', 'csc_related');

  //Get current node id
  $nodeid = csc_related_current_nid();
  //Future events
  $qry = "SELECT fr.entity_id, UNIX_TIMESTAMP(ed.field_event_date_value) as stamp
          FROM field_data_field_related fr, node n, field_data_field_event_date ed
          WHERE fr.field_related_target_id=$nodeid
          AND fr.entity_id=n.nid
          AND ed.entity_type='node' AND ed.entity_id=fr.entity_id
          AND UNIX_TIMESTAMP() <= UNIX_TIMESTAMP(ed.field_event_date_value)
          AND n.status = 1
          AND fr.bundle='event'
          ORDER BY stamp ASC
          LIMIT 3";

  $r = db_query($qry);
  $nids = array();
  foreach($r as $row) $nids[] = $row->entity_id;

  //Less than 3 events, search past events
  $count = sizeof($nids);
  if($count < 3){
    $limit = 3 - $count;
    $qry = "SELECT fr.entity_id, UNIX_TIMESTAMP(ed.field_event_date_value) as stamp
            FROM field_data_field_related fr, node n, field_data_field_event_date ed
            WHERE fr.field_related_target_id=$nodeid
            AND fr.entity_id=n.nid
            AND ed.entity_type='node' AND ed.entity_id=fr.entity_id
            AND UNIX_TIMESTAMP() > UNIX_TIMESTAMP(ed.field_event_date_value)
            AND n.status = 1
            AND fr.bundle='event'
            ORDER BY stamp DESC
            LIMIT $limit";

    $r = db_query($qry);
    foreach($r as $row) $nids[] = $row->entity_id;
  }

  if(sizeof($nids)){
    $output = '<div class="see-all"><a href="'. url('events/' . csc_related_current_nid()) .'">SEE ALL</a></div>';
    $class = 'csc-item-num-' . sizeof($nids);
    foreach($nids as $nid){
      $node = node_load($nid);
      $lng = $node->language;
      $output .= theme('csc_related_events_item', array('title' => $node->title,
                                                        'body' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value']: '',
                                                        'nid' => $node->nid,
                                                        'location' => ($node->field_location) ? $node->field_location[$lng][0] : '',
                                                        'image' => ($node->field_featured_image) ? $node->field_featured_image[$lng][0]['uri'] : '',
                                                        'date' => isset($node->field_event_date[$lng][0]) ? $node->field_event_date[$lng][0] : '',
                                                        'class' => $class,
                                                  ));
    }

    $block = new stdClass();
    $block->title = 'Events';
    $block->content = $output;

    return $block;
  }
}

/**
 * Theme function
 */
function theme_csc_related_events_item($var){
  $past = false;
  $url = l($var['title'], "node/" . $var['nid']);
  $class = $var['class'];

  $when = '';
  if($var['date']){
    $now = new DateTime('now');
    $date = new DateTime($var['date']);
    if( $date < $now ) {
      $past = true;
      $class .= ' past ';
    }
    list($d,$t) = explode(' ', $var['date']);
    list($year, $month, $day) = explode('-', $d);
    list($h, $min, $sec) = explode(':', $t);
    $tstamp = mktime($h, $min, $sec, $month, $day, $year);
    $when = format_date($tstamp, 'small', '', 'UTC');
    $stamp1 = strtotime($var['date']['value']);
    $stamp2 = strtotime($var['date']['value2']);
    $date1 = date('Y-m-d', $stamp1);
    $date2 = date('Y-m-d', $stamp2);
    $arg = array('date1' => format_date($stamp1, 'short', '', 'UTC'),
                 'date2' => format_date($stamp2, 'short', '', 'UTC'),
                 'timezone' => '',
                 'attributes_start' => array(),
                 'attributes_end' => array(),
           );

    if($stamp1 == $stamp2){
      $arg['date'] = $arg['date1'];
      $when = theme('date_display_single',$arg);
    }
    //Same date, diferent hour
    elseif($stamp2 - $stamp1 <= 86400){
      $arg['date'] = $arg['date1'];
      $when = theme('date_display_single',$arg);
      $when .= ' to ' . format_date($stamp2, 'custom', 'g:ia', 'UTC');
    }else{
      $when = theme('date_display_range',$arg);
    }
  }

  //$image = ($var['image']) ? theme_image_style(array('style_name' => 'panopoly_image_featured','path' => $var['image'], 'alt' => $var['title'], 'title' => $var['title'], 'width' => '', 'height' => ''  )) : '';
  $image = ($var['image']) ? '<img src="'. image_style_url('panopoly_image_featured', $var['image']) .'" alt = "'. $var['title'] . '" title="' . $var['title'] .'">' : '';
  $location = ($var['location'])? $var['location']['name']: '';


  $output = '<div class="csc-event-item '. $class .'"><div class="csc-item-container">';
  if ($var['image']) $output .=  l($image, 'node/' . $var['nid'], array('html'=>true)) . "<br>";
  $output .= $past ? '<div class="past-flag">past</div>' : '';
  $output.= "<h2>$url</h2>";
  $output.= '<p class="csc-item-teaser">' . $var['body'] . "</p>";
  $output.= '<p><h3>WHEN</h3>' . $when  . "</p>";
  $output.= '<p><h3>WHERE</h3>' . $location . "</p>";
  $output.= "</div></div>\n";

  return $output;
}
