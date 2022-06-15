<?php
include '../config.php';
session_start();

// Ambil data hasil input
$id = $mysqli->real_escape_string($_GET['id']);
$username = $mysqli->real_escape_string($_POST['username']);
$email = $mysqli->real_escape_string($_POST['email']);
if ($id == $_SESSION['id']) {
    $role = $_SESSION['role'];
} else {
    $role = $mysqli->real_escape_string($_POST['role']);
}

// Update Password
$password = $mysqli->real_escape_string($_POST['password']);
if ($password != "") {
    $password_hash = password_hash($password, PASSWORD_DEFAULT);
    $update_password = $mysqli->query("UPDATE users set password='$password_hash' WHERE id='$id'");
}

// Update User
$update_user = $mysqli->prepare("UPDATE users set email='$email', username='$username', role='$role' WHERE id='$id'");
if ($update_user->execute()) {
    $_SESSION["sukses"] = 'User Telah Berhasil Diedit';
    header("Location: $url/users.php");
} else {
    $_SESSION["error"] = 'User Gagal Diedit';
    header("Location: $url/users.php");
}
?>