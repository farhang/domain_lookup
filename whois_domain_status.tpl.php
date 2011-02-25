<?php

/**
 * @file
 * Template for the Whois module's output method 'HTMLized status only'.
 */


  if (!$registered) {
    echo t('The domain %domain is free', array('%domain' => $address)) ;
  }
  else {
    echo t('The domain %domain is registered', array('%domain' => $address));
  }


