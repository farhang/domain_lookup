<?php
// $Id$

function whois_settings() {
  $form = array();

  $form['whois_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic configuration'),
    '#collapsed' => TRUE,
  );
  $form['whois_settings']['whois_output_method'] = array(
    '#type' => 'radios',
    '#title' => t('Output method'),
    '#default_value' => variable_get('whois_output_method', 'html'),
    '#description' => t('The style in which the whois results are presented to the user.'),
    '#options' => array(
      'basic' => 'Basic',
      'html' => 'HTMLized',
      'html_status' => 'HTMLized status only',
      'object' => 'PHP object',
    ),
  );
  $form['whois_settings']['whois_enable_ajax'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dynamic lookup (AJAX)'),
    '#default_value' => variable_get('whois_enable_ajax', 1),
    '#description' => t('Lookup and view the whois results dynamically (i.e. without reloading page) using AJAX request.'),
  );
  $form['whois_settings']['whois_hourly_threshold'] = array('#type' => 'select',
    '#title' => t('Hourly threshold'),
    '#options' => drupal_map_assoc(array(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59)),
    '#default_value' => variable_get('whois_hourly_threshold', 13),
    '#description' => t('The maximum number of whois lookups a user can perform per hour.'),
  );
  $form['whois_log_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log watchdog entry'),
    '#default_value' => variable_get('whois_log_watchdog', 1),
    '#description' => t('Log a watchdog entry for each whois lookup performed.'),
  );
  return system_settings_form($form);
}

