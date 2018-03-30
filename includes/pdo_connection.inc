<?php
/**
 * A wrapper of PDO for the desired interfaces
 */
class MyPDO extends PDO{

  function __construct($my_dsn, $my_admin, $my_password){
    parent::__construct($my_dsn, $my_admin, $my_password);
  }
  public function exec($sql){
    $m = parent::exec($sql);
    if ($m) {
      return $m;
    }else{
      throw new Exception("Query was not successful.");
    }

  }
  public function query($sql){
    $m = parent::query($sql);
    if($m->rowCount()){
      return $m;
    }else{
      throw new Exception("Query was not successful: ".$m->errorCode() );
    }
  }

  public function query1($sql){
    return parent::query($sql);
  }
}

$dsn = 'mysql:host=127.0.0.1; dbname=classuni';
$db = new MyPDO($dsn, 'myadmin@localhost', '123');
?>
