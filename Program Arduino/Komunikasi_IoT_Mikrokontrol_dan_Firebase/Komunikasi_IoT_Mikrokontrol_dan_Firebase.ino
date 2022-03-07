/*
 * Program Komunikasi IoT antara Mikrokontroler dengan Firebase
 * Sofyan R. - 191311030 - POLBAN - 2022
 */

// Library yang diperlukan
#include <WiFi.h>
#include <FirebaseESP32.h>

// Definisi Autentikasi Wifi
#define WIFI_SSID "Kosan ibu Ai"
#define WIFI_PASSWORD "gataulupa"

// Definisi Autentikasi Firebase
#define FIREBASE_HOST "pintu-air-otomatis-iot-29db0-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "7wSo95lkOMWeM5R7ZKh34u8Xr8WRTsTnNNRS6zcb"

// Definisi Firebase Data Object
FirebaseData firebaseData;

// Deklarasi Variabel Path Firebase
String pathSaluran = "/saluran_1";
String pathPintuAir = "/pintu_air";

// Deklarasi Variabel Pembacaan Sensor Ultrasonik
int trigPin = 12; // Pin D12 ESP32                                                                                                                                                                                // Pin D2 ESP32
int echoPin = 14; // Pin D14 ESP32
long durasi;
float jarak;
float tinggiAir = 0;

// Deklarasi Variabel Pembacaan Sensor Kelembaban Tanah
int analogPin = 34; // Pin D34 ESP32
int analogInput;
float kelembabanTanah;

// Deklarasi Pin Pintu Air
int pinPintuAir = 4; // Pin D4 ESP32

// Deklarasi Variabel Pintu Air Firebase
int modePintuAir = 0;
int kondisiPintuAir = 0;

void setup() {
  // Setup
  Serial.begin(115200);
  initWifi();
  initFirebase();

  // Inisialisasi Input dan Output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(analogPin, INPUT);
  pinMode(pinPintuAir, OUTPUT);
}

void loop() {
  // Melakukan Autentikasi ke Jaringan WiFi kembali saat jaringan terputus
  if (WiFi.status() != WL_CONNECTED) {
    initWifi();
  }

  // Membaca Data Sensor Ultrasonik
  // Mentrigger gelombang
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Menghitung waktu pantulan gelombang
  durasi = pulseIn(echoPin, HIGH);
  // Menghitung jarak berdasarkan waktu pantul gelombang
  jarak = (durasi/2)/29;
  // Mengkalibrasi jarak untuk range ketinggian 0-20 cm
  tinggiAir = (jarak-40)*(-1);
  
  // Membaca Data Sensor Kelembaban Tanah
  // Membaca nilai input analog dari pin A0 sensor
  analogInput = analogRead(analogPin);
  // Mengkonversi nilai pembacaan sensor menjadi persen (4095 = kering & 1500 = basah)
  kelembabanTanah = map(analogInput, 4095, 1500, 0, 100);
  
  // Mencetak Hasil Pembacan Sensor pada Serial Monitor
  Serial.print("Level Air : ");
  Serial.print(tinggiAir);
  Serial.println(" cm");
  Serial.print("Kelembaban Tanah : ");
  Serial.print(kelembabanTanah);
  Serial.println(" %");
  
  // Mengecek koneksi Firebase
  if (Firebase.ready()) {
    // Mengirim Data Pembacaan Sensor ke Firebase
    Firebase.setFloat(firebaseData, pathSaluran + "/sensor_level_air", tinggiAir);
    Firebase.setFloat(firebaseData, pathSaluran + "/sensor_kelembaban_tanah", kelembabanTanah);

    // Mengambil Data Mode Pintu Air dari Firebase
    if (Firebase.getInt(firebaseData, pathPintuAir + "/mode_pintu_air_1")) {
      if (firebaseData.dataType() == "int") {
        modePintuAir = firebaseData.intData();
      }
    }
    Serial.print("Mode Pintu Air : ");
    Serial.println(modePintuAir);

    // Buka Tutup Pintu berdasarkan Mode Otomatis
    if (modePintuAir == 1) {
      // Otomatis berdasarkan level air
      if (tinggiAir <= 10) {
        Firebase.setInt(firebaseData, pathPintuAir + "/pintu_air_1", 1);
      } else {
        Firebase.setInt(firebaseData, pathPintuAir + "/pintu_air_1", 0);
      }
    } else if (modePintuAir == 2) {
      // Otomatis berdasarkan kelembaban tanah
      if (kelembabanTanah <= 30) {
        Firebase.setInt(firebaseData, pathPintuAir + "/pintu_air_1", 1);
      } else {
        Firebase.setInt(firebaseData, pathPintuAir + "/pintu_air_1", 0);
      }
    }

    // Mengambil Data Kondisi Pintu Air dari Firebase
    if (Firebase.getInt(firebaseData, pathPintuAir + "/pintu_air_1")) {
      if (firebaseData.dataType() == "int") {
        kondisiPintuAir = firebaseData.intData();
      }
    }

    // Membuka dan Menutup Pintu Air sesuai Data dari Firebase
    if (kondisiPintuAir == 0) {
      digitalWrite(pinPintuAir, LOW);
      Serial.print("Kondisi Pintu Air : ");
      Serial.println("Tertutup");
    } else {
      digitalWrite(pinPintuAir, HIGH);
      Serial.print("Kondisi Pintu Air : ");
      Serial.println("Terbuka");
    }
    
    Serial.println();
  } else {
    initFirebase();
  }
}

// Fungsi Inisialisasi WiFi
void initWifi() {
  // Melakukan Autentikasi ke Jaringan WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke jaringan Wifi...");
    delay(300);
  }
  Serial.println("Berhasil terkoneksi ke " + (String)WIFI_SSID);
  Serial.print("Dengan IP: ");
  Serial.println(WiFi.localIP());
}

// Fungsi Inisialisai Firebase
void initFirebase() {
  // Melakukan Authentication ke Firebase
  Serial.println("Menghubungkan ke Firebase...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Set database read timeout to 1 minute (max = 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  // Set database write size
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
