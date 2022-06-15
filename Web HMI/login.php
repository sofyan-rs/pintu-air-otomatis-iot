<!DOCTYPE html>
<html lang="en">
<?php 
include './config.php'; 
session_start();
if($_SESSION) {
    if($_SESSION['status'] == "login"){
        header("Location: $url");
    }
}
?>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login - Pintu Air Otomatis</title>
    <link rel="icon" type="image/x-icon" href="<?php echo $url; ?>/assets/images/favicon.ico">
    <link rel="stylesheet" href="<?php echo $url; ?>/assets/css/styles.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
</head>
<body>
    <style>body{display:block}</style>
    <section class="container">
        <div class="login-page"></div>
        <div class="login">
            <div class="logo">
                <i class="fa-solid fa-cloud fa-fw"></i>
                <div class="site-name" id="sitename">
                    <h1>Pintu Air</h1>
                    <h2>Otomatis IoT</h2>
                </div>
            </div>
            <?php
            if (isset($_GET['pesan'])) {
                if ($_GET['pesan'] == "wrong-password") {
                    echo '<div class="alert">Password yang dimasukkan salah.</div>';
                }
                if ($_GET['pesan'] == "email-not-found") {
                    echo '<div class="alert">Email tidak ditemukan.</div>';
                }
                if ($_GET['pesan'] == "logout") {
                    echo '<div class="alert">Anda berhasil logout.</div>';
                }
            } 
            ?>
            <h3>Login</h3>
            <form action="<?php echo $url; ?>/action/login_check.php" method="post">
                <input class="form-control" type="email" name="email" id="email" placeholder="Email" required>
                <input class="form-control" type="password" name="password" placeholder="Password" id="password" required>
                <button class="btn-submit" type="submit">Login</button>
            </form>
        </div>
    </section>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/js/all.min.js"></script>
    <script src="<?php echo $url; ?>/assets/js/jquery.min.js"></script>
</body>
</html>