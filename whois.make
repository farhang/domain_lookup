; Drush_make file for the whois module

; On it's own this file has little meaning. However it is very useful when a larger makefile 
; is used to build a drupal platform. This makefile is automatically included due to the recursive behavior.
; See http://drupal.org/project/drush_make

api = 2
core = 6.x

; Library required to do the actual whois lookup
libraries[phpwhois][download][type] = "get"
libraries[phpwhois][destination] = "modules/whois"
libraries[phpwhois][directory_name] = "phpwhois"

; Download link from http://sourceforge.net/projects/phpwhois/
libraries[phpwhois][download][url] = "http://downloads.sourceforge.net/project/phpwhois/phpwhois/phpwhois-4.2.0/phpwhois-4.2.0.tar.gz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fphpwhois%2F"


