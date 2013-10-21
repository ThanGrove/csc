<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Newsletter Extended'),
  'description' => t('Newsletter subscription form with extra fields'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_newsletter_big_render',
  'admin info' => 'csc_newsletter_big_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_newsletter_big_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Newsletter Extended';
    $block->content = 'Newsletter subscription form with extra fields';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_newsletter_big_render_original($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = 'Sign up for our Newsletter';
  
  //Load block from simplenews module
  $block = block_load('simplenews', 1);
  $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $output = render($render_array);
  
  $block->content = $output;

  return $block;
}

function csc_newsletter_big_render($subtype, $conf, $panel_args, $context = NULL) {
  $path = drupal_get_path('module', 'csc_newsletter');
  drupal_add_js($path . '/plugins/content_types/csc_newsletter.js');
  
  $output = '<div class="content">';
  $output.= '<div class="newsletter-text-wrapper">';
  $output.= '<h3>Newsletter Sign Up</h3>';
  $output.= '<p>Enter your email address to recieve our monthly newsletter</p>';
  $output.= '</div>';
  $output.= '<div class="newsletter-form-wrapper">';
  $output.= '<form action="http://uvacontemplation.us5.list-manage.com/subscribe/post?u=bb09e07367e52174653ec5969&amp;id=bee009d669" method="post" id="mc-embedded-subscribe-form" name="mc-embedded-subscribe-form" class="validate" target="_blank" novalidate>';
  $output .=
  '<div class="form-item form-type-textfield">
    <input type="text" value="" name="FNAME" id="mce-FNAME" maxlength="128" class="form-text required" placeholder="Name*">
  </div>
  <div class="form-item form-type-textfield">
    <input type="email" value="" name="EMAIL" id="mce-EMAIL" maxlength="128" class="form-text required" placeholder="Email*">
  </div>';

  $output.=
  '<div id="mce-responses" class="clear">
  	<div class="response" id="mce-error-response" style="display:none"></div>
  	<div class="response" id="mce-success-response" style="display:none"></div>
   </div>
   <div class="clear"><input type="submit" value="SIGN UP" name="subscribe" id="mc-embedded-subscribe" class="form-submit"></div>';

  $output.= '</form>';
  $output.= "</div>\n";

  $block = new stdClass();
  $block->title = '';  
  $block->content = $output;

  return $block;
}
