<?php
try {
  require_once '../../includes/initialize.inc';
} catch (Exception $e) {
$message = $e->getMessage();
}
?>
<?php
$message = null;
try {
  //$my_user = new User();
  $my_user = new User("Sharath", "Sahu", "ss");
  $my_user->first_name = "Raj";
  //$my_user->set_first_name('Raj12');
  $my_user->last_name = 'Sahu';
} catch (Exception $e) {
  $message = $e->getMessage();
}
?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Test User</title>
  </head>
  <body>
    <h1>Test User</h1>
    <?php echo $my_user->first_name ."<br>";?>
    <?php echo $my_user->last_name."<br>"; ?>
    <?php echo $message."<br>"; ?>
  </body>
</html>
