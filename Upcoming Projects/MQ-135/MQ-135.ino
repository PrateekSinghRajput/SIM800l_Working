#include <SoftwareSerial.h>
SoftwareSerial gsm(2,3);
int input=A0;
int output=7;
int th=600;  
unsigned long A = 1000L;
unsigned long B = A * 60;
unsigned long C = B * 3;
unsigned long D = B * 30;
void setup()
{
Serial.begin(9600);
pinMode(output,OUTPUT);
digitalWrite(output,LOW);
Serial.println("Sensor waiting for optimum temperature");
delay(C);
Serial.println("Sending test SMS......");
gsm.begin(9600);
gsm.println("AT+CMGF=1");
delay(1000);
gsm.println("AT+CMGS='+91xxxxxxxxxx'r"); 
delay(1000);
gsm.println("LPG leak, test SMS");
delay(100);
gsm.println((char)26); 
delay(1000);
Serial.println("Test SMS sent.");
}
void loop()
{
Serial.println(analogRead(input));
delay(1000);
if(analogRead(input)>th)
{
delay(5000);
if(analogRead(input)>th)
{
Serial.println("Sending SMS............");
Serial.println(analogRead(input));
gsm.println("AT+CMGF=1");
delay(1000);
gsm.println("AT+CMGS='+91xxxxxxxxxxx'r"); 
delay(1000);
gsm.println("Warning: LPG gas leak detected");
delay(100);
gsm.println((char)26); 
delay(1000);
Serial.println("SMS sent.");
digitalWrite(output,HIGH);
delay(B);
delay(B);
digitalWrite(output,LOW);
delay(D);
}
}
}