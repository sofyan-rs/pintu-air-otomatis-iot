<?php
$pageTitle = "Dashboard - Pintu Air Otomatis";
include "components/header.php";
?>
    <main>
        <div class="content-wrapper">
            <div class="content-info">
                <span><b>Auto 1 :</b> Mode otomatis berdasarkan ketinggian air</span>
                <span><b>Auto 2 :</b> Mode otomatis berdasarkan kelembaban tanah</span>
            </div>
            <div class="content-flex-3">
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Kontrol Pintu Air</h3>
                        <div class="title">Saluran 1</div>
                        <div class="saluran" id="saluran-1">
                            <div class="flex">
                                <div class="wrap block">
                                    <span id="pintu-air-1" class="indikator">-</span>
                                </div>
                            </div>
                            <div class="flex">
                                <div class="wrap">
                                    <button id="pintu-1-manual">Manual</button>
                                    <button id="pintu-1-btn">-</button>
                                </div>
                            </div>
                            <div class="flex">
                                <div class="wrap">
                                    <button id="pintu-1-auto-1">Auto 1</button>
                                    <button id="pintu-1-auto-2">Auto 2</button>
                                </div>
                            </div>
                        </div>
                        <div class="batas hide" id="batas-saluran-1">
                            <div class="slider hide" id="slider-level-air-1">
                                <label for="batas-level-air-1">Batas Level Air <span class="value" id="value-batas-level-air-1"></span></label>
                                <input type="range" min="0" max="20" value="10" class="slider-batas" id="batas-level-air-1">
                            </div>
                            <div class="slider hide" id="slider-kelembaban-tanah-1">
                                <label for="batas-kelembaban-tanah-1">Batas Kelembaban Tanah <span class="value" id="value-batas-kelembaban-tanah-1"></span></label>
                                <input type="range" min="1" max="10" value="8" class="slider-batas" id="batas-kelembaban-tanah-1">
                            </div>
                        </div>
                        <div class="title">Saluran 2</div>
                        <div class="saluran" id="saluran-2">
                            <div class="flex">
                                <div class="wrap block">
                                    <span id="pintu-air-2" class="indikator">-</span>
                                </div>
                            </div>
                            <div class="flex">
                                <div class="wrap">
                                    <button id="pintu-2-manual">Manual</button>
                                    <button id="pintu-2-btn">-</button>
                                </div>
                            </div>
                            <div class="flex">
                                <div class="wrap">
                                    <button id="pintu-2-auto-1">Auto 1</button>
                                    <button id="pintu-2-auto-2">Auto 2</button>
                                </div>
                            </div>
                        </div>
                        <div class="batas hide" id="batas-saluran-2">
                            <div class="slider hide" id="slider-level-air-2">
                                <label for="batas-level-air-2">Batas Level Air <span class="value" id="value-batas-level-air-2"></span></label>
                                <input type="range" min="0" max="20" value="10" class="slider-batas" id="batas-level-air-2">
                            </div>
                            <div class="slider hide" id="slider-kelembaban-tanah-2">
                                <label for="batas-kelembaban-tanah-2">Batas Kelembaban Tanah <span class="value" id="value-batas-kelembaban-tanah-2"></span></label>
                                <input type="range" min="1" max="10" value="8" class="slider-batas" id="batas-kelembaban-tanah-2">
                            </div>
                        </div>
                    </div>
                </div>
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran Air 1 <span class="battery"><i class="fa-solid fa-battery-full fa-fw"></i> <span id="battery-1"></span>%</span></h3>
                        <div class="title">Ketinggian Air</div>
                        <div class="monitoring">
                            <div class="flex">
                                <span id="level-air-1">0</span><span> cm</span>
                            </div>
                            <div class="flex">
                                <i class="fa-solid fa-water fa-fw"></i>
                            </div>
                        </div>
                        <div class="title">Kelembaban Tanah</div>
                        <div class="monitoring">
                            <div class="flex">
                                <span id="kelembaban-tanah-1">0</span><span></span>
                            </div>
                            <div class="flex">
                                <i class="fa-solid fa-percent fa-fw"></i>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran Air 2 <span class="battery"><i class="fa-solid fa-battery-full fa-fw"></i> <span id="battery-2"></span>%</span></h3>
                        <div class="title">Ketinggian Air</div>
                        <div class="monitoring">
                            <div class="flex">
                                <span id="level-air-2">0</span><span> cm</span>
                            </div>
                            <div class="flex">
                                <i class="fa-solid fa-water fa-fw"></i>
                            </div>
                        </div>
                        <div class="title">Kelembaban Tanah</div>
                        <div class="monitoring">
                            <div class="flex">
                                <span id="kelembaban-tanah-2">0</span><span></span>
                            </div>
                            <div class="flex">
                                <i class="fa-solid fa-percent fa-fw"></i>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="content-flex-2">
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran 1 - Grafik Ketinggian Air <label class="switch"><input type="checkbox" id="save-database-1" onclick="saveDatabase1()"><span class="slider-check"></span></label></h3>
                        <div class="grafik" id="grafikSaluran1_levelAir"></div>
                    </div>
                </div>
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran 2 - Grafik Ketinggian Air <label class="switch"><input type="checkbox" id="save-database-2" onclick="saveDatabase2()"><span class="slider-check"></span></label></h3>
                        <div class="grafik" id="grafikSaluran2_levelAir"></div>
                    </div>
                </div>
            </div>

            <div class="content-flex-2">
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran 1 - Grafik Kelembaban Tanah</h3>
                        <div class="grafik" id="grafikSaluran1_kelembabanTanah"></div>
                    </div>
                </div>
                <div class="content-flex-item">
                    <div class="content">
                        <h3>Saluran 2 - Grafik Kelembaban Tanah</h3>
                        <div class="grafik" id="grafikSaluran2_kelembabanTanah"></div>
                    </div>
                </div>
            </div>


            <script>
                // Get Data from Database and Refresh after 1000ms
                var refreshId = setInterval(function()
                {
                    // Saluran 1
                    $('#grafikSaluran1_levelAir').load("<?php echo $url; ?>/components/saluran_1/grafik_level_air.php");
                    $('#grafikSaluran1_kelembabanTanah').load("<?php echo $url; ?>/components/saluran_1/grafik_kelembaban_tanah.php");

                    // Saluran 2
                    $('#grafikSaluran2_levelAir').load("<?php echo $url; ?>/components/saluran_2/grafik_level_air.php");
                    $('#grafikSaluran2_kelembabanTanah').load("<?php echo $url; ?>/components/saluran_2/grafik_kelembaban_tanah.php");

                }, 1000);
            </script>
        </div>
    </main>
    <script type="module" src="<?php echo $url; ?>/assets/js/firebase.js"></script>
<?php
include "components/footer.php";
?>