<?php

// Plugin definition
$plugin = array(
  'title' => t('CSC 3 Columns'),
  'category' => t('Columns: 3'),
  'icon' => 'csc_3col.png',
  'theme' => 'csc_3col',
  'css' => 'csc_3col.css',
  'regions' => array(
    'fixed' => t('Fixed Column'),
    'fluid1' => t('First fluid column'),
    'fluid2' => t('Second fluid column')
  ),
);
