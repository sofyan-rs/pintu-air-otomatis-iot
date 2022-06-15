<?php
include "../../config.php";

// Membaca id tertinggi pada database
$sql_id = $mysqli->query("SELECT MAX(id) FROM saluran_2");
$data_id = $sql_id->fetch_array(MYSQLI_ASSOC);

// Ambil id awal dan akhir
$last_id = $data_id['MAX(id)'];
$first_id = $last_id - 5;

// Mengambil data dari database dan difilter untuk 6 data terakhir
$datetime = $mysqli->query("SELECT datetime FROM saluran_2 WHERE id >= '$first_id' AND id <= '$last_id' ORDER BY id ASC");
$level_air = $mysqli->query("SELECT level_air FROM saluran_2 WHERE id >= '$first_id' AND id <= '$last_id' ORDER BY id ASC");
?>

<canvas id="chartLevelAir2"></canvas>
<script>
    var canvas = document.getElementById("chartLevelAir2").getContext('2d');
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
                label: "Level Air",
                data: [
                    <?php 
                        while ($data_level_air = $level_air->fetch_array(MYSQLI_ASSOC)) { 
                            echo ''.$data_level_air['level_air'].', ';
                        }
                    ?>
                ],
                backgroundColor: 'rgba(80, 157, 189, .2)',
                borderColor: 'rgb(80, 157, 189)',
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
                max: 20,
                min: 0,
                ticks: {
                    stepSize: 0.5
                }
            }
        }
    };

    // Cetak grafik ke dalam canvas
    var chartLevelAir2 = new Chart(canvas, {
        type: 'line',
        data: data,
        options: option
    });
</script>