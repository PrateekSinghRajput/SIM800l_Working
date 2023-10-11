#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
int X;
int Y;
int sec = 50;
int t = 0;
int i = 0;
int check = 1;
int chk = 0;
int P = A3;
int N = A2;
int tim = 0;
float Time = 0;
float frequency = 0;
float waterFlow = 0;
float total = 0;
float LS = 0;
float average = 0;
const int input = A0;
const int test = 9;
void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  pinMode(test, OUTPUT);
  analogWrite(test, 100);
  pinMode(P, OUTPUT);
  pinMode(N, OUTPUT);
  digitalWrite(P, HIGH);
  digitalWrite(N, LOW);
  for (i = 0; i < sec; i++) {
    delay(1000);
  }
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  Serial.println("Your water supply notification system is ready.");
  delay(100);
  Serial.println((char)26);
  delay(1000);
}
void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    if (tm.Hour > 12) {
      if (tm.Hour == 13) tim = 1;
      if (tm.Hour == 14) tim = 2;
      if (tm.Hour == 15) tim = 3;
      if (tm.Hour == 16) tim = 4;
      if (tm.Hour == 17) tim = 5;
      if (tm.Hour == 18) tim = 6;
      if (tm.Hour == 19) tim = 7;
      if (tm.Hour == 20) tim = 8;
      if (tm.Hour == 21) tim = 9;
      if (tm.Hour == 22) tim = 10;
      if (tm.Hour == 23) tim = 11;
    } else {
      tim = tm.Hour;
    }
    X = pulseIn(input, HIGH);
    Y = pulseIn(input, LOW);
    Time = X + Y;
    frequency = 1000000 / Time;
    waterFlow = frequency / 7.5;
    LS = waterFlow / 60;
    if (frequency >= 0) {
      if (isinf(frequency)) {
        if (chk == 1) {
          Serial.println("AT+CNMI=2,2,0,0,0");
          delay(1000);
          Serial.println("AT+CMGF=1");
          delay(500);
          Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
          delay(1000);
          Serial.print("Time: ");
          delay(10);
          Serial.print(tim);
          delay(10);
          Serial.print(":");
          delay(10);
          Serial.print(tm.Minute);
          delay(10);
          if (tm.Hour >= 12) {
            Serial.println(" PM");
          }
          if (tm.Hour < 12) {
            Serial.println(" AM");
          }
          delay(10);
          Serial.println("Water Supply is Ended.");
          delay(100);
          Serial.print("Average Water Flow (Litre/Min): ");
          delay(100);
          Serial.println(average);
          delay(100);
          Serial.print("Total Water Delivered: ");
          delay(100);
          Serial.print(total);
          delay(100);
          Serial.println(" Litre");
          delay(100);
          Serial.println((char)26);
          delay(5000);
          t = 0;
          total = 0;
          average = 0;
          chk = 0;
          check = 1;
        }
      } else {
        if (check == 1) {
          Serial.println("AT+CNMI=2,2,0,0,0");
          delay(1000);
          Serial.println("AT+CMGF=1");
          delay(500);
          Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
          delay(1000);
          Serial.print("Time: ");
          delay(10);
          Serial.print(tim);
          delay(10);
          Serial.print(":");
          delay(10);
          Serial.print(tm.Minute);
          delay(10);
          if (tm.Hour >= 12) {
            Serial.println(" PM");
          }
          if (tm.Hour < 12) {
            Serial.println(" AM");
          }
          delay(10);
          Serial.println("The water is being supplied now.");
          delay(100);
          Serial.println((char)26);
          delay(1000);
          check = 0;
          chk = 1;
        }
        t = t + 1;
        total = total + LS;
        average = total / t;
        average = average * 60;
      }
    }
    delay(1000);
  }
}