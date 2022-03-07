/*
 * Program untuk mengkoneksikan ke Firebase
 * Sofyan R. - 191311030
 */

// Library yang diperlukan
#include <WiFi.h>
#include <FirebaseESP32.h>

// Definisi Autentikasi Wifi
#define WIFI_SSID "WiFi Sofyan"
#define WIFI_PASSWORD "15022001"

// Definisi Autentikasi Firebase
#define FIREBASE_HOST "pintu-air-otomatis-iot-29db0-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "7wSo95lkOMWeM5R7ZKh34u8Xr8WRTsTnNNRS6zcb"

// Definisi Firebase Data Object
FirebaseData firebaseData;

void setup() {
  // Setup
  Serial.begin(115200);
  initWifi();
  initFirebase();
}

void loop() {
  // Melakukan Autentikasi ke Jaringan WiFi kembali saat jaringan terputus
  if (WiFi.status() != WL_CONNECTED) {
    initWifi();
  }
  // Mengecek kondisi Firebase
  if (Firebase.ready()) {
    Serial.println("Berhasil terkoneksi ke Firebase");
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
