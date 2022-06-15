    <footer>
        <div class="credit">
            <span>Created with <i class="fa-solid fa-heart"></i> by Sofyan</span>
        </div>
    </footer>
    <script>
    if (navigator.userAgent.indexOf('gonative') > -1) {
        $('header').hide();
        $('footer').hide();
        $('.content-wrapper').css("margin", 0);
    }
    </script>
    <script>
        $(document).ready(function() {
            $(function($) {
                let url = window.location.href;
                $('#sideMenu li a').each(function() {
                    if (this.href === url) {
                        $(this).addClass('current');
                    }
                })
            })
        });
        $(document).ready(function() {
            $(function($) {
                let url = window.location.href;
                $('#topMenu li a').each(function() {
                    if (this.href === url) {
                        $(this).addClass('current');
                    }
                })
            })
        });
    </script>
    <script>
        $(document).ready(function(){
            $("#logoutUser").click(function(){
                swal({
                    title: 'Kamu Yakin?',
                    text: "Kamu bisa login kembali.",
                    type: 'warning',
                    showCancelButton: true,
                    confirmButtonColor: '#6e6dfb',
                    cancelButtonColor: '#ff4c4c',
                    confirmButtonText: 'Ya',
                    cancelButtonText: 'Tidak',
                    animation: true,
                }).then((result) => {
                    if (result.value) {
                        window.location.href = '<?php echo $url; ?>/action/logout.php';
                    }
                });
            });
        });
    </script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/js/all.min.js"></script>
    <script src="//cdn.datatables.net/1.11.4/js/jquery.dataTables.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/chart.js@3.7.0/dist/chart.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/limonte-sweetalert2/7.33.1/sweetalert2.min.js"></script>
    <script src="<?php echo $url; ?>/assets/js/main.js"></script>
</body>
</html>