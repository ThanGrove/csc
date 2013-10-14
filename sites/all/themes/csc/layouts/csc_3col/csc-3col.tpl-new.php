<?php
/**
 * @file
 * Template for a 3 column panel layout.
 *
 * This template provides a three column panel display layout, with
 * left column with fix width and other two columns fluid width
 *
 * Variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['fixed']: Content in the fixed column.
 *   - $content['fluid1']: Content in the first fluid column.
 *   - $content['fluid2']: Content in the second fluid column.
 */
?>
<div class="csc-3col-container">
  <div class="csc-3col-col-fixed">
    <div class="csc-3col-inside"><?php print $content['fixed']; ?></div>
  </div>

  <div class="csc-3col-fluid-wrapper">
    <div class="csc-3col-col-fluid csc-3col-first">
      <div class="csc-3col-inside"><?php print $content['fluid1']; ?></div>
    </div>
    <div class="csc-3col-col-fluid csc-3col-second">
      <div class="csc-3col-inside"><?php print $content['fluid2']; ?></div>
    </div>
  </div>
</div>
