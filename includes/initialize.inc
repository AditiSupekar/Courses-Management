<?php
defined('DS') ? null : define('DS', DIRECTORY_SEPARATOR);

defined('P_ROOT') ? null :
define('P_ROOT', dirname(dirname(__FILE__)));
//__FILE__ is the current file, and dirname() gives its path
//I have replaced the following line by the one in line 5
//define('P_ROOT', DS.'Users'.DS.'aditisupekar'.DS.'Sites'.DS.'fall2017project');

defined('LIB_PATH') ? null :
define('LIB_PATH', P_ROOT.DS.'includes');

defined('IMG_PATH') ? null :
define('IMG_PATH', P_ROOT.DS.'public'.DS.'images');

defined('ADMIN_PATH') ? null :
define('ADMIN_PATH', P_ROOT.DS.'public'.DS.'admin'.DS.'index.php');

//session_start();//it turns the session on I will shift this line into clas.session.onc file
require_once LIB_PATH.DS.'pdo_connection.inc';
require_once LIB_PATH.DS.'functions.inc';
require_once LIB_PATH.DS.'class.session.inc';
require_once LIB_PATH.DS.'class.user.inc';
require_once LIB_PATH.DS.'class.photo.inc';
?>
