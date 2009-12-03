<?php

  if (!$registered) {
    echo t('The domain %domain is free', array('%domain' => $address)) ;
  }
  else {
    echo t('The domain %domain is registered', array('%domain' => $address));
  }


