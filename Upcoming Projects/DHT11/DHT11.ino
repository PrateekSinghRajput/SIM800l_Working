#include <dht.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(2, 3);
#define DHTxxPIN A1
dht DHT;
int p = A0;
int n = A2;
int ack;
int msgsend = 0;
int th = 45;
unsigned long A = 1000L;
unsigned long B = A * 60;
unsigned long C = B * 30;
void setup() {
  Serial.begin(9600);
  gsm.begin(9600);
  pinMode(p, OUTPUT);
  pinMode(n, OUTPUT);
  digitalWrite(p, 1);
  digitalWrite(n, 0);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  gsm.println("This is a test SMS from GSM modem");
  delay(100);
  gsm.println((char)26);
  delay(1000);
}
void loop() {
top:
  msgsend = 0;
  ack = 0;
  int chk = DHT.read11(DHTxxPIN);
  switch (chk) {
    case DHTLIB_ERROR_CONNECT:
      ack = 1;
      break;
  }
  if (ack == 0) {
    Serial.print("Temperature(°C) = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity(%) = ");
    Serial.println(DHT.humidity);
    Serial.println("\n");
    delay(2000);
  }
  if (ack == 1) {
goagain:
    msgsend = msgsend + 1;
    Serial.print("NO DATA");
    Serial.print("\n\n");
    Serial.println("Sending SMS......\n");
    delay(500);
    gsm.println("AT+CMGF=1");
    delay(1000);
    gsm.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    gsm.println("No data from sensor/Sensor disconnected");
    delay(100);
    gsm.println((char)26);
    delay(1000);
    Serial.println("Message is sent\n");
    if (msgsend == 2) {
      delay(C);
      goto top;
    } else {
      delay(10000);
      goto goagain;
    }
  }
  if (DHT.temperature >= th) {
doagain:
    msgsend = msgsend + 1;
    Serial.println("Sending SMS......\n");
    gsm.println("AT+CMGF=1");
    delay(1000);
    gsm.println("AT+CMGS=\"+91xxxxxxxxx\"\r");
    delay(1000);
    gsm.println("Fire Alert:");
    gsm.print(DHT.temperature);
    gsm.print(" degree celsius");
    delay(100);
    gsm.println((char)26);
    delay(1000);
    Serial.println("Message is sent\n");
    if (msgsend == 2) {
      delay(C);
      goto top;
    } else {
      delay(10000);
      goto doagain;
    }
  }
}