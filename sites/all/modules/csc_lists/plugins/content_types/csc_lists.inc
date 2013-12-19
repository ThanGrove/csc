<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC List Nodes'),
  'description' => t('Shows List of Different type of nodes'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_lists_render',
  'admin info' => 'csc_lists_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_lists_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC List Nodes';
    $block->content = 'Show Lists of Different type of nodes';
    return $block;
  }
}

function csc_lists_render($subtype, $conf, $panel_args, $context = NULL) {

  $type = arg(1);
  $nid = arg(2);

  switch($type){
    case 'class':
      $title = 'Instruction';
      $node_type = 'class';
      break;
    case 'people':
      $title = 'People';
      $node_type = 'people';
      break;
    case 'research':
      $title = 'Research';
      $node_type = 'research';
      break;
    case 'learning':
      $title = 'Learning';
      $node_type = 'learning';
      break;
    case 'engagement':
      $title = 'Engagement';
      $node_type = 'engagement';
      break;
    case 'feature':
      $title = 'Feature Articles';
      $node_type = 'feature';
      break;
    case 'organization':
      $title = 'Affiliations';
      $node_type = 'organization';
      break;
    case 'school':
      $title = 'Schools';
      $node_type = 'organization';
      break;
    default:
      $title = 'News';
      $node_type = 'news';
      break;
  }

  //*** Initializing ***
  $sort = isset($_GET['sort']) ? htmlspecialchars($_GET['sort']): '';
  $sort_by = 'n.title';
  $order = 'ASC';
  $render_function = 'csc_lists_default_render';
  $tables = $where = $fields = '';

  //*** Filter ***
  $filter = isset($_GET['filter']) ? htmlspecialchars($_GET['filter']): '';
  $filter_by = '';
  if($type == 'class'){
    switch($filter){
      case 'past':
        $tables = ', {field_data_field_date} fd';
        $where = "AND n.nid = fd.entity_id AND fd.entity_type = 'node' AND (fd.field_date_value < NOW() AND fd.field_date_value2 < NOW() AND fd.field_date_value2 <> fd.field_date_value)";
        break;
      case 'upcoming':
        $tables = ', {field_data_field_date} fd';
        $where = "AND n.nid = fd.entity_id AND fd.entity_type = 'node' AND fd.field_date_value > NOW()";
        break;
      case 'ongoing':
        $tables = ', {field_data_field_date} fd';
        $where = "AND n.nid = fd.entity_id AND fd.entity_type = 'node' AND ((fd.field_date_value < NOW() AND fd.field_date_value2 > NOW()) or (fd.field_date_value < NOW() AND fd.field_date_value2 = fd.field_date_value))";
        break;
    }
  }

  if($type == 'school'){
    //Default filter for schools
    $tables = ', {field_data_field_organization_type} ot';
    $where = "AND n.nid = ot.entity_id AND ot.entity_type = 'node' AND ot.field_organization_type_value='UVA School'";
  }

  //*** Related Nodes ***
  if($nid){
    $qry = "SELECT title FROM {node} WHERE nid=$nid";
    $row = db_query($qry)->fetchObject();
    $title.= ' <span class="title-context">for ' . $row->title . '</span>';


    $tables .= ', {field_data_field_related} fr';
    $where .= "AND fr.field_related_target_id=$nid AND fr.entity_id=n.nid AND n.status = 1 AND fr.bundle='$node_type'";
  }

  //*** Audience ***
  if(isset($_GET['audience'])){
    if($type == 'class') {
      $audience = $_GET['audience'] == '' ? 'academic' : $_GET['audience'];
      $tables .= ', {field_data_field_audience} fa';
      $where .= "AND fa.field_audience_value='". htmlspecialchars($audience) ."' AND fa.entity_id=n.nid AND n.status = 1 AND fa.bundle='$node_type'";
    }
  }

  //*** Sorting and Render Function ***
  if($type == 'news' or $type == 'feature'){
    switch($sort){
      case 'date_asc':
        $sort_by = 'n.created';
        $order = 'ASC';
        break;
      case 'date_desc':
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
      default:
        //$sort_by = 'n.title';
        //$order = 'ASC';
        $sort = 'date_desc';
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
    }
  }

  if($type == 'people'){
    switch($sort){
      case 'date_asc':
        $sort_by = 'n.created';
        $order = 'ASC';
        break;
      case 'date_desc':
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
      case 'name_desc':
        $sort_by = 'n.title';
        $order = 'DESC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
      default:
        $sort = 'name_asc';
        $sort_by = 'n.title';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
    }
  }

  if($type == 'class'){
    switch($sort){
      case 'date_asc':
        $sort_by = 'n.created';
        $order = 'ASC';
        break;
      case 'date_desc':
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
      case 'school':
        $fields = ', fr2.field_related_target_id, n2.title as rtitle';
        $tables .= ", {field_data_field_related} fr2, {node} n2, {field_data_field_organization_type} ot";
        $where .= "AND fr2.entity_id=n.nid AND fr2.entity_type='node' AND n2.nid=fr2.field_related_target_id AND n2.nid=ot.entity_id AND ot.field_organization_type_value='UVA School'";
        $sort_by = 'n2.title, n.title';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_school_render';
        break;
      case 'title_desc':
        $sort_by = 'n.title';
        $order = 'DESC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
      case 'title_asc':
        $sort_by = 'n.title';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
      case 'offered':
      default:
        $fields = ', UNIX_TIMESTAMP(fd.field_date_value) as start_date, UNIX_TIMESTAMP(fd.field_date_value2) as end_date';
        if($filter <> 'ongoing' and $filter <> 'past' and $filter <> 'upcoming'){
          $tables .= ', {field_data_field_date} fd';
          $where .= "AND n.nid = fd.entity_id AND fd.entity_type = 'node'";
        }
        //$sort_by = 'n.created';
        $sort_by = 'fd.field_date_value';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_offered_render';
        break;
    }
  }

  if($type == 'organization' or $type == 'school'){
    switch($sort){
      case 'date_asc':
        $sort_by = 'n.created';
        $order = 'ASC';
        break;
      case 'date_desc':
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
      case 'title_desc':
        $sort_by = 'n.title';
        $order = 'DESC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
      default:
        $sort = 'title_asc';
        $sort_by = 'n.title';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
    }
  }

  if($type == 'research' or $type == 'learning' or $type=='engagement'){
    switch($sort){
      case 'date_asc':
        $sort_by = 'n.created';
        $order = 'ASC';
        break;
      case 'date_desc':
        $sort_by = 'n.created';
        $order = 'DESC';
        break;
      case 'year_asc':
        $tables .= ", {field_data_field_year} fy";
        $where .= "AND n.nid=fy.entity_id AND entity_type='node'";
        $sort_by = 'fy.field_year_value';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_year_render';
        break;
      case 'year_desc':
        $tables .= ", {field_data_field_year} fy";
        $where .= "AND n.nid=fy.entity_id AND entity_type='node'";
        $sort_by = 'fy.field_year_value';
        $order = 'DESC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_year_render';
        break;
      case 'title_desc':
        $sort_by = 'n.title';
        $order = 'DESC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
      case 'title_asc':
      default:
        $sort = 'title_asc';
        $sort_by = 'n.title';
        $order = 'ASC';
        $render_function = isset($_GET['group']) ? 'csc_lists_default_render' : 'csc_lists_alpha_render';
        break;
    }
  }

  $qry = "SELECT n.nid $fields FROM {node} n $tables WHERE n.status = '1' AND n.type = '$node_type' $where ORDER BY $sort_by $order";

  //$output = csc_lists_select();
  $output = '<div class="list-items ' . $render_function . '">' . $render_function($qry) . '</div>';
  $output .= '<script>jQuery(".list-item").dotdotdot({watch: true, height: 150})</script>';

  $block = new stdClass();
  $block->title = $title;
  $block->content = csc_lists_select($sort) . '<div class="csc-lists-container">' . $output . '</div><div class="clear"></div>';

  return $block;
}

function csc_lists_select($sortArg) {

  $type = arg(1);
  $nid = arg(2);
  $output = '';

  switch($type){
    case 'people':
      $sort = array('Name' => array('name_asc' => 'A-Z', 'name_desc' => 'Z-A'), 'Date Added' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First'));
      $sort_default = 'name_asc';
      //$sort = array('name_asc' => 'Name: Ascending', 'name_desc' => 'Name: Descending', 'date_desc' => 'Date added: Newest First', 'date_asc' => 'Date added: Oldest First');
      $filter = array();
      break;
    case 'class':
      $sort = array('Date Offered' => array('offered' => 'Upcoming'), 'Title' => array('title_asc' => 'A-Z', 'title_desc' => 'Z-A'), 'Date Added' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First'), 'School' => array('school' => 'School A-Z'));
      $sort_default = 'date_desc';
      //$filter = array('upcoming' => 'Upcoming', 'ongoing' => 'Ongoing', 'past' => 'Past');
      break;
    case 'organization':
      $sort = array('Name' => array('title_asc' => 'A-Z', 'title_desc' => 'Z-A'), 'Date Added' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First'));
      $sort_default = 'title_asc';
      $filter = array();
      break;
    case 'research':
    case 'learning':
    case 'engagement':
      $year = date('Y');
      $sort = array('Title' => array('title_asc' => 'A-Z', 'title_desc' => 'Z-A'), 'Date Added' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First')); //, 'Year' => array('year_asc' => '2013-' . $year, 'year_desc' => $year . '-2013'));
      $sort_default = 'date_desc';
      $filter = array();
      break;
    case 'feature':
      $sort = array('Date Added' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First'));
      $sort_default = 'date_desc';
      $filter = array();
      break;
    //Default News
    default:
      $sort = array('Date' => array('date_desc' => 'Newest First', 'date_asc' => 'Oldest First'));
      $sort_default = 'date_desc';
      $filter = array();
      break;
  }

  $output .= '<div class="list-filter-wrapper">';

  //Audience filter
  if($type == 'class'){
    $class_array = array(
      'academic' => 'Courses for UVa students',
      'non-academic' => 'Courses for anyone',
      'drop-in' => 'Drop-in classes for anyone'
    );

    $base_link = 'list/' . $type;
    $base_link.= ($nid) ? "/$nid" : '';
    $class = isset($_GET['audience']) ? $_GET['audience'] : 'academic';
    $output .= '<div id="audience-filter" class="audience-filter '. $class .'">';

    foreach($class_array as $k => $v) {
      $output .= '<a href="#" class="' . ($class == $k ? 'selected' : '') . '" data-value="' . $k . '">' . $v . '</a>';
    }

    $output .= '</div>';
  } else {
    $class = '';
  }

  if(sizeof($sort)){
    $output .= '<form method="get" id="csc-list-form">';
    $output .= '<input id="audience-input" type="hidden" name="audience" value="' . $class . '"/>';
    $output .= '<input type="hidden" name="q" value="list/' . $type;
    $output .= ($nid) ? "/$nid" : '';
    $output .= '">';

    $output .= '<div class="sort-label">Sort by</div>';
    $output .= '<select style="min-width:125px" data-placeholder="Sort by..." name="sort" onChange="document.getElementById(\'csc-list-form\').submit()">';
    foreach($sort as $k1 => $v1){
      $output .= '<optgroup label="' . $k1 . '">';
      foreach($v1 as $k => $v){
        $output .= '<option value="'. $k .'"';
        if($sortArg == $k) $output .= ' selected';
        $output .='>' . $v . '</option>';
      }
      $output .= '</optgroup>';
    }
    $output .= '</select>';

    //if(sizeof($filter)){
    //$output .= '<select name="filter">';
    //$output .= '<option  value="">Filter by</option>';
    //foreach($filter as $k => $v){
    //$output .= '<option value="'. $k .'"';
    //if(isset($_GET['filter']) && $_GET['filter'] == $k) $output .= ' selected';
    //$output .='>' . $v . '</option>';
    //}
    //$output.= "</select>\n";
    //}

    // grouping
    //$output .= '<div class="group-results"><input type="checkbox" name="group" value="false" onchange="document.getElementById(\'csc-list-form\').submit();"';
    //$output .= ($_GET['group']) ? ' checked': '';
    //$output .=' >Do not group results</div>';

    $output .= "</form>\n";
    $output .= '<script>jQuery("#csc-list-form").find("select").chosen({disable_search: true})</script>';
    $output .= '</div>';
  }

  return $output;
}


function csc_lists_default_render($qry){
  $r = db_query($qry);

  $output = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $output.= theme('csc_lists_item', array('title' => $node->title,
                                            'nid' => $node->nid,
                                            'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                            'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                           ));
  }

  return $output;
}

function csc_lists_alpha_render($qry){
  $r = db_query($qry);

  $output = ''; $letter = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $item = theme('csc_lists_item', array('title' => $node->title,
                                          'nid' => $node->nid,
                                          'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                          'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                         ));

    $l = strtoupper(substr($node->title, 0, 1));
    if($letter <> $l){
      $letter = $l;
      if ($tagopen) {
        $output .= "</div>";
        $tagopen = false;
      }
      $output .= "<div class='clear'></div><h2>$letter</h2>\n";
      $output .= '<div class="list-group">';
      $tagopen = true;
      $output .= $item;
    }else{
      $output .= $item;
    }
  }

  if( $tagopen ) {
    $output .= "</div>";
  }

  return $output;
}

function csc_lists_year_render($qry){
  $r = db_query($qry);

  $output = ''; $year = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $item = theme('csc_lists_item', array('title' => $node->title,
                                          'nid' => $node->nid,
                                          'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                          'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                         ));

    $y = $node->field_year[$lng][0]['value'];
    if($year <> $y){
      $year = $y;
      $output .= "<div class='clear'></div><h2>$year</h2>\n";
      $output .= $item;
    }else{
      $output .= $item;
    }
  }

  return $output;
}

function csc_lists_school_render($qry){
  $r = db_query($qry);

  $output = ''; $school = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $item = theme('csc_lists_item', array('title' => $node->title,
                                          'nid' => $node->nid,
                                          'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                          'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                         ));

    $s = $row->rtitle;
    if($school <> $s){
      $school = $s;
      $output .= "<div class='clear'></div><h2>$school</h2>\n";
      $output .= $item;
    }else{
      $output .= $item;
    }
  }

  return $output;
}

function csc_lists_offered_render($qry){
  $r = db_query($qry);

  $now = time();
  $output = $up = $on = $past = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $item = theme('csc_lists_item', array('title' => $node->title,
                                          'nid' => $node->nid,
                                          'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                          'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                         ));

    if($row->end_date < $now)
      $past .= $item;
    //elseif( ($row->start_date < $now and $row->end_date > $now) or ($row->start_date < $now and $row->end_date == $row->start_date) )
      //$on .= $item;
    else
      $up .= $item;
  }

  if($up){
    $output .= "<div class='clear'></div><h2 class='lower'>Ongoing &amp; Upcoming</h2>\n";
    $output .= "<div class='list-group'>$up</div>";
  }
  if($on){
    $output .= "<div class='clear'></div><h2>Ongoing</h2>\n";
    $output .= $on;
  }
  if($past){
    $output .= "<div class='clear'></div><h2 class='lower'>Past</h2>\n";
    $output .= "<div class='list-group'>$past</div>";
  }

  return $output;
}

function csc_lists_consolidate_render($qry){
  $r = db_query($qry);

  $now = time();
  $output = $con = $past = '';
  foreach($r as $row){
    $node = node_load($row->nid);
    $lng = $node->language;
    $item = theme('csc_lists_item', array('title' => $node->title,
                                          'nid' => $node->nid,
                                          'teaser' => isset($node->field_small_teaser[$lng][0]['value']) ? $node->field_small_teaser[$lng][0]['value'] : '',
                                          'image' => isset($node->field_featured_image[$lng][0]['uri'])? $node->field_featured_image[$lng][0]['uri'] : '',
                                         ));

    if($row->start_date > $now)
      $con .= $item;
    elseif( ($row->start_date < $now and $row->end_date > $now) or ($row->start_date < $now and $row->end_date == $row->start_date) )
      $con .= $item;
    else
      $past .= $item;
  }

  if($con){
    //$output .= "<h2>Future</h2>\n";
    $output .= $con;
  }
  if($past){
    $output .= "<h2>Past</h2>\n";
    $output .= $past;
  }

  return $output;
}
