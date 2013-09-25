<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * left column with fix width and right column fluid width
 *
 * Variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 */
?>
<div class="csc-panel-container"><div class="csc-panel-wrapper">
  <div class="csc-panel-col-left">
    <div class="csc-panel-inside"><?php print $content['left']; ?></div>
  </div>

  <div class="csc-panel-col-right">
    <div class="csc-panel-inside-inside">
      <?php print $content['right']; ?>
      <div class="csc-panel-separator">Previous News &amp; Features</div>
    </div>
  </div>
</div></div>
