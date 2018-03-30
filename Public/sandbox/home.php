<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
if(isset($_POST['user_management'])){
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

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
    <!--
    <link rel="stylesheet" href="../stylesheets/mystyle.css">
  -->
  </head>
  <body>
    <h1>Class of 2018 Pictures</h1>
    <hr>
    <h2>It's Good Time</h2>
    <hr>
    <div class="wrapper">
      <div class="container">
        <div class="innerItem">
          <h2>Login</h2>
        </div>
        <div class="innerItem">
          <h2>Users</h2>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" method="post" id="user_form">
            <input type="text" name="first_name" placeholder="First Name">
            <input type="text" name="last_name" placeholder="Last Name">
            <br>
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password">
            <br>

            <input type="radio" name="type" value="user" checked> User
            <input type="radio" name="type" value="admin"> Admin

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
        </div>

      </div>

      <div class="outerItem">
        <p>We will use it later.</p>
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
