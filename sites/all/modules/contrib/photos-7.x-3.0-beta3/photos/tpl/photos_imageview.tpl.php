<?php
/**
 * @file
 * Formats single image view page.
 */

  // Ajax edit or delete.
  if (isset($image->ajax['edit_url'])) {
    $name_class = ' jQueryeditable_edit_title';
    $des_class = ' jQueryeditable_edit_des';
    $title_edit = ' id="photos-image-edit-title-' . $image->fid . '"';
    $des_edit = ' id="photos-image-edit-des-' . $image->fid . '"';
    $ajax_delete_id = isset($image->ajax['del_id']) ? $image->ajax['del_id'] : '';
  }
  else {
    $name_class = '';
    $des_class = '';
    $title_edit = '';
    $des_edit = '';
    $ajax_delete_id = '';
  }
  // Modifying the code above could lead to Ajax Failure.
  // 修改以上代码可能导致ajax编辑功能失效。
?>
<?php if($type == 'list') : ?>
  <div class="photos_image_list_view" <?php print $ajax_delete_id; ?>>
    <div class="photos_list_view_thumb">
      <a href="<?php print $image->url ?>#image-load"><?php print $image->view; ?></a>
    </div>
    <?php 
      print '<h2 class="photos_list_view_title' . $name_class . '"' . $title_edit . '>';
      print $image->title;
      print '</h2>';
    ?>
    <div class="photos_list_view_des<?php print $des_class; ?>" <?php print $des_edit; ?>><?php print $image->des; ?></div>
    <div class="photos_list_view_info">
      <?php if(isset($image->ajax['del_link'])): ?>
        <?php print $image->ajax['del_link'];?>
      <?php endif; ?>
      <?php if(isset($image->ajax['edit_link'])): ?>
        <?php print $image->ajax['edit_link'];?>
      <?php endif; ?>
      <?php if (isset($image->links['vote'])): ?>
        <?php print $image->links['vote']; ?>
      <?php endif; ?>
      <?php if (isset($image->links['info'])): ?>
        <?php print $image->links['info']; ?>
      <?php endif; ?>
      <?php if (isset($image->links['count'])): ?>
        <?php print $image->links['count']; ?>
      <?php endif; ?>
      <?php if (isset($image->links['cover'])): ?>
        <?php print $image->links['cover']; ?>
      <?php endif; ?>
      <?php if (isset($image->links['comment'])): ?>
        <?php print $image->links['comment']; ?>
      <?php endif; ?>
    </div>
  </div>
<?php endif; ?>
<?php if($type == 'view') : ?>
  <div id="image-load" class="image-load">
    <?php
      print '<h2 class="photos_view_title' . $name_class . '"' . $title_edit . '>';
      print $image->title;
      print '</h2>';
    ?>
    <div class="photos_view_des<?php print $des_class ?>"<?php print $des_edit ?>><?php print $image->des;?></div>
    <div class="photos_view_links">
      <?php if (isset($image->vote)): ?>
        <?php print $image->vote; ?>
      <?php endif; ?>
      <div class="photo-rg">
        <?php if (isset($image->ajax['del_link'])): ?>
          <?php print $image->ajax['del_link'];?>
        <?php endif; ?>
        <?php if (isset($image->ajax['edit_link'])): ?>
          <?php print $image->ajax['edit_link'];?>
        <?php endif; ?>
        <?php if (isset($image->links['to_sub'])): ?>
          <?php print $image->links['to_sub'];?>
        <?php endif; ?>
        <?php if($image->count) { print format_plural($image->count, '!cou visit', '!cou visits', array('!cou' => $image->count)); } ?>
        <?php
          if (isset($image->links['comment'])) {
            print $image->links['comment'];
          }
          if (isset($image->links['cover'])) {
            print $image->links['cover'];
          }
          if (isset($image->links['more'])) {
            print $image->links['more'];
          }
        ?>
      </div>
    </div>
    <div class="photo_link_pager">
      <?php if(isset($image->links['pager']['prev_url'])) { ?>
        <div class="photo-pager-left">
          <a href="<?php print $image->links['pager']['prev_url'];?>#image-load">« <?php print t('previous');?></a>
        </div>
      <?php } ?>
      <?php if(isset($image->links['pager']['next_url'])) { ?>
        <div class="photo-pager-right">
          <a href="<?php print $image->links['pager']['next_url'];?>#image-load"><?php print t('next');?> »</a>
        </div>
      <?php } ?>
    </div>
    <div class="image-a"><?php print $image->view;?></div>
  </div>
  <?php if (isset($image->comment['view'])): ?>
    <?php print drupal_render($image->comment['view']);?>
  <?php endif; ?>
  <?php if (isset($image->comment['box'])): ?>
    <?php print drupal_render($image->comment['box']);?>
  <?php endif; ?>
<?php endif; ?>