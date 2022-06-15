<?php
include '../config.php';

// Destroy Session untuk Logout
session_start();
session_destroy();
header("location:$url/login.php?pesan=logout");
?>