<?php
  $sql  =  "CREATE TABLE photos (";
  $sql .=  "photo_id INT(10) PRIMARY KEY AUTO_INCREMENT, ";
  $sql .=  "photo_name VARCHAR(255) NOT NULL, ";
  $sql .=  "photo_caption VARCHAR(255) NOT NULL, ";
  $sql .=  "file_name VARCHAR(255) NOT NULL, ";
  $sql .=  "file_size INT(10) NOT NULL, ";
  $sql .=  "file_type VARCHAR(25) NOT NULL, ";
  $sql .=  "user_id INT(4) NOT NULL, ";
  $sql .=  "FOREIGN KEY (user_id) ";
  $sql .=  "REFERENCES users (id) ";
  $sql .=  "ON DELETE CASCADE";
  $sql .=  ")";

  echo $sql;
 ?>
