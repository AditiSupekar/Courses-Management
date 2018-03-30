<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Index Page</title>
    <link rel="stylesheet" href="../stylesheets/mystyle.css">
  </head>
  <body>
    <h1>Class of 2018 Pictures</h1>
    <hr>
    <h2>It's Good Time</h2>
    <hr>
    <div class="wrapper">
      <div class="outerItem" style="width:95%">
        <?php
        try {
          $photo = Photo::find_photo($_GET['photo_id']);
        } catch (Exception $e) {
          $photo_message = $e->getMessage();
        }
        ?>
        <img src="<?php echo '..'.DS.'images'.DS.$photo['file_name'];?>" width="100%">
      </div>
    </div>
    <div class="footer">
      <p>Copyrigt Dr. Zeb</p>
    </div>
  </body>
</html>
