/*
 * Program Komunikasi IoT antara Mikrokontroler dengan Database MySQL
 * Sofyan R. - 191311030 - POLBAN - 2022
 */

// Library yang diperlukan
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// Definisi Autentikasi Wifi
#define WIFI_SSID "Kosan ibu Ai"
#define WIFI_PASSWORD "gataulupa"

// Deklarasi Variabel Host untuk Server
const char* server = "192.168.1.8";
const int httpPort = 80;
const char* restAPI = "http://192.168.1.8/pintu-air/api/kirim-data.php";
const char* apiKey = "Ny3BqnerHgnYBgs3mv6ADd4pnqPeXNfG";
int saluran = 1;

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

// Deklarasi Variabel Pintu Air
int modePintuAir = 0;
int kondisiPintuAir = 0;

void setup() {
  // Setup
  Serial.begin(115200);
  initWifi();
  initServer();

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

  // Mengirim Data ke Database
  sendData();
  Serial.println();
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

void initServer() {
  // Test koneksi ke server
  WiFiClient client;
  if (!client.connect(server, httpPort)) {
    Serial.println("Gagal Terkoneksi ke web server");
    return;
  }
}

// Fungsi Kirim Data ke Database
void sendData() {
  // Jika terkoneksi ke server, maka kirim data
  HTTPClient http;
  http.begin(restAPI);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = (String)"api_key=" + apiKey + "&saluran=" + saluran + "&level_air=" + tinggiAir + "&kelembaban_tanah=" + kelembabanTanah + "&kondisi_pintu_air=" + kondisiPintuAir;
  auto httpCode = http.POST(postData);
  String payload = http.getString();
  Serial.println(postData);
  Serial.print("Response: ");
  Serial.println(payload); 
  http.end();
}
