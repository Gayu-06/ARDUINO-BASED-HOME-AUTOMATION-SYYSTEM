 // -------- PIN SETUP --------
int pirPin = 2;     // PIR sensor
int ldrPin = 5;     // Digital LDR
int lm35Pin = A1;   // LM35

// LEDs
int lightLED = 8;   // Yellow
int fanLED   = 9;   // Blue
int alertLED = 10;  // Red

// Threshold
float tempThreshold = 25.0;

void setup() {
  Serial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);

  pinMode(lightLED, OUTPUT);
  pinMode(fanLED, OUTPUT);
  pinMode(alertLED, OUTPUT);

  Serial.println("System Started...");
}

void loop() {

  // -------- READ SENSORS --------
  int motion   = digitalRead(pirPin);
  int ldrState = digitalRead(ldrPin);

  int rawValue = analogRead(lm35Pin);

  // Convert LM35 reading
  float voltage = rawValue * (5.0 / 1023.0);
  float temperature = voltage * 100;

  // -------- SERIAL OUTPUT --------
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C | ");
  Serial.print("PIR: "); Serial.print(motion);
  Serial.print(" | LDR: "); Serial.println(ldrState);

  // -------- 🟡 LIGHT CONTROL --------
  // Light ON if DARK or MOTION detected
  if (ldrState == LOW || motion == HIGH) {
    digitalWrite(lightLED, HIGH);
  } else {
    digitalWrite(lightLED, LOW);
  }

  // -------- 🔵 FAN CONTROL --------
  if (temperature > tempThreshold) {
    digitalWrite(fanLED, HIGH);
  } else {
    digitalWrite(fanLED, LOW);
  }

  // -------- 🔴 ALERT CONTROL --------
  // Alert when motion detected
  if (motion == HIGH) {
    digitalWrite(alertLED, HIGH);
  } else {
    digitalWrite(alertLED, LOW);
  }

  delay(1000);
}