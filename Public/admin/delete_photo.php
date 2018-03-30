<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
if($my_session->is_logged_in()){
  try {
    $_SESSION['delete_message'] = Photo::delete_photo($_GET['photo_id']);
  } catch (Exception $e) {
    $_SESSION['delete_message'] = $e->getMessage();
  }
}
$my_session->redirect_to('index.php');
?>
