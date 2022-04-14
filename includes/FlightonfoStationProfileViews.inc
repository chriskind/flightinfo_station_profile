<?php

class FlightonfoStationProfileViews {
  
  function __construct() {
    
  }

  /*
   * Debugging utilities
   */
  
  function add_link_to_view_edit_with_context($view, $options = array()) {
  
    $current_display = $view->current_display;
    $current_display_title = $view->display[$current_display]->display_title;
    
    $get_vars_array_name =  flightinfo_station_profile_return_default_variable($view, $return = 'name');  
    $string = '';
    $i = 0;
    
    foreach ($view->argument as $id => $arg) {
      $glue = '?';
      $pos = $arg->position;
      if($i > 0) {
        $glue = '&';
      }
      $string .= $glue . $get_vars_array_name . $id . '=' . $view->args[$pos];
      $i = $i+1;
    }
      
    global $base_url;
    $edit_view_link_args = '<a href="' . $base_url . '/admin/structure/views/view/' . $view->name . '/' . $view->current_display . '/edit' . $string . '" target="_blank" class="overlay-exclude">Edit: ' . $view->name . ' => ' . $current_display_title . '</a>';
    
    $edit_view_link_location = variable_get('flightinfo_station_profile_views_edit_links', 'off');
    if(adhd_messages_allowed($options) === TRUE && ($edit_view_link_location == 'top' | $edit_view_link_location == 'both')) {
      adhd_buffer_to_dsm($edit_view_link_args, 'drupal_set_message');
    }
    
    if(adhd_messages_allowed($options) === TRUE && ($edit_view_link_location == 'bottom' | $edit_view_link_location == 'both')) {
      return $edit_view_link_args; // $edit_view;
    }
  }
  
  
  function views_default_getter($variable = NULL) {
    $options['module_debug'] = '1' ;
    if(adhd_messages_allowed($options) === TRUE && variable_get('flightinfo_station_profile_views_debug', 0) == 1) {
      return variable_get($variable);
    } else {
      return NULL;
    }
  }
  
  
  function views_default_setter($variable = NULL, $value = NULL) {
    variable_set($variable, $value);
  }
  
  
  function return_default_variable(&$view, $return = 'value', $id = NULL) {
    $var_prefix = 'flightinfo_station_profile_views_default';
    $get_vars_array_name =  'view_arg_vars';  
    $variable_name = $var_prefix . '__' . $view->current_display . '__' . $get_vars_array_name . '__' . $id; // . $view->current_display;
  
    
    if($return == 'value') {
      return flightinfo_station_profile_views_default_getter($variable_name);
    }
    
    return $variable_name;
  }

  
  function debug($options = NULL) {
    // adhd_buffer_to_dsm($airport_nid);
    // adhd_buffer_to_dsm($FlightinfoStationProfile->terms);
    // adhd_buffer_to_dsm($FlightinfoStationProfile->tids);
    // adhd_buffer_to_dsm($FlightinfoStationProfile->views_displays, 'dpm');
    // adhd_buffer_to_dsm(($FlightinfoStationProfile->debug));
    // adhd_buffer_to_dsm((FlightinfoStationProfile::$viewsDisplays));
    // adhd_buffer_to_dsm(FlightinfoStationProfile::$tabMappingsVendors);
  }
  

  /*
 * Standard drupal HOOK_views implementations...
 */
  
  function views_pre_view(&$view, $display_id, $args) {
    // adhd_buffer_to_dsm($view->current_display, 'drupal_set_message');
    // adhd_buffer_to_dsm($_GET, 'dsm');
    if($view->name == 'airports') {
      
      $get_key = flightinfo_station_profile_return_default_variable($view, 'name');
      
      foreach($_GET as $_get_key => $value) {
        if(strpos($_get_key, 'flightinfo_station_profile_views_default__') !== FALSE) {
          flightinfo_station_profile_views_default_setter($_get_key, $value);
        }
      }
      $debug_displays = array('page_5' , 'block_5', 'block_7', 'block_9', 'block_8');
        if(in_array($view->current_display, $debug_displays)) {
      }
    }
  }
  
  
  
  
  function views_pre_execute($view) {
    
     // adhd_buffer_to_dsm($view->current_display);
    if($view->name == 'airports') {
      // adhd_buffer_to_dsm($query);
      $debug_displays = array('page_5' , 'block_5', 'block_7', 'block_9', 'block_8');
        if(in_array($view->current_display, $debug_displays)) {
          // adhd_buffer_to_dsm($view->current_display, 'drupal_set_message');
          // adhd_buffer_to_dsm($query);
          // adhd_buffer_to_dsm($_GET, 'dsm');
          // adhd_buffer_to_dsm($view->argument['nid']->value[0], 'dsm');
          // $view->argument['nid']->value[] = 7292;
          // adhd_buffer_to_dsm($view->argument['nid']->value[0], 'dsm');
       }
     }
  }
  
  
  
  function views_pre_render(&$view) {
    if($view->name == 'airports') {
      
      // $FlightinfoStationProfile = new FlightinfoStationProfile($airport_nid, $view_name, $display_id);
      
      $debug_displays = array('page_5', 'block_5', 'block_7', 'block_9', 'block_10');
      // $debug_displays = array('block_5');
      
      if(in_array($view->current_display, $debug_displays)) {
        flightinfo_Station_add_link_to_view_edit_with_context($view);
      }
    }
  }
  
