/*
 * Program Pengujian Sensor Ultrasonic JSN-SR04T
 * Sofyan R. - 191311030
 */

// Deklarasi variabel dan pin yang dipakai
int trigPin = 12; // Pin D12 ESP32     
int echoPin = 14; // Pin D14 ESP32
long durasi;
float jarak;
float jarakKonversi;
float jarakKalibrasi;


// Deklarasi Variabel Millis
unsigned long prevMillis = 0;
unsigned long interval = 3000;

void setup() {
  // Inisialisai Input & Output
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
}

void loop() {
  if (millis() - prevMillis > interval || prevMillis == 0) {
    prevMillis = millis();
    // Mentrigger gelombang
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
  
    // Menghitung waktu pantulan gelombang
    durasi = pulseIn(echoPin, HIGH);
  
    // Menghitung jarak berdasarkan waktu pantul gelombang
  //  jarak = (durasi/2)/29;
  //  jarak = durasi/58;
    jarak = durasi*0.034/2;
  
    // Mengkalibrasi jarak untuk range ketinggian 0-20 cm
//    jarakKonversi = (jarak-38.5)*(-1);  // Saluran 1
    jarakKonversi = (jarak-38.5)*(-1);   // Saluran 2

//    jarakKalibrasi = (1.005*jarakKonversi)-0.105;   // Saluran 1
    jarakKalibrasi = (1.056*jarakKonversi)-0.539;    // Saluran 2
                                            
    Serial.print("JarakAsli: ");
    Serial.print(jarak);
    Serial.println(" cm");
    Serial.print("JarakKonversi: ");
    Serial.print(jarakKonversi);
    Serial.println(" cm");
    Serial.print("JarakKalibrasi: ");
    Serial.print(jarakKalibrasi);
    Serial.println(" cm");
    Serial.println("");
  }
}
