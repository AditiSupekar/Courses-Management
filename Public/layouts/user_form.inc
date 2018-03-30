<form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF'])?>" method="post" id="user_form">

  <input type="hidden" name="rand" value="<?php echo $rand ?>">
  <input type="text" name="first_name" placeholder="First Name">
  <input type="text" name="last_name" placeholder="Last Name">
  <br>
  <input type="text" name="username" placeholder="Username">
  <input type="password" name="password">
  <br>

  <input type="radio" name="type" value="user" checked> User
  <input type="radio" name="type" value="admin"> Admin

  <select name="query_type" form="user_form">
    <option value="add">Add User</option>
    <option value="find" selected>Find User</option>
    <option value="delete">Delete User</option>
  </select>
  <br>
  <button type="submit" name="user_management">Submit</button>
</form>
