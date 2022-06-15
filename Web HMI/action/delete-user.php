<?php
include '../config.php';
session_start();

// Ambil data dari url GET
$id = $mysqli->real_escape_string($_GET['id']);

// Delete User
$delete_user = $mysqli->prepare("DELETE FROM users WHERE id='$id'");
if ($delete_user->execute()) {
    $_SESSION["sukses"] = 'User Telah Berhasil Dihapus';
    header("Location: $url/users.php");
} else {
    $_SESSION["error"] = 'User Gagal Dihapus';
    header("Location: $url/users.php");
}
?>