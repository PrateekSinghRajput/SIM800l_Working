int temp = 0;
int i = 0;
int j = 0;
char str[15];
boolean state = false;
const int LOCK = 7;
void setup() {
  Serial.begin(9600);
  pinMode(LOCK, OUTPUT);
  digitalWrite(LOCK, LOW);
  for (j = 0; j < 60; j++) {
    delay(1000);
  }
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  Serial.println("Your car is ready to receive SMS commands.");
  delay(100);
  Serial.println((char)26);
  delay(1000);
}
void loop() {
  if (temp == 1) {
    check();
    temp = 0;
    i = 0;
    delay(1000);
  }
}
void serialEvent() {
  while (Serial.available()) {
    if (Serial.find("/")) {
      delay(1000);
      while (Serial.available()) {
        char inChar = Serial.read();
        str[i++] = inChar;
        if (inChar == '/') {
          temp = 1;
          return;
        }
      }
    }
  }
}
void check() {
  if (!(strncmp(str, "qwerty", 6)))  // (Password Here, Length)
  {
    if (!state) {
      digitalWrite(LOCK, HIGH);
      delay(1000);
      Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
      delay(1000);
      Serial.println("Central Lock: Unlocked.");
      Serial.println("Ignition Lock: Unlocked.");
      delay(100);
      Serial.println((char)26);
      state = true;
      delay(1000);
    } else if (state) {
      digitalWrite(LOCK, LOW);
      delay(1000);
      Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
      delay(1000);
      Serial.println("Central Lock: Locked.");
      Serial.println("Ignition Lock: Locked.");
      delay(100);
      Serial.println((char)26);
      state = false;
      delay(1000);
    }
  } else if (!(strncmp(str, "status", 6))) {
    Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    if (!state) {
      Serial.println("The System is Working Fine.");
      Serial.println("Central Lock: Locked.");
      Serial.println("Ignition Lock: Locked.");
    }
    if (state) {
      Serial.println("The System is Working Fine.");
      Serial.println("Central Lock: Unlocked.");
      Serial.println("Ignition Lock: Unlocked.");
    }
    delay(100);
    Serial.println((char)26);
    delay(1000);
  }
}