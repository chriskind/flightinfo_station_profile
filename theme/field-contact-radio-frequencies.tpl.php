<?php
/**
 *  Field formatter for phone number station profile.
 */
?>

<?php foreach($rows as $row): ?>
  <div class=radio-frequencies">
  <?php if(!empty($row['field_fc_radio_name_used_for'])) { ?>
    <span><?php print $row['field_fc_radio_name_used_for']; ?>: </span>
  <?php } else { ?>
    <span>Radio Frequency: </span>
  <?php }?>
  
  <span class="value"><?php print $row['field_fc_radio_frequency']; ?> </span>
  </div>
<?php endforeach; ?> 