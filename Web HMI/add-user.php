<?php
$pageTitle = "Add User - Pintu Air Otomatis";
include "components/header.php";
if($_SESSION['role'] != "admin"){
    header("Location: $url/login.php");
}
?>
    <main>
        <div class="content-wrapper">
            <div class="content-block">
                <h3>Add User</h3>
                <?php
                if (isset($_GET['pesan'])) {
                    if ($_GET['pesan'] == "error") {
                        echo '<div class="alert" style="margin-bottom:20px">Gagal menambahkan user.</div>';
                    }
                }
                ?>
                <form class="form-block" action="<?php echo $url; ?>/action/add_user.php" method="post">
                    <label for="username">Username :</label>
                    <input class="form-control" type="text" name="username" id="username" placeholder="Username" required>
                    <label for="email">Email :</label>
                    <input class="form-control" type="email" name="email" id="email" placeholder="Email" required>
                    <label for="password">Password :</label>
                    <input class="form-control" type="password" name="password" id="password" placeholder="Password" required>
                    <label for="role">Role :</label>
                    <select class="form-control" name="role" id="role">
                        <option value="admin">admin</option>
                        <option value="operator">operator</option>
                    </select>
                    <button class="btn-submit" type="submit">Add User</button>
                </form>
            </div>
        </div>
    </main>
<?php
include "components/footer.php";
?>