<?php
try {
  require_once '../../includes/initialize.inc';

} catch (Exception $e) {

}
?>
<?php
if(isset($db)){
  echo '<p>The connection was successful</p>';

  $connection_methods = get_class_methods("PDOStatement");
  //$connection_methods = get_class_methods($db);

  foreach ($connection_methods as $value) {
    echo '<p>'.$value.'</p>';
  }

}else{
  echo '<p>The connection was unsuccessful</p>';
}

?>
