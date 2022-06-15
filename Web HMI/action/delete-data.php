<?php
include '../config.php';
session_start();

// Ambil data dari url GET
$saluran = $_GET['saluran'];

// Delete Data
if ($saluran == 1) {
    $delete_data = $mysqli->prepare("DELETE FROM saluran_1");
    if ($delete_data->execute()) {
        $_SESSION["sukses"] = 'Data Telah Berhasil Dihapus';
        header("Location: $url/saluran-1.php");
    } else {
        $_SESSION["error"] = 'Data Gagal Dihapus';
        header("Location: $url/saluran-1.php");
    }
} else if ($saluran == 2) {
    $delete_data = $mysqli->prepare("DELETE FROM saluran_2");
    if ($delete_data->execute()) {
        $_SESSION["sukses"] = 'Data Telah Berhasil Dihapus';
        header("Location: $url/saluran-2.php");
    } else {
        $_SESSION["error"] = 'Data Gagal Dihapus';
        header("Location: $url/saluran-2.php");
    }
}
?>