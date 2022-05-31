/*
 * Pengujian Sensor Kelembaban Tanah YL-69
 * Sofyan R. - 191311030
 */

// Deklarasi variabel dan pin yang dipakai
int analog1Pin = 32; // Pin D32 ESP32
int analog2Pin = 33; // Pin D32 ESP32
int analog1Input;
int analog2Input;
float kelembabanTanah1;
float kelembabanTanah2;

// Deklarasi Variabel Millis
unsigned long prevMillis = 0;
unsigned long interval = 2000;

void setup() {
  // Inisialisasi Input dan Output
  pinMode(analog1Pin, INPUT);
//  pinMode(analog2Pin, INPUT);
  Serial.begin(115200);
}

void loop() {
  if (millis() - prevMillis > interval || prevMillis == 0) {
    prevMillis = millis();
    // Membaca nilai input analog dari pin A0 sensor
    analog1Input = analogRead(analog1Pin);
    Serial.print("Analog Input 1: ");
    Serial.println(analog1Input);
//    analog2Input = analogRead(analog2Pin);
//    Serial.print("Analog Input 2: ");
//    Serial.println(analog2Input);
  
    // Mengkonversi nilai pembacaan sensor menjadi menjadi skala 1-10 (4095 = kering & 1000 = basah)
    kelembabanTanah1 = map(analog1Input, 4095, 1000, 1, 10);
    Serial.print("Kelembaban Tanah 1: ");
    Serial.print(kelembabanTanah1);
    Serial.println("");
//    kelembabanTanah2 = map(analog2Input, 4095, 1000, 1, 10);
//    Serial.print("Kelembaban Tanah 2: ");
//    Serial.print(kelembabanTanah2);
//    Serial.println("");
  }
}
