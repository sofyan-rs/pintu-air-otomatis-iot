<?php
include "../../config.php";

// Membaca id tertinggi pada database
$sql_id = $mysqli->query("SELECT MAX(id) FROM saluran_1");
$data_id = $sql_id->fetch_array(MYSQLI_ASSOC);

// Ambil id awal dan akhir
$last_id = $data_id['MAX(id)'];
$first_id = $last_id - 5;

// Mengambil data dari database dan difilter untuk 6 data terakhir
$datetime = $mysqli->query("SELECT datetime FROM saluran_1 WHERE id >= '$first_id' AND id <= '$last_id' ORDER BY id ASC");
$kelembaban_tanah = $mysqli->query("SELECT kelembaban_tanah FROM saluran_1 WHERE id >= '$first_id' AND id <= '$last_id' ORDER BY id ASC");
?>

<canvas id="chartKelembabanTanah1"></canvas>
<script>
    var canvas = document.getElementById("chartKelembabanTanah1").getContext('2d');
    var data = {
        labels: [
            <?php 
                while ($data_datetime = $datetime->fetch_array(MYSQLI_ASSOC)) {
                    $date = date('H:i:s', strtotime($data_datetime['datetime']));
                    echo '"'.$date.'", ';
                }
            ?>
        ],
        datasets: [
            {
                label: "Kelembaban Tanah",
                data: [
                    <?php 
                        while ($data_kelembaban_tanah = $kelembaban_tanah->fetch_array(MYSQLI_ASSOC)) { 
                            echo ''.$data_kelembaban_tanah['kelembaban_tanah'].', ';
                        }
                    ?>
                ],
                backgroundColor: 'rgba(143, 97, 54, .2)',
                borderColor: 'rgb(143, 97, 54)',
                fill: true,
                lineTension: 0.5,
                pointRadius: 5
            }
        ]
    };

    // Option untuk grafik
    var option = {
        showlines: true,
        responsive: true,
        animation: {
            duration: 0
        },
        scales: {
            y: {
                max: 10,
                min: 1,
                ticks: {
                    stepSize: 0.5
                }
            }
        }
    };

    // Cetak grafik ke dalam canvas
    var chartKelembabanTanah1 = new Chart(canvas, {
        type: 'line',
        data: data,
        options: option
    });
</script>