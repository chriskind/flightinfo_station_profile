<?php
/**
 *  Field formatter for phone number station profile.
 */
?>

<?php foreach($rows as $row): ?>
  <div class=phone-numbers">
  <?php if(!empty($row['field_type'])) { ?>
    <span><?php print $row['field_type']; ?>: </span>
  <?php } else { ?>
    <span>Phone: </span>
  <?php } ?>
    
  <span class="value"><?php print $row['field_phone_number_string']; ?> </span>
  <span class="value"><?php print $row['field_additional_descriptor']; ?> </span>
  </div>
<?php endforeach; ?> 