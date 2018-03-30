<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
if(isset($_POST['logout']) || !$my_session->is_logged_in()){
  $my_session->logout();
  $my_session->redirect_to('login.php');
}
if(isset($_POST['user_management']) &&  $_POST['rand'] == $_SESSION['rand']){
  try {
    $my_user = new User(  $_POST['first_name'],
                          $_POST['last_name'],
                          $_POST['username'],
                          $_POST['password'],
                          $_POST['type']);
    $message = $my_user->db_functions($_POST['query_type']);//run_query();
  } catch (Exception $e) {
    $message = $e->getMessage();
  }
}
if(isset($_POST['upload_file']) && $_POST['rand'] == $_SESSION['rand']){
  try {
    $my_photo = new Photo(  $_POST['photo_name'],
                            $_POST['photo_caption'],
                            $_FILES['uploaded_file']['name'],
                            $_FILES['uploaded_file']['size'],
                            $_FILES['uploaded_file']['type']
    );
    $my_photo->save($_FILES['uploaded_file']['tmp_name']);
    if(!$_FILES['uploaded_file']['error']){
      $file_message = 'Photo with name '.$my_photo->photo_name.' saved successfully by user_id:'. $my_photo->user_id;
    }else{
      $file_message = 'File could not be uploaded due to :'.$_FILES['uploaded_file']['error'].': '.$my_photo->upload_error[$_FILES['uploaded_file']['error']];
    }

  } catch (Exception $e) {
    $file_message = $e->getMessage();
  }
}
$rand = rand();
$_SESSION['rand'] = $rand;
?>
<?php ?>
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
      <div class="container">
        <div class="innerItem">
          <h2>Logout</h2>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" method="post" id="logout_form">
            <input type="hidden" name="rand1" value="<?php echo $rand ?>">
            <button type="submit" name="logout">Logout</button>
          </form>
        </div>
        <div class="innerItem">
          <h2>Users</h2>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" method="post" id="user_form">
            <input type="hidden" name="rand" value="<?php echo $rand ?>">
            <input type="text" name="first_name" placeholder="First Name">
            <input type="text" name="last_name" placeholder="Last Name">
            <br>
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password">
            <br>

            <input type="radio" name="type" value="user" id="user" checked>
            <label for="user">User</label>
            <input type="radio" name="type" value="admin" id="admin">
            <label for="admin">Admin</label>
            <select name="query_type" form="user_form">
              <option value="add">Add User</option>
              <option value="find" selected>Find User</option>
              <option value="delete">Delete User</option>
            </select>
            <br>
            <button type="submit" name="user_management">Submit</button>
          </form>
          <?php echo isset($message) ? $message: null; ?>
        </div>
        <div class="innerItem">
          <h2>Add Media</h2>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" enctype="multipart/form-data" method="post">
            <input type="hidden" name="rand" value="<?php echo $rand ?>">
            <input type="hidden" name="MAX_FILE_SIZE" value="1000000">
            <input type="file" name="uploaded_file" required>
            <input type="text" name="photo_name" placeholder="Photo Name" required><br>
            <input type="text" name="photo_caption" placeholder="Photo Caption" required>
            <input type="submit" name="upload_file" value="Upload File">
          </form>
          <?php echo isset($file_message) ? $file_message : null; ?>
        </div>

      </div>

      <div class="outerItem">

        <?php
        $photos = Photo::find_all_photos();
        foreach ($photos as $photo): ?>
        <table width='100%'>
          <tr>
            <td rowspan="3" width="30%"><img src="<?php echo '..'.DS.'images'.DS.$photo['file_name']; ?>" width="100%"></td>
            <td colspan="3"><?php  echo $photo['photo_name']; ?></td>
          </tr>
          <tr>
            <td colspan="3"><?php  echo $photo['photo_caption']; ?></td>
          </tr>
            <td><?php  echo $photo['file_size']; ?></td>
            <td><?php  echo $photo['user_id']; ?></td>
            <td><a href="delete_photo.php?id=<?php echo $photo['user_id'];?>">Delete</a></td>
          </tr>
          </table>
          <hr>
          <?php endforeach; ?>

      </div>

      <div class="outerItem">
        <?php
          for($i=0; $i<20; $i++){
            echo "<p>We will use it later.</p>";
          }
        ?>
      </div>
    </div>
    <div class="footer">
      <p>Copyrigt Dr. Zeb</p>
    </div>
  </body>
</html>
