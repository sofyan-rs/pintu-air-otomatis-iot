<?php
$pageTitle = "Users - Pintu Air Otomatis";
include "components/header.php";
if($_SESSION['role'] != "admin"){
    header("Location: $url/login.php");
}
?>
    <main>
        <div class="content-wrapper">
            <div class="content-block">
                <h3>Users <a class="btn add" href="<?php echo $url?>/add-user.php">Add User</a></h3>
                <table id="listUser" class="data-table display nowrap" style="width:100%">
                    <thead>
                        <tr>
                            <th>Username</th>
                            <th>Email</th>
                            <th>Role</th>
                            <th style="width: 90px">Action</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php 
                        $query = $mysqli->query("SELECT * FROM users");
                        $check = $query->num_rows;
                        if ($check > 0) {
                            while($data = $query->fetch_array(MYSQLI_ASSOC)) {
                        ?>
                        <tr>
                            <td><?php echo $data['username']; ?></td>
                            <td><?php echo $data['email']; ?></td>
                            <td><?php echo $data['role']; ?></td>
                            <td>
                                <a class="btn btn-edit" href="<?php echo $url; ?>/edit-user.php?id=<?php echo $data['id']; ?>">Edit</a>
                                <?php if($_SESSION['id'] != $data['id']){ ?>
                                <a class="btn btn-delete" id="deleteUser<?php echo $data['id']; ?>">Hapus</a>
                                <?php } ?>
                                <script>
                                    $(document).ready(function(){
                                        $("#deleteUser<?php echo $data['id']; ?>").click(function(){
                                            swal({
                                                title: 'Kamu Yakin?',
                                                text: "Kamu tidak bisa mengembalikan user yang dihapus!",
                                                type: 'warning',
                                                showCancelButton: true,
                                                confirmButtonColor: '#6e6dfb',
                                                cancelButtonColor: '#ff4c4c',
                                                confirmButtonText: 'Ya',
                                                cancelButtonText: 'Tidak',
                                                animation: true,
                                            }).then((result) => {
                                                if (result.value) {
                                                    window.location.href = '<?php echo $url; ?>/action/delete-user.php?id=<?php echo $data['id']; ?>';
                                                }
                                            });
                                        });
                                    });
                                </script>
                            </td>
                        </tr>
                        <?php        
                            }
                        } else {
                            echo "<tr><td>Belum ada data</td><td></td><td></td><td></td></tr>";
                        }
                        ?>
                    </tbody>
                </table>
            </div>
        </div>
    </main>
    <script>
        $(document).ready( function () {
            $('#listUser').DataTable({
                responsive: true
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