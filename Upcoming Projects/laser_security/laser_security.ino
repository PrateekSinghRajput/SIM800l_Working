#include <SoftwareSerial.h>
SoftwareSerial gsm(2,3);
int LDR = A0;
int OP = 7;
int start = 6;
int LED = 5;
int th = 300;
int x;
unsigned long A = 1000L;
unsigned long B = A * 60;
unsigned long C = B * 2;
void setup()
{
Serial.begin(9600);
gsm.begin(9600);
pinMode(LDR,INPUT);
pinMode(OP,OUTPUT);
pinMode(start,INPUT);
pinMode(LED,OUTPUT);
}
void loop()
{
if(digitalRead(start)==1)
{
digitalWrite(LED,HIGH);
delay(C);
A:
x = analogRead(A0);
Serial.println(x);
if(x<=th)
{
delay(2);
goto A;
}
if(x>=th)
{
digitalWrite(OP,HIGH);
Serial.println("Sending SMS......\n");
gsm.println("AT+CMGF=1");
delay(1000);
gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); 
delay(1000);
gsm.println("Security Warning: Intruder detected."); 
delay(100);
gsm.println((char)26); 
delay(1000);
Serial.println("Message is sent\n");
delay(C);
digitalWrite(OP,LOW);
goto A;
}
}
}