/*
 * Program untuk mengkoneksikan ke jaringan Wifi
 * Sofyan R. - 191311030
 */

// Library yang diperlukan
#include <WiFi.h>

// Definisi Autentikasi Wifi
#define WIFI_SSID "WiFi Sofyan"
#define WIFI_PASSWORD "15022001"

void setup() {
  // Setup
  Serial.begin(115200);
  initWifi();
}

void loop() {
  // Melakukan Autentikasi ke Jaringan WiFi kembali saat jaringan terputus
  if (WiFi.status() != WL_CONNECTED) {
    initWifi();
  }
}

// Fungsi Inisialisasi WiFi
void initWifi() {
  // Melakukan Autentikasi ke Jaringan WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke jaringan Wifi...");
    delay(500);
  }
  Serial.println("Berhasil terkoneksi ke " + (String)WIFI_SSID);
  Serial.print("Dengan IP: ");
  Serial.println(WiFi.localIP());
}
