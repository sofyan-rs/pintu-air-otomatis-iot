<?php
$pageTitle = "Saluran 1 - Pintu Air Otomatis";
include "components/header.php";
?>
    <main>
        <div class="content-wrapper">
            <div class="content-block">
                <h3>Data Saluran 1 <a class="btn add btn-delete" id="deleteData">Hapus Semua Data</a><a class="btn add btn-export" href="https://pintu-air.kdevz.net/action/export_excel.php?saluran=1">Export Excel</a></h3>
                <div id="dataSaluran"></div>
            </div>
        </div>
    </main>
    <script>
        // Realtime Mode
        // var refreshId = setInterval(function()
        // {
        //     $('#dataSaluran').load("<?php echo $url; ?>/components/saluran_1/tabel.php");
        // }, 1000);
        $(document).ready(function(){
            $('#dataSaluran').load("<?php echo $url; ?>/components/saluran_1/tabel.php");
        });
    </script>
    <script>
        $(document).ready(function(){
            $("#deleteData").click(function(){
                swal({
                    title: 'Kamu Yakin?',
                    text: "Kamu tidak bisa mengembalikan data yang dihapus!",
                    type: 'warning',
                    showCancelButton: true,
                    confirmButtonColor: '#6e6dfb',
                    cancelButtonColor: '#ff4c4c',
                    confirmButtonText: 'Ya',
                    cancelButtonText: 'Tidak',
                    animation: true,
                }).then((result) => {
                    if (result.value) {
                        window.location.href = '<?php echo $url?>/action/delete-data.php?saluran=1';
                    }
                });
            });
        });
    </script>
    <?php if(@$_SESSION['sukses']){ ?>
    <script>
        $(document).ready(function() {
            swal({
                title: "Berhasil!",
                text: "<?php echo $_SESSION['sukses']; ?>", 
                type: "success",
                confirmButtonColor: '#6e6dfb',
            });
        });
    </script>
    <?php unset($_SESSION['sukses']); } ?>
    <?php if(@$_SESSION['error']){ ?>
    <script>
        $(document).ready(function() {
            swal({
                title: "Berhasil!",
                text: "<?php echo $_SESSION['error']; ?>", 
                type: "error",
                confirmButtonColor: '#6e6dfb',
            });
        });
    </script>
    <?php unset($_SESSION['error']); } ?>
<?php
include "components/footer.php";
?>