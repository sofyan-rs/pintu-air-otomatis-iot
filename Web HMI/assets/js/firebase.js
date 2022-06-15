// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.6/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/9.6.6/firebase-analytics.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
    apiKey: "AIzaSyCvfN0mZdodt3ewGdN1ERucsktNo-FlsmM",
    authDomain: "pintu-air-otomatis-iot-29db0.firebaseapp.com",
    databaseURL: "https://pintu-air-otomatis-iot-29db0-default-rtdb.firebaseio.com",
    projectId: "pintu-air-otomatis-iot-29db0",
    storageBucket: "pintu-air-otomatis-iot-29db0.appspot.com",
    messagingSenderId: "631666352530",
    appId: "1:631666352530:web:a8399da2b928316937a14b",
    measurementId: "G-YD20J5RX1L"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
import {getDatabase, ref, get, child, update, remove} from "https://www.gstatic.com/firebasejs/9.6.6/firebase-database.js";
const db = getDatabase();
const dbRef = ref(getDatabase());

// Variable for Mode Water Sluice 1
var pintu1Btn = document.getElementById("pintu-1-btn");
var manualpintu1Btn = document.getElementById("pintu-1-manual");
var auto1pintu1Btn = document.getElementById("pintu-1-auto-1");
var auto2pintu1Btn = document.getElementById("pintu-1-auto-2");

// Variable for Mode Water Sluice 2
var pintu2Btn = document.getElementById("pintu-2-btn");
var manualpintu2Btn = document.getElementById("pintu-2-manual");
var auto1pintu2Btn = document.getElementById("pintu-2-auto-1");
var auto2pintu2Btn = document.getElementById("pintu-2-auto-2");

// Variable for Water Sluice
var pintuAir1 = document.getElementById("pintu-air-1");
var pintuAir2 = document.getElementById("pintu-air-2");
var batas_saluran_1 = document.getElementById("batas-saluran-1");
var batas_saluran_2 = document.getElementById("batas-saluran-2");

// Variable for Slider Batas Level Air 1
var slider_level_air_1 = document.getElementById("slider-level-air-1");
var batas_level_air_1 = document.getElementById("batas-level-air-1");
var value_batas_level_air_1 = document.getElementById("value-batas-level-air-1");

// Variable for Slider Batas Kelembaban Tanah 1
var slider_kelembaban_tanah_1 = document.getElementById("slider-kelembaban-tanah-1");
var batas_kelembaban_tanah_1 = document.getElementById("batas-kelembaban-tanah-1");
var value_batas_kelembaban_tanah_1 = document.getElementById("value-batas-kelembaban-tanah-1");

// Variable for Slider Batas Level Air 2
var slider_level_air_2 = document.getElementById("slider-level-air-2");
var batas_level_air_2 = document.getElementById("batas-level-air-2");
var value_batas_level_air_2 = document.getElementById("value-batas-level-air-2");

// Variable for Slider Batas Kelembaban Tanah 2
var slider_kelembaban_tanah_2 = document.getElementById("slider-kelembaban-tanah-2");
var batas_kelembaban_tanah_2 = document.getElementById("batas-kelembaban-tanah-2");
var value_batas_kelembaban_tanah_2 = document.getElementById("value-batas-kelembaban-tanah-2");

// Variable for Sensor
var levelAir1 = document.getElementById("level-air-1");
var kelembabanTanah1 = document.getElementById("kelembaban-tanah-1");
var levelAir2 = document.getElementById("level-air-2");
var kelembabanTanah2 = document.getElementById("kelembaban-tanah-2");

// Variable for Battery
var battery1 = document.getElementById("battery-1");
var battery2 = document.getElementById("battery-2");

// Variable for Save Database
var save_database_1 = document.getElementById("save-database-1");
var save_database_2 = document.getElementById("save-database-2");

// Get Data from Firebase and Refresh after 100ms
var refreshId = setInterval(function()
{
    // Get Data Water Level Sensor 1
    get(child(dbRef, '/saluran_1/monitoring/sensor_level_air')).then((snapshot) => {
        if (snapshot.exists()) {
            levelAir1.innerHTML = (snapshot.val()).toFixed(2);
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Soil Moisture Sensor 1
    get(child(dbRef, '/saluran_1/monitoring/sensor_kelembaban_tanah')).then((snapshot) => {
        if (snapshot.exists()) {
            kelembabanTanah1.innerHTML = (snapshot.val());
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Water Level Sensor 2
    get(child(dbRef, '/saluran_2/monitoring/sensor_level_air')).then((snapshot) => {
        if (snapshot.exists()) {
            levelAir2.innerHTML = (snapshot.val()).toFixed(2);
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Soil Moisture Sensor 1
    get(child(dbRef, '/saluran_2/monitoring/sensor_kelembaban_tanah')).then((snapshot) => {
        if (snapshot.exists()) {
            kelembabanTanah2.innerHTML = (snapshot.val());
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Battery 1
    get(child(dbRef, '/saluran_1/monitoring/baterai_status')).then((snapshot) => {
        if (snapshot.exists()) {
            battery1.innerHTML = (snapshot.val());
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Battery 2
    get(child(dbRef, '/saluran_2/monitoring/baterai_status')).then((snapshot) => {
        if (snapshot.exists()) {
            battery2.innerHTML = (snapshot.val());
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });
    
}, 10);

// Get Data from Firebase and Refresh after 1000ms
var refreshId = setInterval(function()
{
    // Get Data Water Sluice 1
    get(child(dbRef, '/saluran_1/monitoring/kondisi_pintu_air')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 0) {
                pintuAir1.classList.remove("off");
                pintuAir1.classList.add("on");
                pintuAir1.innerHTML = "Terbuka";
                pintu1Btn.innerHTML = "Tutup";
            } else {
                pintuAir1.classList.remove("on");
                pintuAir1.classList.add("off");
                pintuAir1.innerHTML = "Tertutup";
                pintu1Btn.innerHTML = "Buka";
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Mode Water Sluice 1
    get(child(dbRef, '/saluran_1/kontrol/mode_pintu_air')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 1) {
                auto1pintu1Btn.classList.add("active");
                auto2pintu1Btn.classList.remove("active");
                manualpintu1Btn.classList.remove("active");
                pintu1Btn.disabled = true;
                batas_saluran_1.classList.remove("hide");
                slider_level_air_1.classList.remove("hide");
                slider_kelembaban_tanah_1.classList.add("hide");
            } else if (snapshot.val() == 2) {
                auto1pintu1Btn.classList.remove("active");
                auto2pintu1Btn.classList.add("active");
                manualpintu1Btn.classList.remove("active");
                pintu1Btn.disabled = true;
                batas_saluran_1.classList.remove("hide");
                slider_level_air_1.classList.add("hide");
                slider_kelembaban_tanah_1.classList.remove("hide");
            } else {
                auto1pintu1Btn.classList.remove("active");
                auto2pintu1Btn.classList.remove("active");
                manualpintu1Btn.classList.add("active");
                pintu1Btn.disabled = false;
                batas_saluran_1.classList.add("hide");
                slider_level_air_1.classList.add("hide");
                slider_kelembaban_tanah_1.classList.add("hide");
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Water Sluice 2
    get(child(dbRef, '/saluran_2/monitoring/kondisi_pintu_air')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 0) {
                pintuAir2.classList.remove("off");
                pintuAir2.classList.add("on");
                pintuAir2.innerHTML = "Terbuka";
                pintu2Btn.innerHTML = "Tutup";
            } else {
                pintuAir2.classList.remove("on");
                pintuAir2.classList.add("off");
                pintuAir2.innerHTML = "Tertutup";
                pintu2Btn.innerHTML = "Buka";
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Data Mode Water Sluice 2
    get(child(dbRef, '/saluran_2/kontrol/mode_pintu_air')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 1) {
                auto1pintu2Btn.classList.add("active");
                auto2pintu2Btn.classList.remove("active");
                manualpintu2Btn.classList.remove("active");
                pintu2Btn.disabled = true;
                batas_saluran_2.classList.remove("hide");
                slider_level_air_2.classList.remove("hide");
                slider_kelembaban_tanah_2.classList.add("hide");
            } else if (snapshot.val() == 2) {
                auto1pintu2Btn.classList.remove("active");
                auto2pintu2Btn.classList.add("active");
                manualpintu2Btn.classList.remove("active");
                pintu2Btn.disabled = true;
                batas_saluran_2.classList.remove("hide");
                slider_level_air_2.classList.add("hide");
                slider_kelembaban_tanah_2.classList.remove("hide");
            } else {
                auto1pintu2Btn.classList.remove("active");
                auto2pintu2Btn.classList.remove("active");
                manualpintu2Btn.classList.add("active");
                pintu2Btn.disabled = false;
                batas_saluran_2.classList.add("hide");
                slider_level_air_2.classList.add("hide");
                slider_kelembaban_tanah_2.classList.add("hide");
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });
    
    // Get Data Batas Ketinggian Air 1
    get(child(dbRef, '/saluran_1/kontrol/batas_level_air')).then((snapshot) => {
        if (snapshot.exists()) {
            batas_level_air_1.value = snapshot.val();
            value_batas_level_air_1.innerHTML = snapshot.val();
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });
    
    // Get Data Batas Ketinggian Air 2
    get(child(dbRef, '/saluran_2/kontrol/batas_level_air')).then((snapshot) => {
        if (snapshot.exists()) {
            batas_level_air_2.value = snapshot.val();
            value_batas_level_air_2.innerHTML = snapshot.val();
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });
    
    // Get Data Batas Kelembaban Tanah 1
    get(child(dbRef, '/saluran_1/kontrol/batas_kelembaban_tanah')).then((snapshot) => {
        if (snapshot.exists()) {
            batas_kelembaban_tanah_1.value = snapshot.val();
            value_batas_kelembaban_tanah_1.innerHTML = snapshot.val();
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });
    
    // Get Data Batas Kelembaban Tanah 2
    get(child(dbRef, '/saluran_2/kontrol/batas_kelembaban_tanah')).then((snapshot) => {
        if (snapshot.exists()) {
            batas_kelembaban_tanah_2.value = snapshot.val();
            value_batas_kelembaban_tanah_2.innerHTML = snapshot.val();
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Save Database 1
    get(child(dbRef, '/saluran_1/kontrol/save_database')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 0) {
                save_database_1.checked = false;
            } else {
                save_database_1.checked = true;
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

    // Get Save Database 2
    get(child(dbRef, '/saluran_2/kontrol/save_database')).then((snapshot) => {
        if (snapshot.exists()) {
            if (snapshot.val() == 0) {
                save_database_2.checked = false;
            } else {
                save_database_2.checked = true;
            }
        } else {
            console.log("No data available");
        }
    }).catch((error) => {
        console.error(error);
    });

}, 1000);

// Function for Mode Water Sluice 1
function pintu1Mode1() {
    update(ref(db, '/saluran_1/kontrol'), {
        mode_pintu_air: 0,
    }).then(() => {
        console.log("Mode Pintu Air 1 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}
function pintu1Mode2() {
    update(ref(db, '/saluran_1/kontrol'), {
        mode_pintu_air: 1,
    }).then(() => {
        console.log("Mode Pintu Air 1 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}
function pintu1Mode3() {
    update(ref(db, '/saluran_1/kontrol'), {
        mode_pintu_air: 2,
    }).then(() => {
        console.log("Mode Pintu Air 1 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Function for Open & Close Water Sluice 1 Manual Mode
function pintu1Bukatutup() {
    var pintuAir1 = pintu1Btn.innerHTML;
    if (pintuAir1 == "Tutup") {
        update(ref(db, '/saluran_1/kontrol'), {
            buka_pintu_air: 0,
        }).then(() => {
            console.log("Buka Pintu Air 1");
        }).catch((error) => {
            console.log(error);
        });
    } else {
        update(ref(db, '/saluran_1/kontrol'), {
            buka_pintu_air: 1,
        }).then(() => {
            console.log("Tutup Pintu Air 1");
        }).catch((error) => {
            console.log(error);
        });
    }
}

// Listener for Button Mode Water Sluice 1
manualpintu1Btn.addEventListener('click', pintu1Mode1);
auto1pintu1Btn.addEventListener('click', pintu1Mode2);
auto2pintu1Btn.addEventListener('click', pintu1Mode3);
pintu1Btn.addEventListener('click', pintu1Bukatutup);

// Function for Mode Water Sluice 2
function pintu2Mode1() {
    update(ref(db, '/saluran_2/kontrol'), {
        mode_pintu_air: 0,
    }).then(() => {
        console.log("Mode Pintu Air 2 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}
function pintu2Mode2() {
    update(ref(db, '/saluran_2/kontrol'), {
        mode_pintu_air: 1,
    }).then(() => {
        console.log("Mode Pintu Air 2 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}
function pintu2Mode3() {
    update(ref(db, '/saluran_2/kontrol'), {
        mode_pintu_air: 2,
    }).then(() => {
        console.log("Mode Pintu Air 2 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Function for Open & Close Water Sluice 2 Manual Mode
function pintu2Bukatutup() {
    var pintuAir2 = pintu2Btn.innerHTML;
    if (pintuAir2 == "Tutup") {
        update(ref(db, '/saluran_2/kontrol'), {
            buka_pintu_air: 0,
        }).then(() => {
            console.log("Buka Pintu Air 2");
        }).catch((error) => {
            console.log(error);
        });
    } else {
        update(ref(db, '/saluran_2/kontrol'), {
            buka_pintu_air: 1,
        }).then(() => {
            console.log("Buka Pintu Air 2");
        }).catch((error) => {
            console.log(error);
        });
    }
}

// Listener for Button Mode Water Sluice 1
manualpintu2Btn.addEventListener('click', pintu2Mode1);
auto1pintu2Btn.addEventListener('click', pintu2Mode2);
auto2pintu2Btn.addEventListener('click', pintu2Mode3);
pintu2Btn.addEventListener('click', pintu2Bukatutup);

// Slider Batas Level Air 1
value_batas_level_air_1.innerHTML = batas_level_air_1.value;
batas_level_air_1.oninput = function() {
    value_batas_level_air_1.innerHTML = this.value;
    update(ref(db, '/saluran_1/kontrol'), {
        batas_level_air: parseInt(this.value),
    }).then(() => {
        console.log("Batas Level Air Saluran 1 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Slider Batas Kelembaban Tanah 1
value_batas_kelembaban_tanah_1.innerHTML = batas_kelembaban_tanah_1.value;
batas_kelembaban_tanah_1.oninput = function() {
    value_batas_kelembaban_tanah_1.innerHTML = this.value;
    update(ref(db, '/saluran_1/kontrol'), {
        batas_kelembaban_tanah: parseInt(this.value),
    }).then(() => {
        console.log("Batas Kelembaban Tanah Saluran 1 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Slider Batas Level Air 2
value_batas_level_air_2.innerHTML = batas_level_air_2.value;
batas_level_air_2.oninput = function() {
    value_batas_level_air_2.innerHTML = this.value;
    update(ref(db, '/saluran_2/kontrol'), {
        batas_level_air: parseInt(this.value),
    }).then(() => {
        console.log("Batas Level Air Saluran 2 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Slider Batas Kelembaban Tanah 2
value_batas_kelembaban_tanah_2.innerHTML = batas_kelembaban_tanah_2.value;
batas_kelembaban_tanah_2.oninput = function() {
    value_batas_kelembaban_tanah_2.innerHTML = this.value;
    update(ref(db, '/saluran_2/kontrol'), {
        batas_kelembaban_tanah: parseInt(this.value),
    }).then(() => {
        console.log("Batas Kelembaban Tanah Saluran 2 Berubah");
    }).catch((error) => {
        console.log(error);
    });
}

// Save Database Saluran 1
function saveDatabase1() {
    if (save_database_1.checked == true){
        update(ref(db, '/saluran_1/kontrol'), {
            save_database: 1,
        }).then(() => {
            console.log("Data akan disimpan");
        }).catch((error) => {
            console.log(error);
        });
    } else {
        update(ref(db, '/saluran_1/kontrol'), {
            save_database: 0,
        }).then(() => {
            console.log("Data tidak disimpan");
        }).catch((error) => {
            console.log(error);
        });
    }
}
save_database_1.addEventListener('click', saveDatabase1);

// Save Database Saluran 2
function saveDatabase2() {
    if (save_database_2.checked == true){
        update(ref(db, '/saluran_2/kontrol'), {
            save_database: 1,
        }).then(() => {
            console.log("Data akan disimpan");
        }).catch((error) => {
            console.log(error);
        });
    } else {
        update(ref(db, '/saluran_2/kontrol'), {
            save_database: 0,
        }).then(() => {
            console.log("Data tidak disimpan");
        }).catch((error) => {
            console.log(error);
        });
    }
}
save_database_2.addEventListener('click', saveDatabase2);