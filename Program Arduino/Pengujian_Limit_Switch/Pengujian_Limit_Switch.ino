/*
 * Program Pengujian Limit Switch
 * Sofyan R. - 191311030 - POLBAN - 2022
 */

#define limitSwitch 26
int Button = 0;

void setup() {
  Serial.begin(115200);
  // Inisialisasi Input
  pinMode(limitSwitch, INPUT_PULLUP);
}

void loop() {
  // Membaca input dari Limit Switch
  Button = digitalRead(limitSwitch);
  if (Button == 1) {
    Serial.println("Button = 1");
  } else {
    Serial.println("Button = 0");
  }
}
