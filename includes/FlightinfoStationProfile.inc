<?php
class FlightinfoStationProfile {
  
  public static $lastAirportId;
  public static $viewsDisplays = NULL;
  public static $tabMappingsTopLevel;
  public static $tabMappingsVendors;
  public static $airportId;
  public static $tabSwitch;
  public static $selectView;
  public static $debugInfo = array();
  
  
  public $debug = array();
  public $views_displays = array();
  public $terms;
  public $display_id;
  public $view_name;
  public $airport_nid;
  public $tabMappingVendors = array();
  // public $tabSwitch;
  
  
  function __construct($airport_nid = NULL, $view_name = NULL, $display_id = NULL) {
    self::$tabSwitch = variable_get('flightinfo_station_profile_tab_switch', 1);
    self::$airportId = $airport_nid;
    
    
    
    $this->airport_nid = $airport_nid;
    
    if($this->airport_nid != FlightinfoStationProfile::$lastAirportId) {
      self::$viewsDisplays = NULL;
      self::$lastAirportId = $this->airport_nid;
    }
    
    $this->view_name = $view_name;
    $this->display_id = $display_id;
    $this->getCompanyCategories($airport_nid);
    $this->createList();
    $this->addSortedViews();
    $this->tabMappingTopLevel();
    self::$viewsDisplays = $this->views_displays;
  }
  
  function tabMappingTopLevel() {
    
    $keys = array('view_4', 'view_2', 'view');
    foreach($keys as $key) {
      $$key = $this->airport_nid . '-' . $key;
    }    
    
    $tab_mapping = array(
      $view_4 => array('open' => 'view_4', 'title' => 'Airport Info', 'close' => 'php_4'),
      $view_2 => array('open' => 'view_2', 'title' => 'AAI Contact', 'close' => 'view_2'),
      $view => array('open' => 'view', 'title' => 'Air Carrier Info', 'close' => 'view'),
    );
    self::$tabMappingsTopLevel = $tab_mapping;
  }
  
  function getCompanyCategories() {
    $vocabulary = taxonomy_vocabulary_machine_name_load('station_profile_primary_category');
    // adhd_buffer_to_dsm($vocabulary);
    $this->terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
    // dpm($terms);
  }
  
  function addSortedViews() {
    
    $debug_views = array();
    self::$debugInfo['addSortedViews'] = array();
    
    foreach($this->tids as $tid => $weight) {
        
        $term = taxonomy_term_load($tid);
        $title = $term->name;
        
        self::$debugInfo['addSortedViews'][$title] = array();
        self::$debugInfo['addSortedViews'][$title]['title'] = "$title (tid: $tid)";
        self::$debugInfo['addSortedViews'][$title]['content'] = array();
        
        $header = views_embed_view('taxonomies', 'block_1', $tid);
        
        $anchor_id = $this->airport_nid . '-' . str_replace(array(' ', '&'), array('-', ''), strtolower($title));
        $anchor = '#' . $anchor_id;
        
        // Category Companies, Airlines, Contacts, etc THIS IS SET IN THE TAXONOMY FIELDS IN THE VOCABULARY "Station Profile Primary Category" 

        $views_content_array = array();
        self::$debugInfo['addSortedViews'][$title]['content']['field_spp_frontendtab_management_values'] = array();
        
        if(is_array($term->field_spp_frontendtab_management['und'])) {
          foreach($term->field_spp_frontendtab_management['und'] as $field_spp_frontendtab_management_key => $field_spp_frontendtab_management_values) {
            
            self::$debugInfo['addSortedViews'][$title]['content']['field_spp_frontendtab_management_values'][$field_spp_frontendtab_management_key] = array();
            
            $fcid = $field_spp_frontendtab_management_values['value']; // $term->field_spp_frontendtab_management['und'][$key]['value'];
            $fc_values = entity_load_single('field_collection_item', $fcid);
            
            self::$debugInfo['addSortedViews'][$title]['content']['field_spp_frontendtab_management_values'][$field_spp_frontendtab_management_key] = $fc_values;
            
            /*
             * TODO
             * "$field_spp_frontendtab_management_values->field_fc_view_2['und'][0]['value']"
             * We may need a foreach loop if this is a multifield value we use later on...
             */
            
            $view_name = $fc_values->field_fc_view_2['und'][0]['value'];
            $display_id = $fc_values->field_fc_view_display['und'][0]['value'];
            $views_content_array[] = views_embed_view($view_name, $display_id, $this->airport_nid, $tid);
            $debug_views[] = ("section $title :: views_embed_view($view_name, $display_id, $this->airport_nid, $tid);");
            
          }
        }
        
        $views_content = implode("\r\n", $views_content_array);
        
        $this->views_displays[$tid] = array('anchor' => $anchor, 'anchor_id' => $anchor_id, 'title' => $title, 'view' => $views_content, 'header' => $header);
        
        $this->tabMappingVendors[$anchor_id] = array('open' => $anchor_id, 'title' => $title, 'close' => $anchor_id);
    }

    $this->debug['views'] = $debug_views;
    self::$debugInfo['views'] = $debug_views;
    self::$tabMappingsVendors = $this->tabMappingVendors;
  }
  
  function createList() {
 
    $tids = array();
      
    foreach($this->terms as $term) {
      // adhd_buffer_to_dsm("$key -> " . $term->name, 'dpm');
      $tids[$term->tid] = $term->weight;
    }
    asort($tids);
    $this->tids = $tids;
  }
  
  public static function selectView($view = 'airports', $current_display = NULL) {
    
    $views = views_get_all_views();
    // adhd_buffer_to_dsm_object_properties($views['airports']);
    // adhd_buffer_to_dsm($views['airports'], 'dpm');
    $options = array();
    foreach($views as $key => $view) {
      // adhd_buffer_to_dsm_object_properties($view);
      $options[$view->name] = $view->human_name . ' (' . $view->name . ')';
    }
    return $options;
  }
  
  public static function selectDisplay($view = 'airports', $display = 'page_8') {
  
    $view = views_get_view($view);
    $options = array();
    foreach ($view->display as $display_name => $display) {
      $options[$display->id] = $display->display_title . ' (' . $display->id . ')';
    }
    // adhd_buffer_to_dsm($options);
    return $options;
  }
  
  public static function selectField($view = 'airports', $display = 'page_8') {
  
    $view = views_get_view($view);
    $options = array();
    foreach ($view->display[$display]->display_options['fields'] as $field_name => $field_details) {
      $options[$field_name] = $field_details['id'] . ' (' . $field_details['ui_name'] . ')';
    }
    // adhd_buffer_to_dsm($options);
    return $options;
  }
}