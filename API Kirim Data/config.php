<?php 
// Konfigurasi Server Website
$name = 'Pintu Air Otomatis IoT';
$url = 'http://192.168.1.2/pintu-air';

// Koneksi Database
$host_db = "localhost";
$user_db = "pintu_air";
$pass_db = "K01d3z1gn.n3t";
$nama_db = "pintu_air";
$mysqli = new mysqli($host_db, $user_db, $pass_db, $nama_db);
?>