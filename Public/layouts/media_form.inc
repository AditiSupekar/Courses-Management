<form class="" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" method="post" enctype="multipart/form-data">
  <input type="hidden" name="rand" value="<?php echo $rand ?>">
  <input type="file" name="uploaded_file" required><br>
  <input type="text" name="photo_name" placeholder="Photo Name" required><br>
  <input type="text" name="photo_caption" placeholder="Photo Caption" required><br>
  <button type="submit" name="photo_upload">Upload Photo</button>
</form>
