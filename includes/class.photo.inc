<?php
/**
 *User class members to be saved in DB
 */

 class Photo{
   protected $_photo_id;
   protected $_photo_name;//get from the user
   protected $_photo_caption;//get from the user
   protected $_file_name;//orignal name + some unique extension
   protected $_file_size;
   protected $_file_type;
   protected $_user_id;//coming from the users

   public $upload_error = array(
     UPLOAD_ERR_OK => "No Errors.",
     UPLOAD_ERR_INI_SIZE => "Larger than the Max File Size.",
     UPLOAD_ERR_FORM_SIZE => "Larger than the Max of Form File Size.",
     UPLOAD_ERR_PARTIAL => "Partial upload.",
     UPLOAD_ERR_NO_FILE => "No FILE.",
     UPLOAD_ERR_NO_TMP_DIR => "No Temporary directory.",
     UPLOAD_ERR_CANT_WRITE => "Cannot write to the disk.",
     UPLOAD_ERR_EXTENSION => "File upload stopped by extension."
   );

   function __construct( $photo_name     ='',
                         $photo_caption  ='',
                         $file_name      ='',
                         $file_size      =0,
                         $file_type      ='',
                         $user_id        =17){
     try {
       $this->__set('photo_name', $photo_name);
       $this->__set('photo_caption', $photo_caption);
       $this->__set('user_id', $user_id);//this one is out of order why?
       $this->__set('file_name', $file_name);
       $this->__set('file_size', $file_size);
       $this->__set('file_type', $file_type);
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
     if (property_exists($this, $var) && $var != '_photo_id') {
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

   private function _set_photo_name($value){
     if(isset($value)){
       $this->_photo_name = $value;
     }else{
       throw new Exception("photo_name must be a alpha string, while {$value} is not an alpha string");
     }
   }
   private function _set_photo_caption($value){
     if(!empty($value)){
       $this->_photo_caption = $value;
     }else{
       throw new Exception("photo_caption must be a nonempty string");
     }
   }
   private function _set_file_name($value){
     if(1){
       $value = 'file_by_'.$this->_user_id.'_at_'.date('c').'_'.($value);
       $this->_file_name = $value;
     }else{
       throw new Exception("file_name must be a nonempty string");
     }
   }
   private function _set_file_size($value){
     if(is_int($value)){//additional checks on the max size must be imposed
       $this->_file_size = $value;
     }else{
       throw new Exception("file_size must be a number");
     }
   }
   private function _set_file_type($value){
     if(!empty($value)){
       $this->_file_type = $value;
     }else{
       throw new Exception("file_type must be a nonempty string");
     }
   }
   private function _set_comment($value){
     $this->_comment = $value;
   }
   private function _set_user_id($value){
     $this->_user_id = $value;
   }

   public  function db_functions($var){
     $func = '_'.$var.'_photo';
       try {
         return static::$func();//it will execute the corresponding function
       } catch (Exception $e) {
         throw $e;
       }
   }
   private function _add_photo(){
     global $db;

     $photo_name      = $db->quote($this->_photo_name);
     $photo_caption   = $db->quote($this->_photo_caption);
     $file_name       = $db->quote($this->_file_name);
     $file_type       = $db->quote($this->_file_type);

     $sql = "SELECT * FROM photos WHERE file_name = ".$file_name." LIMIT 1";

     if(!$db->query1($sql)->rowCount()){
       $sql  = "INSERT INTO photos (";
       $sql .= "photo_name, photo_caption, file_name, file_size, file_type, user_id";
       $sql .= ") VALUES ( ";
       $sql .= $photo_name .", ". $photo_caption .", ". $file_name.", ". $this->_file_size .", ". $file_type."," .$this->_user_id;
       $sql .= ")";
       try {
         $db->exec($sql);
         return "Photo with name ".$photo_name." added, query Successful.";
       } catch (Exception $e) {
         throw $e;
       }
     }
     else{
       throw new Exception("The file name ".$file_name. " alrady exists");
     }
   }
   public static function delete_photo($id){
     global $db;
     $sql1 = "SELECT * FROM photos WHERE photo_id = ".$id." LIMIT 1";
     $sql  = "DELETE FROM photos WHERE photo_id = '".$id."' LIMIT 1";
     try {
       if($db->query($sql1)){
         $row = static::find_photo($id);
         unlink(IMG_PATH.DS.$row['file_name']);
         $db->exec($sql);
         return 'Photo with ID '.$id.' deleted from DB';
       }else{
         throw new Exception("File could not be deleteed");
       }
     } catch (Exception $e) {
       return $e;
     }
   }

   public static function find_photo($id){
     global $db;
     $message = null;
     $sql = "SELECT * FROM photos WHERE photo_id = '".$id."' LIMIT 1";
     try {
       $result = $db->query($sql);
       $row = $result->fetch();
       return $row;
     } catch (Exception $e) {
       throw $e;
     }
   }

   public static function find_all_photos(){
     global $db;
     $sql = "SELECT * FROM photos";
     try {
       $result = $db->query($sql);
       $rows=$result->fetchall();
       return $rows;
     } catch (Exception $e) {
       throw $e;
     }
   }

   public  function save($value){
       $target_path = IMG_PATH.DS.$this->file_name;
       try {
         move_uploaded_file($value, $target_path);
         return $this->_add_photo();
       } catch (Exception $e) {
         throw $e;
       }
   }
 }
?>
