<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('CSC Newsletter'),
  'description' => t('Newsletter subscription form'),
  'category' => t('CSC Plugins'),
  'render callback' => 'csc_newsletter_render',
  'admin info' => 'csc_newsletter_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function csc_newsletter_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = 'CSC Newsletter';
    $block->content = 'Newsletter subscription form';
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function csc_newsletter_render_original($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = 'Sign up for our Newsletter';

  //Load block from simplenews module
  $block = block_load('simplenews', 1);
  $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $output = render($render_array);

  $block->content = $output;

  return $block;
}

function csc_newsletter_render($subtype, $conf, $panel_args, $context = NULL) {
  global $base_root, $base_path;

  $path = drupal_get_path('module', 'csc_newsletter');
  drupal_add_js($base_root . $base_path . 'profiles/panopoly/modules/contrib/jquery_update/replace/ui/ui/minified/jquery.ui.position.min.js');
  drupal_add_js($base_root . $base_path . 'profiles/panopoly/modules/contrib/jquery_update/replace/ui/ui/minified/jquery.ui.dialog.min.js');
  drupal_add_js($path . '/plugins/content_types/csc_newsletter.js');

  $output = '
    <div id="dialog-modal" class="csc-hide" title="Select Newsletter">
      <p>By clicking "Subscribe" you are signing up to receive our monthly newsletter.</p>
      <p>Also sign up for...</p>
      <form id="modal-form">
        <p><input type="checkbox" value="1" name="news-1" id="news-1">Local updates (events, classes at UVa, etc.)</p>
        <p><input type="checkbox" value="2" name="news-2" id="news-2">Online course updates</p>
     </form>
    </div>

    <div class="content">
      <p>Enter your email address below to stay up to date on the latest at CSC.
      <form action="http://uvacontemplation.us5.list-manage.com/subscribe/post?u=bb09e07367e52174653ec5969&amp;id=bee009d669" method="post" id="mc-embedded-subscribe-form" name="mc-embedded-subscribe-form" class="validate" target="_blank" novalidate>
        <div class="form-item form-type-textfield">
          <label for="mce-EMAIL">E-mail <span class="form-required" title="This field is required.">*</span></label>
          <input type="email" value="" name="EMAIL" id="mce-EMAIL" size="20" maxlength="128" class="form-text required">
        </div>
        <div id="mce-responses" class="clear">
        	<div class="response" id="mce-error-response" style="display:none"></div>
        	<div class="response" id="mce-success-response" style="display:none"></div>
        </div>
        <div class= "csc-hide">
          <input type="checkbox" value="1" name="group[16045][1]" id="mce-group-16045-0"><br>
          <input type="checkbox" value="2" name="group[16045][2]" id="mce-group-16045-1"><br>
          <input type="text" name="b_bb09e07367e52174653ec5969_bee009d669" value="">
        </div>
        <div class="clear"><input type="button" value="Subscribe" class="mce-button form-submit"></div>
      </form>
    </div>
  ';

  $block = new stdClass();
  $block->title = 'Sign up for our Newsletter';
  $block->content = $output;

  return $block;
}
