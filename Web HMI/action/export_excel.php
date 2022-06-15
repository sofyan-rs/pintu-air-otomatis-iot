<!DOCTYPE html>
<html>
<head>
<title>Export Data Hasil Pemilihan E-Vote HME</title>
</head>
<body>
<style type="text/css">
body{
	font-family: sans-serif;
}
table{
	margin: 20px auto;
	border-collapse: collapse;
}
table th,
table td{
	border: 1px solid #3c3c3c;
	padding: 3px 8px;
}
a{
	background: blue;
	color: #fff;
	padding: 8px 10px;
	text-decoration: none;
	border-radius: 2px;
}
</style>
<?php
$saluran = $_GET['saluran'];
$date = date("d-m-Y");
header("Content-type: application/vnd-ms-excel");
header("Content-Disposition: attachment; filename=Data Saluran ".$saluran."_".$date.".xls");
?>
<center><h2>Data Hasil Monitoring Pintu Air - Saluran <?php echo $saluran; ?></h2></center>
<?php 
	include '../config.php';
	if ($saluran == 1) {
	    $query = $mysqli->query("SELECT * FROM saluran_1 ORDER BY id DESC");   
	} else if ($saluran == 2) {
	    $query = $mysqli->query("SELECT * FROM saluran_2 ORDER BY id DESC");
	}
    $check = $query->num_rows;
    $nomor = 0;
    if ($check > 0) {
?>
<table border="1">
	<tr>
		<th>No.</th>
		<th>Tanggal & Waktu</th>
		<th>Ketinggian Air</th>
		<th>Kelembaban Tanah</th>
		<th>Kondisi Pintu Air</th>
	</tr>
    <?php
        while($data = $query->fetch_array(MYSQLI_ASSOC)) {
        $nomor++;
    ?>
	<tr>
		<td><?php echo $nomor; ?></td>
        <td><?php echo date('d-m-Y H:i:s', strtotime($data['datetime'])); ?></td>
        <td><?php echo $data['level_air']; ?></td>
        <td><?php echo $data['kelembaban_tanah']; ?></td>
        <td><?php echo $data['kondisi_pintu_air']; ?></td>
	</tr>
	<?php }	?>
</table>
<?php } else {
    echo "<b>Belum ada data</b>";
} ?>
</body>
</html>