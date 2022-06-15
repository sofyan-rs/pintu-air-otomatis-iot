<!DOCTYPE html>
<html lang="en">
<?php 
include './config.php'; 
?>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Download APK - Pintu Air Otomatis</title>
    <link rel="icon" type="image/x-icon" href="<?php echo $url; ?>/assets/images/favicon.ico">
    <link rel="stylesheet" href="<?php echo $url; ?>/assets/css/styles.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
</head>
<body>
    <style>
        body{display:block}
        .download-apk{background:#fff;margin:50px;padding:20px;border-radius:5px;box-shadow:0 5px 5px rgb(0 0 0 / 5%);text-align:center;}
        .download-apk h1{margin-bottom:20px;padding-bottom:15px;border-bottom:dashed 5px #f1f1f1}
        .download-apk h1 span{display:block;font-size:20px;font-weight:400;margin-top:5px;}
        .download-apk a{background:#6e6dfb;color:#fff;padding:10px;border-radius:5px;display:inline-block;font-weight:600;opacity:.8}
        .download-apk a:hover{opacity:1}
        .download-apk img{max-width:100px;margin-bottom:20px;}
    </style>
    <section class="container">
        <div class="download-apk">
            <img src="<?php echo $url; ?>/assets/images/ICON.png" title="Pintu Air Otomatis"/>
            <h1>Download APK<span>Simulasi Pintu Air Otomatis berdasarkan Ketinggian Air dan Kelembaban Tanah berbasis IoT</span></h1>
            <a href="<?php echo $url; ?>/download-apk/Pintu_Air_Otomatis_V1.0_Beta.apk">Download</a>
        </div>
    </section>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/js/all.min.js"></script>
    <script src="<?php echo $url; ?>/assets/js/jquery.min.js"></script>
</body>
</html>