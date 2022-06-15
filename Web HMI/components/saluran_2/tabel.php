<?php 
include "../../config.php";
$query = $mysqli->query("SELECT * FROM saluran_2 ORDER BY id DESC");
$check = $query->num_rows;
$nomor = 0;
if ($check > 0) { ?>
<table id="listData" class="data-table display nowrap" style="width:100%">
    <thead>
        <tr>
            <th style="width: 20px">No.</th>
            <th>Tanggal & Waktu</th>
            <th>Ketinggian Air</th>
            <th>Kelembaban Tanah</th>
            <th>Kondisi Pintu Air</th>
        </tr>
    </thead>
    <tbody>
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
        <?php } ?>
    </tbody>
</table>
<script>
    $(document).ready( function () {
        $('#listData').DataTable({
            responsive: true
        });
    });
</script>
<?php } else {
    echo "<b>Belum ada data</b>";
}
?>