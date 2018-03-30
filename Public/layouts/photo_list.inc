<?php
try {
  $rows = Photo::find_all_photos();
  foreach ($rows as $value):
  ?>
  <table width="100%">
    <tr>
      <td width="30%" rowspan="3">
        <a href="
                <?php
                  if(strtolower($_SERVER['SCRIPT_FILENAME']) == strtolower(ADMIN_PATH)){
                    echo '..'.DS.'common'.DS.'image.php?photo_id='.$value['photo_id'];
                  }else{
                    echo 'image.php?photo_id='.$value['photo_id'];
                  }
                ?>
        ">
          <img src="<?php echo '..'.DS.'images'.DS.$value['file_name']?>" width="100%">
        </a>
      </td>
      <td colspan="3"><?php echo  $value['photo_name']?></td>
    </tr>
    <tr>
      <td colspan="3"><?php echo  $value['photo_caption']?></td>
    </tr>
    <tr>
      <td><?php echo  $value['file_size']?></td>
      <td><?php echo  $value['user_id']?></td>
      <td>
        <?php
          if(strtolower($_SERVER['SCRIPT_FILENAME']) == strtolower(ADMIN_PATH)){
            echo '<a href="delete_photo.php?photo_id='. $value['photo_id'].'">Delete</a>';
          }
        ?>
      </td>
    </tr>

  </table>
  <hr>
<?php endforeach;

} catch (Exception $e) {
$photo_message = $e->getMessage();
}?>
