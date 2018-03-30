<?php
/**
 *The Session class is resposible for fuctions like login
 *logout
 */
 class Session {
   private $_is_logged_in = false;
   private $_id;

   function __construct(){
     session_start();
     self::_check_login();//set the attributes at the time of construction
   }

   public function redirect_to($url=null){
     if(isset($url)){
       ob_start();
       header('Location: '.$url);
       ob_end_flush();
     }
   }

   public function is_logged_in(){
     return $this->_is_logged_in;
   }

//checks the usernqme and password in db
//returns the result row in success else trows an exception.
   public function authenticate($username, $password){
     global $db;//$db is a globa variable created in pdo_connection.inc
     $username = $db->quote($username);
     $sql = "SELECT * FROM users WHERE username = ".$username." LIMIT 1";

     try {
       $result = $db->query($sql);
       $row = $result->fetch();
       if(password_verify($password, $row['password'])){
         return $row;
       }else{
         //new exception if password does not match
         throw new Exception("Password Incorrect");
       }
     } catch (Exception $e) {
       throw $e;//relay the exception from MyPDO class
     }
   }

   public function login($user_row){
     $_SESSION['is_logged_in'] = true;
   }

   public function logout(){
     unset($_SESSION['is_logged_in']);
   }

   private function _check_login(){
     if(isset($_SESSION['is_logged_in'])){
       $this->_is_logged_in = $_SESSION['is_logged_in'];
     }else{
       $this->_is_logged_in = false;
     }
   }
 }

$my_session = new Session();
?>
<?php 
/*
class Session {
  private $_is_logged_in = false;
  private $_id;

  function __construct(){
    session_start();
    self::_check_login();
  }

  private function _check_login(){
    if(isset($_SESSION['is_logged_in'])){
      $this->_is_logged_in = true;
    }else{
      $this->_is_logged_in = false;
    }
  }

  public function redirect_to($url=null){
    if(isset($url)){
      ob_start();
      header('Location: '.$url);
      ob_end_flush();
    }
  }
  public function is_logged_in(){
    return $this->_is_logged_in;
  }

  public function authunticate($username, $password){
    global $db;

    $sql  = "SELECT * FROM users WHERE username = '";
    $sql .= $username."' LIMIT 1";

    try {
      $result = $db->query($sql);
      $row = $result->fetch();
      if(password_verify($password, $row['password'])){
        return $row;
      }else{
        throw new Exception("Password does not match", 1);
      }
    } catch (Exception $e) {
      throw $e;
    }
  }
  public function login($found_user){
    $this->_is_logged_in = true;
    $_SESSION['is_logged_in'] = true;
    $_SESSION['first_name'] = $found_user['first_name'];
  }

  public function logout(){
    //$this->_is_logged_in = false;
    unset($_SESSION['is_logged_in']);
    unset($_SESSION['first_name']);
  }

}*/
?>
