<?php
/**
 * @file
 * Admin settings form(s) and submit handler.
 */

function photos_admin_settings() {
  $form['basic'] = array(
    '#title' => t('Basic settings'),
    '#weight' => -5,
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['basic']['photos_access_photos'] = array(
    '#type' => 'radios',
    '#title' => t('Privacy settings'),
    '#default_value' => variable_get('photos_access_photos', 0),
    '#description' => t('People will be able to set album confidentiality.') . (!module_exists('photos_access') ?  ' ' . t('Please enable the ' . l('photos_access', 'admin/modules', array('fragment' => 'edit-modules-album-photos')) . ' module.', array('@url' => url('http://drupal.org/project/photos_access'))) : ''),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#required' => TRUE,
    '#disabled' => (module_exists('photos_access') ? FALSE : TRUE)
  );
  $form['basic']['photos_num'] = array(
    '#type' => 'select',
    '#title' => t('Classic form'),
    '#default_value' => variable_get('photos_num', 5),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
    '#description' => t('Maximum number of upload fields on the classic upload form.'),
  );
  $form['basic']['num'] = array(
    '#title' => t('Number of albums'),
    '#weight' => 10,
    '#type' => 'fieldset',
    '#description' => t('The number of albums a user allowed to create. Administrater is not limited.'),
    '#collapsible' => TRUE,
  );
  $roles = user_roles(TRUE);
  foreach ($roles as $key => $role) {
    $form['basic']['num']['photos_pnum_' . $key] = array(
      '#type' => 'textfield',
      '#title' => $role,
      '#required' => TRUE,
      '#default_value' => variable_get('photos_pnum_' . $key, 20),
      '#prefix' => '<div class="photos-admin-inline">',
      '#suffix' => '</div>',
      '#size' => 10
    );
  }
  $form['basic']['photos_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#default_value' => variable_get('photos_path', 'photos/image_%uid'),
    '#description' => t('The path where the files will be saved relative to the files folder.  Available variables: %uid, %username, %Y, %m, %d.'),
    '#size' => '40',
    '#required' => TRUE,
  );
  $form['basic']['photos_print_sizes'] = array(
    '#type' => 'radios',
    '#title' => t('How to display original image and all sizes?'),
    '#default_value' => variable_get('photos_print_sizes', 1),
    '#description' => t('Print rather than return. To avoid the theme layout been destroyed. Recommended selection "print".'),
    '#required' => TRUE,
    '#options' => array(t('return'), t('print')),
  );
  $form['basic']['photos_comment'] = array(
    '#type' => 'radios',
    '#title' => t('Comment setting'),
    '#default_value' => variable_get('photos_comment', 0),
    '#description' => t('Enable to comment on single photo. You must also open comments for content type / node.'),
    '#required' => TRUE,
    '#options' => array(t('Disabled'), t('Enabled')),
  );
  $form['basic']['photos_vote'] = array(
    '#type' => 'radios',
    '#title' => t('Images vote'),
    '#default_value' => variable_get('photos_vote', 0),
    '#description' => t('For the image to increase the voting feature, you must first install the votingapi.module.'),
    '#required' => TRUE,
    '#options' => array(t('Disabled'), t('Enabled')),
    '#disabled' => (module_exists('votingapi') ? FALSE : TRUE)
  );
  $form['basic']['photos_upzip'] = array(
    '#type' => 'radios',
    '#title' => t('zip compressed upload'),
    '#default_value' => variable_get('photos_upzip', 0),
    '#description' => t('Will be allowed to upload images compressed into a zip, extract the necessary support to open php'),
    '#required' => TRUE,
    '#options' => array(t('Disabled'), t('Enabled')),
    '#disabled' => ((version_compare(PHP_VERSION, '5') >= 0) ? FALSE : TRUE)
  );
  $form['basic']['photos_rname'] = array(
    '#type' => 'radios',
    '#title' => t('Rename image'),
    '#default_value' => variable_get('photos_rname', 0),
    '#description' => t('Rename uploaded image by random numbers, to solve problems with non-ASCII filenames such as Chinese.'),
    '#required' => TRUE,
    '#options' => array(t('Disabled'), t('Enabled')),
  );
  //thumb settings
  if ($size = photos_upload_info(0)) {
    $num = ($size['count'] + 3);
  }
  else {
    $num = 3;
    $size['size'] = array(
      array(
        'style' => 'medium'
      ),
      array(
        'style' => 'large'
      )
    );
  }
  $form['photos_thumb_count'] = array(
    '#type' => 'hidden',
    '#default_value' => $num,
  );
  $form['thumb'] = array(
    '#title' => t('Image sizes'),
    '#weight' => -4,
    '#type' => 'fieldset',
    '#description' => t('Default image sizes. Note: if an image style is deleted after it has been in use for some time that may result in broken external image links (i.e. from the share code and shared galleries).'),
    '#collapsible' => TRUE,
  );
  $thumb_options = image_style_options(TRUE);
  if (empty($thumb_options)) {
    $form['thumb']['image_style'] = array(
      '#markup' => '<p>One or more image styles required: ' . l(t('add image styles'), 'admin/config/media/image-styles') . '.</p>'
    );
  }
  else {
    $form['thumb']['photos_pager_imagesize'] = array(
      '#type' => 'select',
      '#title' => 'Pager size',
      '#default_value' => variable_get('photos_pager_imagesize', 'thumbnail'),
      '#description' => '(Default pager block image style.)',
      '#options' => $thumb_options,
      '#required' => TRUE,
    );
    $form['thumb']['photos_name_0'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => isset($size['size'][0]['name']) ? $size['size'][0]['name'] : NULL,
      '#size' => '10',
      '#required' => TRUE,
      '#prefix' => '<div class="photos-admin-inline">'
    );
    $form['thumb']['photos_size_0'] = array(
      '#type' => 'select',
      '#title' => 'Thumb size',
      '#default_value' => isset($size['size'][0]['style']) ? $size['size'][0]['style'] : NULL,
      '#options' => $thumb_options,
      '#required' => TRUE,
      '#suffix' => '</div>'
    );
    $empty_option = array('' => '');
    $thumb_options = $empty_option+$thumb_options;
    $form['thumb']['additional_sizes'] = array(
      '#markup' => '<p>Additional image sizes ' . l(t('add more image styles'), 'admin/config/media/image-styles') . '.</p>'
    );

    for ($i = 1; $i < $num; $i++) {
      $form['thumb']['photos_name_' . $i] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => isset($size['size'][$i]['name']) ? $size['size'][$i]['name'] : NULL,
        '#size' => '10',
        '#prefix' => '<div class="photos-admin-inline">',
      );
      $form['thumb']['photos_size_' . $i] = array(
        '#type' => 'select',
        '#title' => t('Size'),
        '#default_value' => isset($size['size'][$i]['style']) ? $size['size'][$i]['style'] : NULL,
        '#options' => $thumb_options,
        '#suffix' => '</div>',
      );
    }
  }
  //thumb settings end
  //Display settings
  $form['display'] = array(
    '#title' => t('Display Settings'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );

  $form['display']['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),
    '#collapsible' => TRUE,
    '#description' => t('Albums basic display settings')
  );
  $form['display']['page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page Settings'),
    '#collapsible' => TRUE,
    '#description' => t('Page (e.g: node/[nid]) display settings'),
    '#prefix' => '<div id="photos-form-page">',
    '#suffix' => '</div>'
  );
  $form['display']['teaser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Teaser Settings'),
    '#collapsible' => TRUE,
    '#description' => t('Teaser display settings'),
    '#prefix' => '<div id="photos-form-teaser">',
    '#suffix' => '</div>'
  );
  $form['display']['global']['photos_display_viewpager'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('photos_display_viewpager', 10),
    '#title' => t('How many images show in each page?'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(5, 10, 15, 20, 25, 30, 35, 40, 45, 50))
  );
  $form['display']['global']['photos_display_imageorder'] = array(
    '#type' => 'select',
    '#title' => t('Image display order'),
    '#required' => TRUE,
    '#default_value' => variable_get('photos_display_imageorder', 'weight|asc'),
    '#options' => _photos_order_label()
  );
  $list_imagesize = variable_get('photos_display_list_imagesize', 'thumbnail');
  $view_imagesize = variable_get('photos_display_view_imagesize', 'large');
  $form['display']['global']['photos_display_list_imagesize'] = array(
    '#type' => 'select',
    '#title' => t('Image display size (list)'),
    '#required' => TRUE,
    '#default_value' => $list_imagesize,
    '#description' => t('Displayed in the list (e.g: photos/album/[nid]) of image size.'),
    '#options' => _photos_select_size()
  );
  $form['display']['global']['photos_display_view_imagesize'] = array(
    '#type' => 'select',
    '#title' => t('Image display size (page)'),
    '#required' => TRUE,
    '#default_value' => $view_imagesize,
    '#description' => t('Displayed in the page (e.g: photos/image/[fid]) of image size.'),
    '#options' => _photos_select_size()
  );
  /*
  $form['display']['global']['photos_display_slide'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('photos_display_slide', '640x480'),
    '#title' => t('Slide width and height'),
    '#required' => TRUE,
    '#description' => t('The width and height of flash, e.g: 640x480.'),
  );
  */
  $form['display']['global']['photos_display_user'] = array(
    '#type' => 'radios',
    '#title' => t('Allow users to modify this setting when they create a new album.'),
    '#default_value' => variable_get('photos_display_user', 1),
    '#options' => array(t('Disabled'), t('Enabled (Recommend)'))
  );
  $form['display']['page']['photos_display_page_display'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('photos_display_page_display', 1),
    '#title' => t('Display setting'),
    '#required' => TRUE,
    '#options' => array(t('Do not display'), t('Display cover'), t('Display thumbnails'))
  );
  $form['display']['page']['photos_display_full_viewnum'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('photos_display_full_viewnum', 10),
    '#title' => t('Display quantity'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(5, 10, 15, 20, 25, 30, 35, 40, 45, 50)),
    '#prefix' => '<div class="photos-form-count">'
  );
  $form['display']['page']['photos_display_full_imagesize'] = array(
    '#type' => 'select',
    '#title' => t('Image display size'),
    '#required' => TRUE,
    '#default_value' => variable_get('photos_display_full_imagesize', 'large'),
    '#options' => _photos_select_size(),
    '#suffix' => '</div>'
  );
  /*
  $form['display']['page']['photos_display_page_slide'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('photos_display_page_slide', '640x480'),
    '#title' => t('Slide width and height'),
    '#required' => TRUE,
    '#description' => t('The width and height of flash, e.g: 640x480.'),
    '#prefix' => '<div class="photos-form-slide">',
    '#suffix' => '</div>'
  );
  */
  $form['display']['page']['photos_display_page_user'] = array(
    '#type' => 'radios',
    '#title' => t('Allow users to modify this setting when they create a new album.'),
    '#default_value' => variable_get('photos_display_page_user', 1),
    '#options' => array(t('Disabled'), t('Enabled (Recommend)'))
  );
  $form['display']['teaser']['photos_display_teaser_display'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('photos_display_teaser_display', 1),
    '#title' => t('Display setting'),
    '#required' => TRUE,
    '#options' => array(t('Do not display'), t('Display cover'), t('Display thumbnails'))
  );
  $form['display']['teaser']['photos_display_teaser_viewnum'] = array(
    '#type' => 'select',
    '#default_value' => variable_get('photos_display_teaser_viewnum', 5),
    '#title' => t('Display quantity'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
    '#prefix' => '<div class="photos-form-count">'
  );
  $form['display']['teaser']['photos_display_teaser_imagesize'] = array(
    '#type' => 'select',
    '#title' => t('Image display size'),
    '#required' => TRUE,
    '#default_value' => variable_get('photos_display_teaser_imagesize', 'thumbnail'),
    '#options' => _photos_select_size(),
    '#suffix' => '</div>'
  );
  /*
  $form['display']['teaser']['photos_display_teaser_slide'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('photos_display_teaser_slide', '640x480'),
    '#title' => t('Slide width and height'),
    '#required' => TRUE,
    '#description' => t('The width and height of flash, e.g: 640x480.'),
    '#prefix' => '<div class="photos-form-slide">',
    '#suffix' => '</div>'
  );
  */
  $form['display']['teaser']['photos_display_teaser_user'] = array(
    '#type' => 'radios',
    '#title' => t('Allow users to modify this setting when they create a new album.'),
    '#default_value' => variable_get('photos_display_teaser_user', 1),
    '#options' => array(t('Disabled'), t('Enabled (Recommend)'))
  );
  // slideshow settings
  /*
  $form['slideshow'] = array(
    '#title' => t('Slideshow default settings'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['slideshow']['show_size'] = array(
    '#title' => t('Slide show image size'),
    '#type' => 'fieldset',
    '#weight' => 10,
    '#collapsible' => TRUE,
  );
  $form['slideshow']['photos_slide'] = array(
    '#type' => 'radios',
    '#title' => t('Slide show'),
    '#default_value' => variable_get('photos_slide', 0),
    '#description' => (!module_exists('dfgallery') ? t('Please enable <a href="@url">dfgallery</a> module', array('@url' => url('http://drupal.org/project/dfgallery'))) : ''),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#disabled' => (module_exists('dfgallery') ? FALSE : TRUE)
  );
  $form['slideshow']['photos_slide_zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide default width and height'),
    '#default_value' => variable_get('photos_slide_zoom', '640x480'),
    '#description' => t('The width and height of flash, e.g: 640x480.'),
    '#size' => '20',
    '#disabled' => (module_exists('dfgallery') ? FALSE : TRUE)
  );
  $form['slideshow']['photos_slide_music'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('photos_slide_music', FALSE),
    '#title' => t('Slide default Music'),
    '#description' => t('e.g: http://mysite/music.mp3'),
  );
  $form['slideshow']['show_size']['photos_slide_show_thumb'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails'),
    '#default_value' => variable_get('photos_slide_show_thumb', variable_get('photos_title_0', 'thumb')),
    '#options' => _photos_select_size(),
    '#disabled' => (module_exists('dfgallery') ? FALSE : TRUE)
  );
  $form['slideshow']['show_size']['photos_slide_show_view'] = array(
    '#type' => 'select',
    '#title' => t('Medium image'),
    '#default_value' => variable_get('photos_slide_show_view', $view_imagesize),
    '#options' => _photos_select_size(),
    '#disabled' => (module_exists('dfgallery') ? FALSE : TRUE)
  );
  */
  // slideshow settings end
  // count settings
  $form['count'] = array(
    '#title' => t('Statistics'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['count']['photos_image_count'] = array(
    '#type' => 'radios',
    '#title' => t('Count image views'),
    '#default_value' => variable_get('photos_image_count', 0),
    '#description' => t('Increment a counter each time image is viewed.'),
    '#options' => array( t('Enabled'), t('Disabled'))
  );
  $form['count']['photos_user_count_cron'] = array(
    '#type' => 'radios',
    '#title' => t('Image quantity statistics'),
    '#default_value' => variable_get('photos_user_count_cron', 1),
    '#description' => t('Users/Site images and albums quantity statistics.'),
    '#options' => array( t('Update count when cron runs (affect the count update).'), t('Update count when image is uploaded (affect the upload speed)'))
  );
  // count settings end
  // exif settings
  $form['exif'] = array(
    '#title' => t('Exif Settings'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#description' => t('These options require the php exif extension to be loaded.')
  );
  $form['exif']['photos_exif'] = array(
    '#type' => 'radios',
    '#title' => t('Show exif information'),
    '#default_value' => variable_get('photos_exif', 0),
    '#description' => t('When the image is available automatically read and display exif information.'),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#disabled' => (extension_loaded('exif') ? FALSE : TRUE)
  );
  $form['exif']['photos_exif_cache'] = array(
    '#type' => 'radios',
    '#title' => t('Cache exif information'),
    '#default_value' => variable_get('photos_exif_cache', 1),
    '#description' => t('Exif information cache can improve access speed.'),
    '#options' => array(t('Do not cache'), t('To database')),
    '#disabled' => (extension_loaded('exif') ? FALSE : TRUE)
  );
  $form['exif']['photos_exif_help']['#value'] = t('Custom exif. Please modify function _photos_exif_tag, at this location: .../modules/photos/inc/photos.down.inc');
  // exif settings end
  // photos swfu settings
  $form['photos_swfu'] = array(
    '#title' => t('Photos swfu'),
    '#type' => 'fieldset',
    '#description' => t('SWFUpload can provide a better upload experience (requires flash).'),
    '#collapsible' => TRUE,
  );
  $form['photos_swfu']['photos_swfu_num'] = array(
    '#type' => 'select',
    '#title' => t('Number of upload'),
    '#default_value' => variable_get('photos_swfu_num', 100),
    '#options' => drupal_map_assoc(array(1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100)),
    '#description' => module_exists('photos_swfu') ? t('Number of images allowed per upload.') : t('Please enable the photos_swfu module.'),
    '#disabled' => module_exists('photos_swfu') ? FALSE : TRUE
  );
  // photos swfu settings end
  $form['#submit'][] = 'photos_admin_settings_submit';
  $form['#validate'][] = 'photos_admin_settings_validate';
  return system_settings_form($form);
}

/**
 * Validate admin form.
 */
function photos_admin_settings_validate($form, &$form_state) {
  $size = array();
  for ($i = 0; $i < $form_state['values']['photos_thumb_count']; $i++) {
    if (isset($form_state['values']['photos_size_' . $i]) && !empty($form_state['values']['photos_size_' . $i])) {
      $array = array('%uid', '%username', '%Y', '%m', '%d');
      $topdir = current(explode('/', $form_state['values']['photos_path']));
      if (preg_match('/%uid|%username|%Y|%m|%d/i', $topdir)) {
        form_set_error('photos_path', t('Variables(%uid, %username, %Y, %m, %d) can not be on the top floor'));
        return;
      }
      if (in_array($form_state['values']['photos_size_' . $i], $size)) {
        form_set_error('photos_size_' . $i, t('Not allowed to repeat'));
        return;
      }
      $size[] = $form_state['values']['photos_size_' . $i];
    }
  }
}

/**
 * Submit handler for admin form.
 */
function photos_admin_settings_submit($form, &$form_state) {
  global $user;
  $size = array();
  for ($i = 0; $i < $form_state['values']['photos_thumb_count']; $i++) {
    if ($form_state['values']['photos_size_' . $i]) {
      $size[] = array(
        'style' => $form_state['values']['photos_size_' . $i],
        'name' => isset($form_state['values']['photos_name_' . $i]) ? $form_state['values']['photos_name_' . $i] : ''
      );
    }
  }
  variable_set('photos_size', $size);

  /* $filepath = drupal_realpath(file_default_scheme() . '://') . current(explode('/', $form_state['values']['photos_path']));
  if (!file_prepare_directory($filepath, FILE_CREATE_DIRECTORY)) {
    return false;
  }
  if ($form_state['values']['photos_access_photos']) {
    if (!is_file($filepath. '/.htaccess')) {
      drupal_set_message(t('%name creating successful', array('%name' => $filepath. '/.htaccess')));
      if ($handle = @fopen($filepath. '/.htaccess', 'wb')) {
        $str = '<FilesMatch "\.*$">Order allow,deny</FilesMatch>';
        if (fwrite($handle, $str)) {
          fclose($handle);
        }
      }
    }
  }
  elseif (is_file($filepath . '/.htaccess')) {
    file_delete($filepath . '/.htaccess');
  } */

  cache_clear_all('*', 'cache_menu', TRUE);
//  if ($form_state['values']['photos_exif_cache'] == 1) {
//    $filepath = $filepath . '/cache_exif';
//    if (!file_check_directory($filepath, FILE_CREATE_DIRECTORY)) {
//      return false;
//    }
//    if (!is_file($filepath. '/.htaccess')) {
//      drupal_set_message(t('%name creating successful', array('%name' => $filepath. '/.htaccess')));
//      if ($handle = @fopen($filepath. '/.htaccess', 'wb')) {
//        $str = '<FilesMatch "\.*$">Order allow,deny</FilesMatch>';
//        if (fwrite($handle, $str)) {
//          fclose($handle);
//        }
//      }
//    }
//  }
}

/**
 * Upload to album form.
 */
function photos_admin_import($form, &$form_state) {
  $form['pid'] = array(
    '#title' => t('Upload to album'),
    '#type' => 'select',
    '#options' => _photos_useralbum_option(),
    '#required' => TRUE,
    '#prefix' => '<div id="photos-pid">',
    '#suffix' => '</div>',
  );
  $form['url'] = array(
    '#title' => t('Filepath'),
    '#type' => 'textfield',
    '#description' => t('From the server directory into zip files, to extract. You can upload images to a directory server, enter here path, you can extract and add to the album phtos. Path such as: !zip/test.zip. Documents must be read and write, php can operate.'),
    '#required' => TRUE,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title'),
  );
  $form['des'] = array(
    '#type' => 'textarea',
    '#title' => t('Image description'),
    '#cols' => 40,
    '#rows' => 3,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm import'),
  );
  $form['#validate'] = array('photos_admin_import_validate');

  return $form;
}

/**
 * Validate upload to album form.
 */
function photos_admin_import_validate($form, & $form_state) {
  $value = new stdClass();
  $value->pid = $form_state['values']['pid'];
  $value->des = $form_state['values']['des'];
  $value->title = $form_state['values']['title'];
  if ($msg = _photos_unzip($form_state['values']['url'], $value)) {
    drupal_set_message(check_plain($msg));
  }
}