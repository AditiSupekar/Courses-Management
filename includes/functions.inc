<?php
function run_query(){
  global $db;
  $message = null;
  switch ($_POST['query_type']) {
    case 'add':
      $user_type = ($_POST['user_type'] == "user") ? 'u' : 'a';
      $password = password_hash($_POST['password'], PASSWORD_DEFAULT);
      //$_POST['first_name']  = $db->quote($_POST['first_name']);
      //$_POST['last_name']   = $db->quote($_POST['last_name']);
      //$_POST['username']    = $db->quote($_POST['username']);

      $message = 'User added';
      $sql  = "INSERT INTO users (";
      $sql .= "first_name, last_name, username, password, type";
      $sql .= ") VALUES ( '";
      $sql .= $_POST['first_name'] ."', '". $_POST['last_name'] ."', '". $_POST['username']."', '". $password ."', '". $user_type."'";
      $sql .= ")";
      try {
        $db->exec($sql);
        $message = "Query Successful.";
      } catch (Exception $e) {
        $message = $e->getMessage();
      }
      break;

    case 'find':
        $message = 'user found';
        break;

    case 'delete':
          $message = 'user deleted';
          break;

  }
  return $message;
}
?>
