/*
 * Pengujian Mikrokontroller
 * Sofyan R. - 191311030
*/

// Deklarasi pin yang dipakai
const int D2 = 2;
const int D4 = 4;
const int D12 = 12;
const int D14 = 14;
const int D21 = 21;
const int D22 = 22;
const int D32 = 32;
const int D33 = 33;

void setup() {
  // Inisialisasi pin-pin sebagai output
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D14, OUTPUT);
  pinMode(D21, OUTPUT);
  pinMode(D22, OUTPUT);
  pinMode(D32, OUTPUT);
  pinMode(D33, OUTPUT);
}

void loop() {
  // Memberi Logic HIGH pada semua pin yang dipakai
  digitalWrite(D2, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D12, HIGH);
  digitalWrite(D14, HIGH);
  digitalWrite(D21, HIGH);
  digitalWrite(D22, HIGH);
  digitalWrite(D32, HIGH);
  digitalWrite(D33, HIGH);
}
