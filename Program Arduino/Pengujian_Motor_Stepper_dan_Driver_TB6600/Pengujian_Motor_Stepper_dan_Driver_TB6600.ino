#define dirPin 2
#define stepPin 4

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  forward(400);
  delay(5000);
  reverse(400);
  delay(5000);
}

void forward(int steps) {
  digitalWrite(dirPin, HIGH); // Set Direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
}

void reverse(int steps) {
  digitalWrite(dirPin, LOW); // Set Direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
}
