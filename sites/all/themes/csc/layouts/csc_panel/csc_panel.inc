<?php

// Plugin definition
$plugin = array(
  'title' => t('CSC Custom panel'),
  'category' => t('Columns: 2'),
  'icon' => 'csc_panel.png',
  'theme' => 'csc_panel',
  'css' => 'csc_panel.css',
  'regions' => array(
    'left' => t('Left side'),
    'right' => t('Right side')
  ),
);
