<?php
$pageTitle = "Edit User - Pintu Air Otomatis";
include "components/header.php";
if($_SESSION['role'] != "admin"){
    header("Location: $url/login.php");
}
?>
    <main>
        <div class="content-wrapper">
            <div class="content-block">
                <h3>Edit User</h3>
                <?php
                $id = $_GET['id'];
                $query = $mysqli->query("SELECT * FROM users WHERE id='$id'");
                $check = $query->num_rows;
                if ($check > 0) {
                while($data = $query->fetch_array(MYSQLI_ASSOC)) {
                ?>
                <form class="form-block" action="<?php echo $url; ?>/action/edit_user.php?id=<?php echo $data['id']; ?>" method="post">
                    <label for="username">Username :</label>
                    <input class="form-control" type="text" name="username" id="username" value="<?php echo $data['username']; ?>" placeholder="Username" required>
                    <label for="email">Email :</label>
                    <input class="form-control" type="email" name="email" id="email" value="<?php echo $data['email']; ?>" placeholder="Email" required>
                    <label for="password">Password :</label>
                    <input class="form-control" type="password" name="password" id="password" placeholder="Password">
                    <?php if ($data['id'] != $_SESSION['id']) { ?>
                    <label for="role">Role :</label>
                    <select class="form-control" name="role" id="role">
                        <option value="admin"<?php if ($data['role'] == 'admin') { echo ' selected'; } ?>>admin</option>
                        <option value="operator"<?php if ($data['role'] == 'operator') { echo ' selected'; } ?>>operator</option>
                    </select>
                    <?php } ?>
                    <button class="btn-submit" type="submit">Update</button>
                </form>
                <?php } } else {
                    echo 'Tidak ditemukan user dengan id ini.';
                } ?>
            </div>
        </div>
    </main>
<?php
include "components/footer.php";
?>