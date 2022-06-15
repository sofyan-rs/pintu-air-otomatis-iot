<!DOCTYPE html>
<html lang="en">
<?php 
include './config.php'; 
session_start();
if($_SESSION['status'] != "login"){
    header("Location: $url/login.php");
}
?>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $pageTitle; ?></title>
    <link rel="icon" type="image/x-icon" href="<?php echo $url; ?>/assets/images/favicon.ico">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
    <link rel="stylesheet" href="//cdn.datatables.net/1.11.4/css/jquery.dataTables.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/limonte-sweetalert2/7.33.1/sweetalert2.min.css">
    <link rel="stylesheet" href="<?php echo $url; ?>/assets/css/styles.css">
    <script src="<?php echo $url; ?>/assets/js/jquery.min.js"></script>
</head>
<body>
    <header>
        <div class="side-nav">  
            <div class="navigation">
                <a class="side-button" id="showside" onclick="showSide()"><i class="fa-solid fa-angles-right fa-fw"></i></a>
                <div class="logo">
                    <i class="fa-solid fa-cloud fa-fw"></i>
                    <div class="site-name" id="sitename">
                        <h1>Pintu Air</h1>
                        <h2>Otomatis IoT</h2>
                    </div>
                </div>
                <div class="side-menu">
                    <ul id="sideMenu">
                        <li><a class="link" href="<?php echo $url; ?>/"><i class="fa-solid fa-house fa-fw"></i> <span>Home</span></a></li>
                        <li><a class="link" href="<?php echo $url; ?>/saluran-1.php"><i class="fa-solid fa-water fa-fw"></i> <span>Saluran 1</span></a></li>
                        <li><a class="link" href="<?php echo $url; ?>/saluran-2.php"><i class="fa-solid fa-water fa-fw"></i> <span>Saluran 2</span></a></li>
                        <?php if($_SESSION['role'] == "admin") { ?>
                        <li><a class="link" href="<?php echo $url; ?>/users.php"><i class="fa-solid fa-user-group fa-fw"></i> <span>Users</span></a></li>
                        <?php } ?>
                    </ul>
                </div>
            </div>
        </div>
        <div class="top-nav">
            <ul id="topMenu">
                <li><a href="<?php echo $url; ?>/profile.php">Profile</a></li>
                <li><a id="logoutUser">Logout</a></li>
            </ul>
        </div> 
    </header>