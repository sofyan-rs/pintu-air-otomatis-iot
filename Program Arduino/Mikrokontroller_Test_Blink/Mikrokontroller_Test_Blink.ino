/*
 * Mikrokontroller ESP32 Test - Blink Built in LED
 * Sofyan R. - 191311030
*/

// Deklarasi pin yang dipakai
int ledPin = 2;  // Pin D2 yang terhubung dengan LED Built in

void setup() {
  // Inisialisasi pin 2 sebagai output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // LED on (HIGH)
  delay(1000);                // delay 1 detik
  digitalWrite(ledPin, LOW);  // LED off (LOW)
  delay(1000);                // delay 1 detik
}
