<?php
/**
 *  Field formatter for phone number station profile.
 */
$address_fields = array(
  'top_lines' => array(
    'name_line', 
    'first_name', 
    'last_name', 
    'organisation_name',
  ),
  
  'basic' => array(
    'thoroughfare',
    'locality',
    'administrative_area',
    'postal_code',
  )
);

$basic = 'N';

?>
<?php // adhd_buffer_to_dsm($rows, 'dpm')?>
<?php foreach($rows as $row) { ?>
  
    <?php
      foreach($address_fields['basic'] as $line) {
        if(!empty($row['field_fc_address'][$line])) {
          $basic = 'Y';
        }
      }
      
    ?>
  
  
  
  <div class="address-type">
  <?php // adhd_buffer_to_dsm($row)?>
  <?php if(!empty($row['field_fc_address_type']) && $basic == 'Y') { ?>
    <?php foreach($row['field_fc_address_type'] as $type) {?>
      <span><?php print $type->name; ?></span>
    <?php } ?>
  <?php } ?>
  </div>
  
  
  <div class="address-values">
  <?php if(!empty($row['field_fc_address'])) { ?>
    <?php
      foreach($address_fields['top_lines'] as $line) {
        if(!empty($row['field_fc_address'][$line])) {
          $top_line = 'Y';
        }
      }
      
      if($top_line == 'Y') {
     ?>
        <div><?php print $row['field_fc_address']['organisation_name']?></div>
        <div><?php print $row['field_fc_address']['name_line']?></div>
        <div><?php print $row['field_fc_address']['first_name']?> <?php print $row['field_fc_address']['last_name']?></div>
    <?php } ?>
       
    <?php if($basic == 'Y') { ?>
    <div><?php print $row['field_fc_address']['thoroughfare']?></div>
    <div><?php print $row['field_fc_address']['locality']?>, <?php print $row['field_fc_address']['administrative_area']?> <?php print $row['field_fc_address']['postal_code']?></div>
    
    <?php } ?>
  
  <?php } ?>
  </div>
<?php } ?>