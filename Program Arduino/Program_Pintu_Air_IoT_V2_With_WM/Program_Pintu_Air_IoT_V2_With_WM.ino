

/*
 * ------------------------------------------------------
 * Program Pintu Air Otomatis berbasis IoT - Tugas Akhir
 * ------------------------------------------------------
 * Nama   : Sofyan Rudiana Syamsi
 * NIM    : 191311030
 * Prodi  : D3 Teknik Elektronika
 * POLITEKNIK NEGERI BANDUNG - TAHUN 2022
 * ------------------------------------------------------
 */

// Library yang diperlukan
//#include <WiFi.h>
#include <WiFiManager.h>
#include <FirebaseESP32.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Nomer Saluran Air
#define nomerSaluran 1

// Definisi Autentikasi Firebase
#define DATABASE_URL "pintu-air-otomatis-iot-29db0-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyCvfN0mZdodt3ewGdN1ERucsktNo-FlsmM"

// Deklarasi Firebase Data Object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;

// Deklarasi Variabel Millis
unsigned long timeElapsed = 0;
unsigned long timeDatabase = 0;

// Deklarasi Variabel Path Firebase
String pathSaluran = "/saluran_" + String(nomerSaluran);
String pathMonitoring = pathSaluran + "/monitoring";
String pathKontrol = pathSaluran + "/kontrol";

// Deklarasi Variabel Host untuk Server
const char* server = "pintu-air.kdevz.net";
const int httpPort = 80;
const char* restAPI = "https://pintu-air.kdevz.net/api/kirim-data.php";
const char* apiKey = "Ny3BqnerHgnYBgs3mv6ADd4pnqPeXNfG";
WiFiClient client;

// Deklarasi Variabel Baterai Monitoring
int batPin  = 33;        // Pin D33 ESP32
int sensorBaterai;
float voltage;
int batPersentase;
float kalBaterai;

// Deklarasi Variabel Pembacaan Sensor Ultrasonik
const int trigPin = 12; // Pin D12 ESP32                                                                                                                                                                                
const int echoPin = 14; // Pin D14 ESP32
const int jarakSensor = 38.5;
long durasi;
float jarak;
float jarakKonversi;
float tinggiAir;

// Deklarasi Variabel Pembacaan Sensor Kelembaban Tanah
const int analogPin = 32; // Pin D32 ESP32
int analogInput;
float kelembabanTanah;

// Deklarasi Pin Motor Stepper (Pintu Air)
const int dirPin = 2;    // Pin D2 ESP32
const int stepPin = 4;   // Pin D4 ESP32

// Deklarasi Variabel Limit Switch
const int limitSwitch = 26; // Pin D26 ESP32
int Button = 0;
int kondisiPintuAir = 0;

// Deklarasi Variabel Pintu Air Firebase
int modePintuAir = 0;         
int bukatutupPintuAir = 0;
int saveDatabase = 0;
int batasLevelAir = 0;
int batasKelembabanTanah = 0;

void setup() {
  // Setup
  Serial.begin(115200);
  initDisplay();
  initWifi();
  initFirebase();
  initServer();

  // Inisialisasi Input dan Output
  pinMode(batPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  pinMode(analogPin, INPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(limitSwitch, INPUT_PULLUP);
}

void loop() {
  // Melakukan Autentikasi ke Jaringan WiFi kembali saat jaringan terputus
  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
    delay(3000);
  }
  
  // Membaca data setiap selang waktu 3000ms
  if (millis() - timeElapsed >= 3000 || timeElapsed == 0) {
      timeElapsed = millis();

      // Membaca Kondisi Pintu Air
      readPintuAir();
      
      // Membaca Status Baterai
      readBattery();
    
      // Membaca Data Sensor Ultrasonik
      readUltrasonik();
      
      // Membaca Data Sensor Kelembaban Tanah
      readMoisture();
  }
  
  // Mencetak Hasil Pembacaan Sensor pada Serial Monitor
  Serial.println("--------------------------------");
  Serial.println("Saluran " + String(nomerSaluran));
  Serial.println("--------------------------------");
  Serial.print("Kondisi Pintu Air : ");
  Serial.println(kondisiPintuAir);
  Serial.print("Baterai Status : ");
  Serial.print(batPersentase);
  Serial.println("%");
  Serial.print("Level Air : ");
  Serial.print(tinggiAir);
  Serial.println(" cm");
  Serial.print("Kelembaban Tanah : ");
  Serial.print(kelembabanTanah);
  Serial.println(" %");
  
  // Mengecek koneksi Firebase
  if (Firebase.ready() && signupOK == true) {

    // Mengirim Data Pembacaan Kondisi Pintu Air ke Firebase
    if (kondisiPintuAir == 1) {
      if (Firebase.RTDB.setInt(&fbdo, pathMonitoring + "/kondisi_pintu_air", 1)) {
        Serial.println("Data Pintu Air Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    } else {
      if (Firebase.RTDB.setInt(&fbdo, pathMonitoring + "/kondisi_pintu_air", 0)) {
        Serial.println("Data Pintu Air Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    }
    
    // Mengirim Data Pembacaan Baterai ke Firebase
    if (Firebase.RTDB.setInt(&fbdo, pathMonitoring + "/baterai_status", batPersentase)) {
      Serial.println("Data Baterai Terkirim");
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mengirim Data Pembacaan Sensor Ultrasonik ke Firebase
    if (Firebase.RTDB.setFloat(&fbdo, pathMonitoring + "/sensor_level_air", tinggiAir)) {
      Serial.println("Data Sensor Ultrasonik Terkirim");
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mengirim Data Pembacaan Sensor Kelembaban Tanah ke Firebase
    if (Firebase.RTDB.setFloat(&fbdo, pathMonitoring + "/sensor_kelembaban_tanah", kelembabanTanah)) {
      Serial.println("Data Sensor Kelembaban Tanah Terkirim");
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mencetak Hasil Pembacaan dari Firebase pada Serial Monitor
    Serial.println("--------------------------------");
    Serial.println("Data Kontrol Firebase");
    Serial.println("--------------------------------");
    
    // Mengambil Data Mode Pintu Air dari Firebase
    if (Firebase.RTDB.getInt(&fbdo, pathKontrol + "/mode_pintu_air")) {
      if (fbdo.dataType() == "int") {
        modePintuAir = fbdo.intData();
        Serial.print("Mode Pintu Air : ");
        Serial.println(modePintuAir);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mengambil Data Batas Level Air dari Firebase
    if (Firebase.RTDB.getInt(&fbdo, pathKontrol + "/batas_level_air")) {
      if (fbdo.dataType() == "int") {
        batasLevelAir = fbdo.intData();
        Serial.print("Batas Level Air : ");
        Serial.println(batasLevelAir);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mengambil Data Batas Kelembaban Tanah dari Firebase
    if (Firebase.RTDB.getInt(&fbdo, pathKontrol + "/batas_kelembaban_tanah")) {
      if (fbdo.dataType() == "int") {
        batasKelembabanTanah = fbdo.intData();
        Serial.print("Batas Kelembaban Tanah : ");
        Serial.println(batasKelembabanTanah);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Mengambil Status Save ke Database MySQL dari Firebase
    if (Firebase.RTDB.getInt(&fbdo, pathKontrol + "/save_database")) {
      if (fbdo.dataType() == "int") {
        saveDatabase = fbdo.intData();
        Serial.print("Save Database : ");
        Serial.println(saveDatabase);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    // Menjalankan Fungsi Kontrol Pintu Air Otomatis
    autoPintuAir();
    
    // Mengambil Data Buka Tutup Pintu Air dari Firebase
    if (Firebase.RTDB.getInt(&fbdo, pathKontrol + "/buka_pintu_air")) {
      if (fbdo.dataType() == "int") {
        bukatutupPintuAir = fbdo.intData();
        Serial.print("Buka/Tutup : ");
        Serial.println(bukatutupPintuAir);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
    Serial.println("--------------------------------");

    // Menjalankan Fungsi Buka Tutup Pintu Air
    kontrolPintuAir();

    // Mengirim Data ke Database MySQL
    if (millis() - timeDatabase >= 60000 || timeDatabase == 0) {
      timeDatabase = millis();
      if (saveDatabase == 1) {
        sendDatabase();
      }
    }
    Serial.println();    
  }
  // Display Monitoring
  displayMonitor();
}

// Fungsi Inisialisasi Display OLED
void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Initializing System");
  display.display();
  delay(1000);
}

// Fungsi Reset Display
void resetDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
}

// Fungsi Inisialisasi WiFi
void initWifi() {
  // Melakukan Autentikasi ke Jaringan WiFi
  WiFi.mode(WIFI_STA);
  Serial.println("Menghubungkan ke jaringan WiFi");
  // Display OLED
  resetDisplay();
  display.println("Menghubungkan ke WiFi...");
  display.display();
  WiFiManager wifiManager;
  if (!wifiManager.autoConnect("WiFiManagerAP", "password")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    wifiManager.resetSettings();
    ESP.restart();
    delay(1000);
  }
  Serial.println();
  Serial.println("Berhasil terkoneksi ke WiFi");
  Serial.print("Dengan IP: ");
  Serial.println(WiFi.localIP());
  // Display OLED
  resetDisplay();
  display.println("Berhasil terkoneksi");
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
}

// Fungsi Inisialisai Firebase
void initFirebase() {
  // Assign the api key (required)
  config.api_key = API_KEY;
  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;
  // Melakukan Sign Up
  if (Firebase.signUp(&config, &auth, "", "")){
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  // Melakukan Authentication ke Firebase
  Serial.println("Menghubungkan ke Firebase...");
  // Display OLED
  resetDisplay();
  display.println("Menghubungkan ke Firebase...");
  display.display();
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(2000);
}

void initServer() {
  // Display OLED
  resetDisplay();
  display.println("Menghubungkan ke Web Server...");
  display.display();
  // Test koneksi ke server
  if (!client.connect(server, httpPort)) {
    Serial.println("Gagal Terkoneksi ke web server");
    return;
  }
  delay(1000);
}

// Fungsi untuk Display Monitoring
void displayMonitor() {
  // Display OLED
  resetDisplay();
  display.println("SALURAN " + (String)nomerSaluran);
  display.println("---------------");
  display.println("Baterai : " + (String)batPersentase + "%");
  if (WiFi.status() != WL_CONNECTED) {
    display.println("Wifi Tidak Terhubung");
    display.println("Coba setting kembali");
    display.println("192.168.4.1");
    display.display();
    return;
  } else {
    display.println("Wifi : OK");
  }
  if (Firebase.ready() && signupOK == true && Firebase.RTDB.getInt(&fbdo, pathMonitoring + "/kondisi_pintu_air")) {
    display.println("Firebase : OK");
  } else {
    display.println("Firebase : Failed");
  }
  if (!client.connect(server, httpPort)) {
    display.println("Server : Failed");
  } else {
    display.println("Server : OK");
  }
  display.display();
}

// Fungsi Kirim Data ke Database (HTTP Protocol => jadi agak lambat)
void sendDatabase() {
  // Jika terkoneksi ke server, maka kirim data
  HTTPClient http;
  http.begin(restAPI);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = (String)"api_key=" + apiKey + "&saluran=" + nomerSaluran + "&level_air=" + tinggiAir + "&kelembaban_tanah=" + kelembabanTanah + "&kondisi_pintu_air=" + kondisiPintuAir;
  auto httpCode = http.POST(postData);
  String payload = http.getString();
  Serial.print("Response: ");
  Serial.println(payload); 
  http.end();
}

// Fungsi Konversi Voltage Battery ke Persentase
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Fungsi Baca Status Baterai
void readBattery() {
  // Membaca Kondisi Baterai
  if (nomerSaluran == 1){
    kalBaterai = 0.282; // Saluran 1
  } else if (nomerSaluran == 2){
    kalBaterai = 0.372; // Saluran 2
  }
  sensorBaterai = analogRead(batPin);
  voltage = (((sensorBaterai * 3.3) / 4095) * 2 + kalBaterai); // multiply by two as voltage divider network is 100K & 100K Resistor
  batPersentase = mapfloat(voltage, 2.8, 4.2, 0, 100); // 2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
  if (batPersentase >= 100) {
    batPersentase = 100;
  }
  if (batPersentase <= 0) {
    batPersentase = 1;
  }
}

// Fungsi Baca Sensor Ultrasonik
void readUltrasonik() {
  // Mentrigger gelombang
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  // Menghitung waktu pantulan gelombang
  durasi = pulseIn(echoPin, HIGH);
  // Menghitung jarak berdasarkan waktu pantul gelombang
  jarak = durasi*0.034/2; 
  // Mengkalibrasi jarak untuk range ketinggian 0-20 cm
  if (nomerSaluran == 1){
    // Saluran 1
    jarakKonversi = (jarak-jarakSensor)*(-1);
    tinggiAir = (1.005*jarakKonversi)-0.105;
  } else if (nomerSaluran == 2){
    // Saluran 2
    jarakKonversi = (jarak-jarakSensor)*(-1);
    tinggiAir = (1.056*jarakKonversi)-0.539;
  }
  // Membatasi pembacaan sensor untuk range ketinggian 0-20 cm
  if(tinggiAir < 0) {
    tinggiAir = 0;
  } else if (tinggiAir > 20) {
    tinggiAir = 20;
  }
}

// Fungsi Baca Sensor Kelembaban Tanah
void readMoisture() {
  // Membaca nilai input analog dari pin A0 sensor
  analogInput = analogRead(analogPin);
  // Mengkonversi nilai pembacaan sensor menjadi skala 1-10 (4095 = kering & 1000 = sangat basah)
  kelembabanTanah = map(analogInput, 4095, 1000, 1, 10);
  // Membatasi Pembacaan Sensor
  if (kelembabanTanah < 1){
    kelembabanTanah = 1;
  } else if (kelembabanTanah > 10) {
    kelembabanTanah = 10;
  }
}

// Fungsi Baca Kondisi Pintu Air
void readPintuAir() {
  // Membaca input dari Limit Switch
  Button = digitalRead(limitSwitch);
  if (Button == 1) {
    kondisiPintuAir = 1;
  } else {
    kondisiPintuAir = 0;
  }
}

// Fungsi Buka Pintu Air
void bukaPintuAir(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
}

// Fungsi Tutup Pintu Air
void tutupPintuAir(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
}

// Fungsi Kontrol Pintu Air Otomatis
void autoPintuAir() {
  // Buka Tutup Pintu berdasarkan Mode Otomatis
  if (modePintuAir == 1) {
    // Otomatis berdasarkan level air
    if (tinggiAir <= batasLevelAir && kondisiPintuAir == 1) {
      if (Firebase.RTDB.setInt(&fbdo, pathKontrol + "/buka_pintu_air", 1)) {
        Serial.println("Data Kontrol Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    } else if (tinggiAir > batasLevelAir && kondisiPintuAir == 0) {
      if (Firebase.RTDB.setInt(&fbdo, pathKontrol + "/buka_pintu_air", 0)) {
        Serial.println("Data Kontrol Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    }
  } else if (modePintuAir == 2) {
    // Otomatis berdasarkan kelembaban tanah
    if (kelembabanTanah <= batasKelembabanTanah && kondisiPintuAir == 1) {
      if (Firebase.RTDB.setInt(&fbdo, pathKontrol + "/buka_pintu_air", 1)) {
        Serial.println("Data Kontrol Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    } else if (kelembabanTanah > batasKelembabanTanah && kondisiPintuAir == 0) {
      if (Firebase.RTDB.setInt(&fbdo, pathKontrol + "/buka_pintu_air", 0)) {
        Serial.println("Data Kontrol Terkirim");
      } else {
        Serial.println(fbdo.errorReason());
      }
    }
  }
}

// Fungsi Kontrol Pintu Air
void kontrolPintuAir() {
  // Membuka dan Menutup Pintu Air sesuai Data dari Firebase
  if (bukatutupPintuAir == 1 && kondisiPintuAir == 1) {
    bukaPintuAir(400);
  } else if (bukatutupPintuAir == 0 && kondisiPintuAir == 0) {
    tutupPintuAir(400);
  }
}
