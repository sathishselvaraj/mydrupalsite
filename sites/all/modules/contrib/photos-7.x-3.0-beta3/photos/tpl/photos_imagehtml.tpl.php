<?php
/**
 * @file
 * Formats single image.
 */
?>
<?php
  $style_label = isset($image->thumb[$style_name]) ? $image->thumb[$style_name] : '';
  $filename = isset($image->filename) ? strip_tags($image->filename) : '';
  $title = isset($image->title) ? strip_tags($image->title) : $filename;
  $alt = isset($image->alt) ? strip_tags($image->alt) : $title;
  // @todo move to preprocess / other function / variable $image->view.
  if ($style_name == 'original') {
    $image_styles = image_style_options(FALSE);
    if (isset($image_styles['original'])) {
      $image_view = theme('image_style', array(
        'style_name' => $style_name,
        'path' => $image->uri,
        'alt' => $alt,
        'title' => $alt
      ));
    }
    else {
      $image_view = theme('image', array(
        'path' => $image->uri,
        'alt' => $alt,
        'title' => $alt
      ));
    }
  }
  else {
    $image_view = theme('image_style', array(
      'style_name' => $style_name,
      'path' => $image->uri,
      'alt' => $alt,
      'title' => $alt
    ));
  }
?>
<?php if(!isset($image->href)): ?>
<?php print $image_view; ?>
<?php else: ?>
    <div class="photos_imagehtml">
      <?php
        print l($image_view, $image->href, array(
          'html' => true
        ));
      ?>
      <?php if(isset($image->colorbox)): ?>
        <a class="photos_imagehtml_colorbox colorbox" rel="colorbox_<?php print $image->pid; ?>" href="<?php print _photos_l($image->uri, 'origianl'); ?>" title="<?php print $title; ?>">view original</a>
      <?php endif; ?>
    </div>
<?php endif; ?>