<?php
include "../config.php";
header('Content-type: application/json');

$response = array();

if (isset($_POST['api_key'])) {
    // Ambil data hasil kirim dari ESP32
    $apikey = $_POST['api_key'];
    if (isset($_POST['saluran'])) {
        $saluran = $_POST['saluran'];
        $level_air = $mysqli->real_escape_string($_POST['level_air']);
        $kelembaban_tanah = $mysqli->real_escape_string($_POST['kelembaban_tanah']);
        $kondisi = $mysqli->real_escape_string($_POST['kondisi_pintu_air']);
        if ($kondisi == 1) {
            $kondisi_pintu_air = "Tertutup";
        } else {
            $kondisi_pintu_air = "Terbuka";
        }
    }

    if ($apikey == "Ny3BqnerHgnYBgs3mv6ADd4pnqPeXNfG") {
        // Tambah Data
        if ($saluran == 1) {
            $add_data = $mysqli->prepare("INSERT INTO saluran_1 (level_air, kelembaban_tanah, kondisi_pintu_air) VALUES (?,?,?)");
            $add_data->bind_param("sss", $level_air, $kelembaban_tanah, $kondisi_pintu_air);
            if ($add_data->execute()) {
                $response["status"] = "Berhasil Tersimpan";
                $response["nomer_saluran"] = 1;
                $response["level_air"] = $level_air;
                $response["kelembaban_tanah"] = $kelembaban_tanah;
                $response["kondisi_pintu_air"] = $kondisi_pintu_air;
                echo json_encode($response);
            } else {
                $response["status"] = "Gagal Tersimpan";
                $response["keterangan"] = "Data Tidak Valid";
                echo json_encode($response);
            }
        } else if ($saluran == 2) {
            $add_data = $mysqli->prepare("INSERT INTO saluran_2 (level_air, kelembaban_tanah, kondisi_pintu_air) VALUES (?,?,?)");
            $add_data->bind_param("sss", $level_air, $kelembaban_tanah, $kondisi_pintu_air);
            if ($add_data->execute()) {
                $response["status"] = "Berhasil Tersimpan";
                $response["nomer_saluran"] = 2;
                $response["level_air"] = $level_air;
                $response["kelembaban_tanah"] = $kelembaban_tanah;
                $response["kondisi_pintu_air"] = $kondisi_pintu_air;
                echo json_encode($response);
            } else {
                $response["status"] = "Gagal Tersimpan";
                $response["keterangan"] = "Data Tidak Valid";
                echo json_encode($response);
            }
        } else {
            $response["status"] = "Gagal Tersimpan";
            $response["keterangan"] = "Saluran Tidak Tersedia";
            echo json_encode($response);
        }
    } else {
        $response["status"] = "Gagal Tersimpan";
        $response["keterangan"] = "Key Tidak Valid";
        echo json_encode($response);
    }
} else {
    $response["status"] = "Gagal Tersimpan";
    $response["keterangan"] = "Key Tidak Valid";
    echo json_encode($response);
}
?>