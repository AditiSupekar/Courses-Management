<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
if(isset($_POST['user_management'])){
  $sql = "SELECT * FROM users WHERE username = '".$_POST['username']."'";
  try {
    $result = $db->query($sql);
    $row = $result->fetch();
    $message = "
    <table>
      <tr>
        <th>First Name</th>
        <th>Last Name</th>
        <th>Username</th>
        <th>User Type</th>
      </tr>
      <tr>
        <td>{$row['first_name']}</td>
        <td>{$row['last_name']}</td>
        <td>{$row['username']}</td>
        <td>{$row['type']}</td>
      </tr>
    </table>
    ";
  } catch (Exception $e) {
    $message = $e->getMessage();
  }

}
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Tutorial</title>
    <link rel="stylesheet" href="../stylesheets/mystyle.css">
  </head>
  <body>
    <h1>Tutorial</h1>
    <div class="wrapper">
      <div class="container">
        <div class="innerItem">
          <h2>Logout</h2>
        </div>

        <div class="innerItem">
          <h2>User Management</h2>
          <form action="<?php echo $_SERVER['PHP_SELF']?>" method="post" id="user_management">
            <input type="text" name="first_name" placeholder="First Name">
            <input type="text" name="last_name" placeholder="Last Name"> <br>
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password" placeholder="Password"><br>

            <input type="radio" name="user_type" value="user" checked>User
            <input type="radio" name="user_type" value="admin">Admin

            <select name="query_type" form="user_management">
              <option value="add_user">Add User</option>
              <option value="find_user" selected>Find User</option>
              <option value="delete_user">Delete User</option>
            </select><br>
            <button type="submit" name="user_management">Submuit</button>
          </form>
          <?php echo isset($message) ? $message : null;?>
        </div>

        <div class="innerItem">
          <h2>Contents Management</h2>
        </div>

      </div>

      <div class="outerItem">
        <?php

          echo "<h2>_POST</h2>";

          foreach ($_POST as $key => $value) {
            echo '<p>'.$key.': ' . $value.'</p>' ;
          }

         ?>
      </div>

      <div class="outerItem">
        <?php
        echo "<h2>_SERVER</h2>";
          foreach ($_SERVER as $key => $value) {
            echo '<p>'.$key.': ' . $value.'</p>' ;
          }
        ?>

      </div>

    </div>

    <div class="footer">
      <p>copy right Dr. Zeb</p>
    </div>

  </body>
</html>
