<?php
// $Id$


function whois_whois_page() {
  if (!user_access('access whois')) {
    return;
  }

  $output = '';
  $address = $_POST['address'] ? $_POST['address'] : arg(1);

  if (isset($address)) {
    // Check for hourly threshold.
    if (flood_is_allowed('whois', variable_get('whois_hourly_threshold', 13))) {
      $output .= whois_display_whois($address);
    }
    else {
      $output .= t("You cannot do more than %number whois lookups per hour. Please try again later.", array('%number' => variable_get('whois_hourly_threshold', 13)));
    }
    if (isset($_POST['address'])) {
      // Avoid debug information(devel.module) from being added to the preview.
      $GLOBALS['devel_shutdown'] = FALSE;

      // Stop further processing and return requested data.
      exit(drupal_json(array('html' => $output)));
    }
    drupal_set_breadcrumb(array(l(t('Home'), '<front>'), l(t('Whois lookup'), 'whois')));
  }
  // Load JS and CSS for dynamic lookups using AJAX.
  if (variable_get('whois_enable_ajax', 1)) {
    $path = drupal_get_path('module', 'whois');
    drupal_add_js($path . '/whois.js');
    drupal_add_css($path . '/whois.css');
  }

  return drupal_get_form('whois_whois_form') . '<div id="live-preview-container"><div id="live-whois-preview">' . $output . '</div><div id="live-whois-preview-background"></div></div>';
}

/**
 * Implementation of hook_form().
 */
function whois_whois_form() {
  $form = array();

  $form['whois_lookup'] = array(
    '#type' => 'fieldset',
    '#collapsed' => TRUE,
  );
  $form['whois_lookup']['whois_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Lookup address'),
    '#default_value' => arg(1),
    '#required' => TRUE,
    '#prefix' => '<div class="container-inline">',
  );
  $form['whois_lookup']['whois_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Lookup'),
    '#suffix' => '</div>',
  );
  $form['whois_lookup']['whois_description'] = array(
    '#value' => '<div class="description" style="margin: 0;">' . t('Enter a domain name or IP address for <em>whois</em> information.') . '</div>',
  );

  return $form;
}


function whois_whois_form_submit($form, &$form_state) {
  global $user;
  $address = $form_state['values']['whois_address'];

  $address = _whois_cleanup_address($address);

  $form_state['redirect'] = check_url('whois/' . $address);
  return;
}

