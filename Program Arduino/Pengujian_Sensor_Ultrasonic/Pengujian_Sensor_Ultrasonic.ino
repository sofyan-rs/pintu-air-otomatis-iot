/*
 * Program Pengujian Sensor Ultrasonic JSN-SR04T
 * Sofyan R. - 191311030
 */

// Deklarasi variabel dan pin yang dipakai
int trigPin = 2;                                                                                                                                                                                   // Pin D2 ESP32
int echoPin = 4; // Pin D4 ESP32
long durasi;
float jarak;
float jarakKalibrasi = 0;

void setup() {
  // Inisialisai Input & Output
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
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
  jarakKalibrasi = (jarak-40)*(-1);
                                          
  Serial.print("Jarak: ");
  Serial.print(jarakKalibrasi);
  Serial.println(" cm");
  delay(1000);
}
