<?php
//Get current node id
function csc_related_current_nid(){
  $nodeid = 0;
  if (arg(0) == 'node' && is_numeric(arg(1))) $nodeid = arg(1);

  return $nodeid;
}

//Retrieve nodes of a given content type related to current node
function csc_related_get_nodes($type, $limit = 3){
  //Get current node id
  $nodeid = csc_related_current_nid();
  
  if($nodeid){
    $qry = "SELECT entity_id FROM field_data_field_related WHERE field_related_target_id=$nodeid AND bundle='$type' ORDER BY field_related_target_id DESC LIMIT $limit";
    $r = db_query($qry);
    $nids = array();
    foreach($r as $row) $nids[] = $row->entity_id;
    
    return $nids;
  }else{
    return false;
  }  
}