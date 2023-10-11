int LED = 8;
int motor = 9;
int temp = 0;
int i = 0;
char str[15];
void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(motor, LOW);
  digitalWrite(LED, LOW);
  delay(20000);
  delay(20000);
  delay(20000);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  Serial.println("System is ready to receive commands.");
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
  if (!(strncmp(str, "motor on", 8))) {
    digitalWrite(motor, HIGH);
    digitalWrite(LED, HIGH);
    delay(1000);
    Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    Serial.println("Motor Activated");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  } else if (!(strncmp(str, "motor off", 9))) {
    digitalWrite(motor, LOW);
    digitalWrite(LED, LOW);
    delay(1000);
    Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    Serial.println("Motor deactivated");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  } else if (!(strncmp(str, "test", 4))) {
    Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    Serial.println("The System is Working Fine.");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  }
}