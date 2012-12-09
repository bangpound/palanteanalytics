<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Detail'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Entity'), 'entity'),
);

/**
 * Output function for the 'block' content type. Outputs a block
 * based on the module and delta supplied in the configuration.
 */
function palanteanalytics_detail_content_type_render($subtype, $conf, $panel_args, $context) {
  $uri = entity_uri('node', $context->data);
  $path = url($uri['path'], $uri['options']);

  module_load_include('inc', 'google_analytics_reports', 'google_analytics_reports.pages');

  $report = array(
    'pageviews_chart' => _google_analytics_reports_pageviews($path),
    'stats' => _google_analytics_reports_detail_stats($path),
    'referrals' => _google_analytics_reports_top_referrals($path),
    'keywords' => _google_analytics_reports_top_keywords($path),
  );
  if (in_array(FALSE, $report, TRUE)) {
    drupal_set_message(_google_analytics_reports_error_message(), 'error');
    return ' ';
  }

  $block->title = t('Content detail: @path', array('@path' => $path));
  $block->content = theme('google_analytics_reports_detail', $report);

  return $block;
}

/**
 * Empty form so we can have the default override title.
 */
function palanteanalytics_detail_content_type_edit_form($form, &$form_state) {
  // Does nothing!
  return $form;
}
