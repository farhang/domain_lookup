// $Id$

/**
 * Fade Transition plugin. (c) 2008 Gurpartap Singh.
 */
(function($) {
  var runonce = true;
  var saved_html = '';
  var old_html = '';
  $.fn.fadeTransition = function(options) {
      return this.each(function() {   
          $.fadeTransition(this, options);
      });
  };

  $.fadeTransition = function(container, options) {
    var settings = {
        'html':    '',
        'speed':   'normal',
        'first':   null,
        'second':  null
    };
    if (options) {
      $.extend(settings, options);
    }
    old_html = saved_html;
    saved_html = settings.html;

    var first = settings.first;
    var second = settings.second;
    var temp;

    if ((typeof first == 'undefined') || (typeof second == 'undefined')) {
      return true;
    }

    if (runonce) {
      $(container).css({'position': 'relative'});
      first.css({'z-index': '2', 'position': 'absolute', 'width': '100%'}).hide();
      second.css({'z-index': '1', 'position': 'absolute', 'width': '100%'}).hide();
      runonce = false;
    };

    setTimeout(function() {
      first.html(settings.html).fadeIn(settings.speed, function() {
				removeFilter($(this)[0]);
			});
      second.fadeOut(settings.speed, function() {
        $(this).html(settings.html);
      });

      if (settings.html.length >= old_html.length) {
        var containerHeight = first[0].offsetHeight > second[0].offsetHeight ? first[0].offsetHeight : second[0].offsetHeight;
        var containerWidth = first[0].offsetWidth > second[0].offsetWidth ? first[0].offsetWidth : second[0].offsetWidth;
      }
      else {
        var containerHeight = first[0].offsetHeight < second[0].offsetHeight ? first[0].offsetHeight : second[0].offsetHeight;
        var containerWidth = first[0].offsetWidth < second[0].offsetWidth ? first[0].offsetWidth : second[0].offsetWidth;
      }
      $(container).animate({'height': containerHeight, 'width': containerWidth});
    }, 100);

    $(first).show();

    // Interchange first and seconds.
    temp = first;
    first = second;
    second = temp;
  };

})(jQuery);

/**
 * Remove Opacity-Filter in IE.
 */
function removeFilter(element) {
	if (element.style.removeAttribute){
		element.style.removeAttribute('filter');
	}
}

Drupal.behaviors.liveWhoisPreview = function() {
  $('#whois-whois-form input#edit-whois-submit').bind('click', updateWhoisPreview);

  function updateWhoisPreview() {
    var preview_button = $(this);
    var address = $('input#edit-whois-address').val() || '';
    var captcha_response = $('input#edit-captcha-response').val() || '';
    var captcha_token = $('input#edit-captcha-token').val() || '';

    var whois_div = $('div#live-whois-preview');
    var whois_div_background = $('div#live-whois-preview-background');
    var progress_panel = $('<div class="live-progress-panel">Loading...</div>');

    $.ajax({
      type: "POST",
      url: Drupal.settings.basePath + 'index.php?q=whois',
      data: {
        address: address,
        captcha_response: captcha_response,
        captcha_token: captcha_token
      },
      dataType: 'json',
      timeout: 5000,
      beforeSend: function() {
        progress_panel.appendTo('body').hide().fadeIn(200);
      },
      success: function(data){
        if (typeof data['html'] == 'undefined' || data['html'] != 0) {
          $('div#live-preview-container').slideDown().fadeTransition({
            html: data['html'],
            first: whois_div,
            second: whois_div_background
          });
        }
        setTimeout(function() {
          progress_panel.fadeTo(500, 0, function() {
            $(this).remove();
          });
        }, 500);
      },
      error: function() {
        progress_panel.html('Error requesting data!');

        whois_div.parent().slideUp();

        setTimeout(function() {
          progress_panel.fadeTo(1500, 0, function() {
            $(this).remove();
          });
        }, 2500);
      }
    });
    return false;
  }
}
