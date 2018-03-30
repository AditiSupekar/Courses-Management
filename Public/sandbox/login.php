<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
if($my_session->is_logged_in()){
  $my_session->redirect_to('index.php');
}
if(isset($_POST['login'])){
  $username = trim($_POST['username']);
  $password = $_POST['password'];

  try {
    $row = $my_session->authenticate($username, $password);
    $my_session->login($row);
    $my_session->redirect_to('index.php');
  } catch (Exception $e) {
    $message = $e->getMessage();
  }
}
$rand = rand();
$_SESSION['rand'] = $rand;
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
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
          <h2>Login</h2>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>" method="post" id="login_form">
            <input type="hidden" name="rand1" value="<?php echo $rand ?>">
            <input type="text" name="username" placeholder="Username" required>
            <input type="password" name="password" placeholder="Password">
            <button type="submit" name="login">Login</button>
          </form>
          <?php echo isset($message) ? $message: null; ?>
        </div>
        <div class="innerItem">
          <h2>Users</h2>

        </div>
        <div class="innerItem">
          <h2>Add Media</h2>
        </div>
      </div>
      <div class="outerItem">
        <p>We will use it</p>
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
