/*
 * Program Pengujian Baterai dan Modul Charger
 * Sofyan R. - 191311030 - POLBAN - 2022
 */

// Deklarasi Variabel Baterai Monitoring
int batPin  = 33;    // Pin D33 ESP32
int sensorBaterai;
float voltage;
int batPersentase;
//float kalBaterai = 0.282; // Saluran 1
float kalBaterai = 0.372; // Saluran 2

// Deklarasi Variabel Millis
unsigned long prevMillis = 0;
unsigned long interval = 5000;

void setup() {
  // Setup
  Serial.begin(115200);
  pinMode(batPin, INPUT);
}

void loop() {
  if (millis() - prevMillis > interval || prevMillis == 0) {
    prevMillis = millis();
    // Membaca Kondisi Baterai
    sensorBaterai = analogRead(batPin);
    voltage = (((sensorBaterai * 3.3) / 4095) * 2 + kalBaterai); // multiply by two as voltage divider network is 100K & 100K Resistor
    batPersentase = mapfloat(voltage, 2.8, 4.2, 0, 100); // 2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
    if (batPersentase >= 100) {
      batPersentase = 100;
    }
    if (batPersentase <= 0) {
      batPersentase = 1;
    }
  
    // Tampilkan pada Serial Monitor
    Serial.print("Analog Value = ");
    Serial.println(sensorBaterai);
    Serial.print("Output Voltage = ");
    Serial.println(voltage);
    Serial.print("Battery Percentage = ");
    Serial.println(batPersentase);
    Serial.println();
  }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
