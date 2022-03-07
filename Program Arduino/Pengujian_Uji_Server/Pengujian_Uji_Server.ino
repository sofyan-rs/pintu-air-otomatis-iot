/*
 * Program untuk uji koneksi ke web server
 * Sofyan R. - 191311030
 */

// Library yang diperlukan
#include <WiFi.h>
#include <WiFiClient.h>

// Definisi Autentikasi Wifi
#define WIFI_SSID "WiFi Sofyan"
#define WIFI_PASSWORD "15022001"

// Deklarasi Variabel Host untuk Server
const char* server = "192.168.1.8";
const int httpPort = 80;

void setup() {
  // Setup
  Serial.begin(115200);
  initWifi();
  initServer();
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
  Serial.println("Berhasil terhubung ke " + (String)WIFI_SSID);
  Serial.print("Dengan IP: ");
  Serial.println(WiFi.localIP());
}

// Fungsi untuk mengecek koneksi ke web server
void initServer() {
  // Test koneksi ke server
  WiFiClient client;
  if (!client.connect(server, httpPort)) {
    Serial.println("Gagal Terkoneksi ke web server");
    return;
  }
  Serial.println("Berhasil terhubung ke server: " + (String)server);
}
