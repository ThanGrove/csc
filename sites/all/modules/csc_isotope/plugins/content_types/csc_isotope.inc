<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Isotope Filter'),
  'description' => t('Shows filter options for CSC Isotope page'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_isotope_admin_render',
  'admin info' => 'csc_isotope_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_isotope_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'Filter';
    $block->content = 'CSC Isotope filter widget';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_isotope_admin_render($subtype, $conf, $panel_args, $context = NULL) {
  $path = drupal_get_path('module', 'csc_isotope') . '/plugins/content_types';
//  drupal_add_js($path .'/csc_isotope.filter.js');
  drupal_add_css($path .'/csc_isotope.filter.css');

  $block = new stdClass();

  $block->title = 'Filter Content';

  $block->content = '
  <div id="filters">
    <a href="#" data-filter="type-news"><img class="" src="/'.$path.'/images/news_icon.png" width=35 height=35 alt="News"></a>
    <a href="#" data-filter="type-feature"><img class="" src="/'.$path.'/images/feature_icon.png" width=35 height=35 alt="Features"></a><br>
    <a href="#" data-filter="type-initiatives"><img class="" src="/'.$path.'/images/initiatives_icon.png" width=35 height=35 alt="Initiatives"></a>
    <a href="#" data-filter="*"><img class="" src="/'.$path.'/images/refresh_icon.png" width=35 height=35 alt="Refresh"></a>
  </div>
  ';

  return $block;
}
