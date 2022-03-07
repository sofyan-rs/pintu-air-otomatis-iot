/*
 * Pengujian Sensor Kelembaban Tanah YL-69
 * Sofyan R. - 191311030
 */

// Deklarasi variabel dan pin yang dipakai
int analogPin = 2; // Pin D2 ESP32
int analogInput;
float kelembabanTanah;

void setup() {
  // Inisialisasi Input dan Output
  pinMode(analogPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // Membaca nilai input analog dari pin A0 sensor
  analogInput = analogRead(analogPin);
  Serial.print("Analog Input: ");
  Serial.println(analogInput);

  // Mengkonversi nilai pembacaan sensor menjadi persen (2100 = kering & 1400 = basah)
  kelembabanTanah = map(analogInput, 2064, 1400, 0, 100);
  Serial.print("Kelembaban Tanah: ");
  Serial.print(kelembabanTanah);
  Serial.println(" %");
  Serial.println("");
  delay(1000);
}
