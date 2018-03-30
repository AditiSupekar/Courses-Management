<?php
/**
 *This class is responsible for all the user related functions
*/
class User{
  protected $_id;
  protected $_first_name;
  protected $_last_name;
  protected $_username;
  protected $_password;
  protected $_type;
  protected $_comment;

  function __construct( $first_name='',
                        $last_name='',
                        $username='',
                        $password='',
                        $type='',
                        $comment=''){
    try {
      $this->__set('first_name', $first_name);
      $this->__set('last_name', $last_name);
      $this->__set('username', $username);
      $this->__set('password', $password);
      $this->__set('type', $type);
      $this->__set('comment', $comment);
    } catch (Exception $e) {
      throw $e;
    }
  }

  public function __set($name, $value){
    $name = '_'.$name;
    switch ($name) {
      case '_first_name':
        $this->_first_name = $value;
        break;
      case '_last_name':
        $this->_last_name = $value;
        break;
      case '_username':
        $this->_username = $value;
        break;
      case '_password':
        $this->_password = $value;
        break;
      case '_type':
        $this->_type = $value;
        break;
      case '_comment':
        $this->_comment = $value;
        break;
      default:
        throw new Exception('No such attrib.');
        break;
    }
  }

  public function __get($name){
    $protected_attrib = '_'.$name;
    if(property_exists($this, $protected_attrib)){
      return $this->$protected_attrib;
    } else {
      throw new Exception('No such attrib.');
    }
  }

  public function db_function($type){
    switch ($type) {
      case 'add':
        return $this->insert();
        break;
      case 'find':
        return $this->find();
        break;
      case 'delete':
        return $this->delete();
        break;
    }
  }

  private function insert(){
    global $db;
    $password = password_hash($this->password, PASSWORD_DEFAULT);
    $user_type = ($this->_type == 'user') ? 'u' : 'a';

    $sql  = "INSERT INTO users ";
    $sql .= "(first_name, last_name, username, password, user_type )";
    $sql .= "VALUES ('";
    $sql .= $this->_first_name ."', '". $this->_last_name."', '". $this->_username."', '". $password."', '". $user_type."'";
    $sql .= ")";
    try {
      $db->exec($sql);
      return 'User with Username '.$this->_username.' created in DB';
    } catch (Exception $e) {
      return $e->getMessage();
    }

  }

  private function find(){
    global $db;

    $sql  = "SELECT * FROM users WHERE username = '".$this->_username."' LIMIT 1";
    try {
      $result = $db->query($sql);
      $row1 = $result->fetch();
      //$row1 = null;
      //foreach ($result as $row) {
        //$row1 = $row;
      //}
      $message = "
      <table>
        <tr>
          <th>First Name</th>
          <th>Last Name</th>
          <th>Username</th>
          <th>User Type</th>
        </tr>
        <tr>
          <td>{$row1['first_name']}</td>
          <td>{$row1['last_name']} </td>
          <td>{$row1['username']}</td>
          <td>{$row1['user_type']}</td>
        </tr>
      </table>
      ";
      return $message;
    } catch (Exception $e) {
      return $e->getMessage();
    }
  }

  private function delete(){
    global $db;
    $sql  = "DELETE FROM users WHERE username = '".$this->_username."' LIMIT 1";
    try {
      $db->exec($sql);
      return 'User with Username '.$this->_username.' deleted from DB';
    } catch (Exception $e) {
      return $e->getMessage();
    }

  }

  private function instanciate($record){
    $user = new static;
    foreach ($record as $key => $value) {
      $key = '_'.$key;
      $user->$key = $value;
    }
    return $user;
  }

}


?>
