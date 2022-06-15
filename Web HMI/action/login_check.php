<?php
include '../config.php';

// Ambil hasil input email dan password
$email = $mysqli->real_escape_string($_POST['email']);
$password = $mysqli->real_escape_string($_POST['password']);

// Check User Login
$login = $mysqli->query("SELECT * from users WHERE email='$email'");
$check = $login->num_rows;
$data = $login->fetch_assoc();

if ($check > 0) {
    if (password_verify($password, $data['password'])) {
        session_start();
        $_SESSION['id'] = $data['id'];
        $_SESSION['email'] = $data['email'];
        $_SESSION['username'] = $data['username'];
        $_SESSION['role'] = $data['role'];
        $_SESSION['status'] = "login";
        header("location: $url");
    } else {
        header("Location: $url/login.php?pesan=wrong-password");
    }
} else {
    header("Location: $url/login.php?pesan=email-not-found");
}
?>