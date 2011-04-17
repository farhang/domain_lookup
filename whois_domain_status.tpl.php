<?php
// $Id: whois_domain_status.tpl.php,v 1.2 2009/12/30 10:12:02 helmo Exp $

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


