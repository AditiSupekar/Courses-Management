<?php
/**
 *User class members to be saved in DB
 */
class User{
  protected $_id;
  protected $_first_name;
  protected $_last_name;
  protected $_username;
  protected $_password;
  protected $_type;
  protected $_comment;

  function __construct( $fname  ='',
                        $lname  ='',
                        $uname  ='',
                        $pword  ='123',
                        $ty     ='user',
                        $comm   ='No Comment.'){
    try {
      $this->__set('first_name', $fname);
      $this->__set('last_name', $lname);
      $this->__set('username', $uname);
      $this->__set('password', $pword);
      $this->__set('type', $ty);
      $this->__set('comment', $comm);
    } catch (Exception $e) {
      throw $e;
    }
  }

  public function __get($var){
    $var = '_'.$var;
    if (property_exists($this, $var)) {
      return $this->$var;
    }else {
      throw new Exception("{$var} No such Attribute1.");
    }
  }
  public function __set($var, $value){
    $var = '_'.$var;
    if (property_exists($this, $var) && $var != '_id') {
      $func = '_set'.$var;
      try {
        static::$func($value);
      } catch (Exception $e) {
        throw $e;
      }
    }else {
      throw new Exception("{$var} No such Attribute.");
    }
  }

  private function _set_first_name($value){
    if(ctype_alpha($value)){
      $this->_first_name = $value;
    }else{
      throw new Exception("first_name must be a alpha string, while {$value} is not an alpha string");
    }
  }
  private function _set_last_name($value){
    if(ctype_alpha($value)){
      $this->_last_name = $value;
    }else{
      throw new Exception("last_name must be a alpha string, while {$value} is not an alpha string");
    }
  }
  private function _set_username($value){
    if(!empty($value)){
      $this->_username = $value;
    }else{
      throw new Exception("username must be a nonempty string");
    }
  }
  private function _set_password($value){
    if(!empty($value)){
      $this->_password = $value;
    }else{
      throw new Exception("password must be a nonempty string");
    }
  }
  private function _set_type($value){
    if($value == 'user' || $value == 'admin'){
      $this->_type = $value;
    }else{
      throw new Exception("Not a valid use type");
    }
  }
  private function _set_comment($value){
    $this->_comment = $value;
  }

  public function db_functions($var){
    $func = '_'.$var.'_user';
      try {
        return static::$func();//it will execute the corresponding function
      } catch (Exception $e) {
        throw $e;
      }
  }
  private function _add_user(){
    global $db;
    $user_type = ($this->_type == "user") ? 'u' : 'a';
    $password = password_hash($this->_password, PASSWORD_DEFAULT);
    $first_name  = $db->quote($this->_first_name);
    $last_name   = $db->quote($this->_last_name);
    $username    = $db->quote($this->_username);
    $comment     = $db->quote($this->_comment);

    $sql = "SELECT * FROM users WHERE username = '".$this->_username."' LIMIT 1";

    if(!$db->query1($sql)->rowCount()){
      $sql  = "INSERT INTO users (";
      $sql .= "first_name, last_name, username, password, type, comment";
      $sql .= ") VALUES ( ";
      $sql .= $first_name .", ". $last_name .", ". $username.", '". $password ."', '". $user_type."'," .$comment;
      $sql .= ")";
      try {
        $db->exec($sql);
        return "User with username ".$username." added, query Successful.";
      } catch (Exception $e) {
        throw $e;
      }
    }else{
      throw new Exception("The username ".$this->_username. " alrady exists");
    }
  }
  private function _delete_user(){
    global $db;
    $sql  = "DELETE FROM users WHERE username = '".$this->_username."' LIMIT 1";
    try {
      $db->exec($sql);
      return 'User with Username '.$this->_username.' deleted from DB';
    } catch (Exception $e) {
      return $e;
    }
  }
  private function _find_user(){
    global $db;
    $message = null;
    $sql = "SELECT * FROM users WHERE username = '".$this->_username."' LIMIT 1";
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
          <td>{$row['last_name']} </td>
          <td>{$row['username']}</td>
          <td>{$row['type']}</td>
        </tr>
      </table>
      ";
      return $message;
    } catch (Exception $e) {
      throw $e;
    }
  }
}

/*
public function set_first_name($value=''){
  if(ctype_alpha($value)){
    $this->_first_name = $value;
  }else{
    throw new Exception("first_name must be a alpha string, while {$value} is not an alpha string");
  }

}*/
/*
public function get_first_name(){
  return $this->_first_name;
}*/
/*
public function __set($var, $value){
  $var = '_'.$var;
  switch ($var) {
    case '_first_name':
      if(ctype_alpha($value)){
        $this->_first_name = $value;
      }else{
      throw new Exception("first_name must be a alpha string, while {$value} is not an alpha string");
      }
      break;
    case '_last_name':
      if(ctype_alpha($value)){
        $this->_last_name = $value;
      }else{
        throw new Exception("last_name must be a alpha string, while {$value} is not an alpha string");
      }
      break;
    case '_username':
      if(!empty($value)){
        $this->_username = $value;
      }else{
        throw new Exception("username must be a nonempty string");
      }
      break;
    case '_password':
      if(!empty($value)){
        $this->_password = $value;
      }else{
        throw new Exception("password must be a nonempty string");
      }
      break;
    case '_type':
      if($value == 'user' || $value == 'admin'){
        $this->_type = $value;
      }else{
        throw new Exception("Not a valid use type");
      }
      break;
    case '_comment':
        $this->_comment = $value;
        break;
    default:
      throw new Exception("No such Attribute");
      break;
  }
}//*/
/*
function __construct(){
  # code...
}*/
?>
