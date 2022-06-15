<?php
include '../config.php';
session_start();

// Ambil data hasil input
$username = $mysqli->real_escape_string($_POST['username']);
$email = $mysqli->real_escape_string($_POST['email']);
$password = $mysqli->real_escape_string($_POST['password']);
$password_hash = password_hash($password, PASSWORD_DEFAULT);
$role = $mysqli->real_escape_string($_POST['role']);

// Tambah User
$add_user = $mysqli->prepare("INSERT INTO users (email, username, password, role) VALUES (?,?,?,?)");
$add_user->bind_param("ssss", $email, $username, $password_hash, $role);
if ($add_user->execute()) {
    $_SESSION["sukses"] = 'User Telah Ditambahkan';
    header("Location: $url/users.php");
} else {
    header("Location: $url/add-user.php?pesan=error");
}
?>