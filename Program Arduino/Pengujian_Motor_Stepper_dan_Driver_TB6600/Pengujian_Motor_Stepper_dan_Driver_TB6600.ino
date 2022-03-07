/*
 * Program Pengujian Motor Stepper dan Driver TB6600
 * Sofyan R. - 191311030 - POLBAN - 2022
 */
 
// Definisi Pin Motor Stepper
#define dirPin 2
#define stepPin 4
#define CWButton 34
#define CCWButton 35

// Deklarasi Variabel Tombol Arah Gerak Motor Stepper
int CW = 0;
int CCW = 0;

void setup() {
  // Setup
  Serial.begin(115200);
  
  // Inisialisasi Input dan Output
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(CWButton, INPUT);
  pinMode(CCWButton, INPUT);
}

void loop() {
  // Membaca input dari Push Button
  CW = digitalRead(CWButton);
  CCW = digitalRead(CCWButton);
  // Kondisi saat Button CW HIGH
  if (CW == 1) {
    Serial.println("CW = 1");
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  // Kondisi saat Button CCW HIGH
  else if (CCW == 1) {
    Serial.println("CCW = 1");
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  // Kondisi saat Kedua Button LOW
  else if (CCW == 0 && CCW == 0) {
    Serial.println("CW = 0 & CCW = 0");
    digitalWrite(stepPin, LOW);
  }
}
