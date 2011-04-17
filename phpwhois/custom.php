<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title>whois.php -base classes to do whois queries with php</title>
</head>
<body bgcolor="white">
<?php
  include('whois.main.php');

  $whois = new Whois();
  $query = 'minyatoor.com';
  $result = $whois->Lookup($query,false);
  echo "<pre>";
  print_r($result);
  echo "</pre>";
?>
</body>
</html>

