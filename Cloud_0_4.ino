//Libraries
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <NTPClient.h>
#include <ESP8266httpUpdate.h>

//Time Server
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//Wetter Server (CHANGE munich-12836564 to the yahoo area code you life in)
const char hostname[] = "query.yahooapis.com";
const String url = "/v1/public/yql?q=select%20item.condition.code%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22munich-12836564%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
const int port = 80;
unsigned long timeout = 800;
WiFiClient client;

// Other variables
char w;
int sensorPin1 = D5;
int LEDYellow = D4;
int LEDBright1 = D0;
int LEDBright2 = D1;
int LEDBlue1 = D2;
int LEDBlue2 = D3;
int brightness1 = 0;
int brightness2 = 0;
int fadeAmount = 5;

//////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //Define Pins
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDBright1, OUTPUT);
  pinMode(LEDBright2, OUTPUT);
  pinMode(LEDBlue2, OUTPUT);
  pinMode(LEDBlue1, OUTPUT);
  pinMode(sensorPin1, INPUT);

  //Connect to WIFI
  WiFi.disconnect();
  delay(1000);
  WiFi.begin("ENTER WIFI SSID HERE", "ENTER WIFI PASSWORD HERE");
  delay(1000);
  timeClient.begin();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (digitalRead(sensorPin1) == 1) {
    if (hour() < 22 && hour() > 5){
      weather();
      }
    else {
     for (int x = 0; x < 2; x++) {
        night();
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// Check current time (hours)
int hour() {
  timeClient.update();       
  int h = timeClient.getHours() + 2; //+1 wintertime, +2 sommertime
  client.stop();
  return h;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Read weather
int weather() {
  unsigned long timestamp;
  int wcode;

  client.connect(hostname, port);

  String req = "GET " + url + " HTTP/1.1\r\n" +
               "Host: " + hostname + "\r\n" +
               "Connection: close\r\n" +
               "\r\n";
  client.print(req);

  delay(250);
  timestamp = millis();
  while ( !client.available() && (millis() < timestamp + timeout) ) {
    delay(1);
  }

  if ( client.find("code\":") ) {
  long wcodel = client.parseInt();
  wcode = (int)wcodel;
  }

  while ( client.available() ) {
    client.readStringUntil('\r');
  }

  client.stop();

if ((wcode > 0) && (wcode < 7)){
  rain();
}
else if ((wcode > 7) && (wcode < 13)){
  rain();
}
else if (wcode == 35 ){
  rain();
}
else if ((wcode > 36) && (wcode < 41)){
  rain();
}
else if (wcode == 45){
  rain();
}
else if (wcode == 47){
  rain();
}
else if (wcode == 7){
  snow();
}
else if ((wcode > 12) && (wcode < 19)){
  snow();
}
else if ((wcode > 40) && (wcode < 44)){
  snow();
}
else if (wcode == 46){
  snow();
}
else if ((wcode > 18) && (wcode < 29)){
  cloud();
}
else if (wcode == 44){
  cloud();
}
else if ((wcode > 28) && (wcode < 35)){       
  sun();
}
else if (wcode == 36){       
  sun();
}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void LEDlow() {
  digitalWrite(LEDYellow, LOW);
  digitalWrite(LEDBlue1, LOW);
  digitalWrite(LEDBlue2, LOW);
  digitalWrite(LEDBright1, LOW);
  digitalWrite(LEDBright2, LOW);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void rain() {
  for (int x = 0; x < 8; x++) {
    digitalWrite(LEDBright1, HIGH);
    delay(10);
    digitalWrite(LEDBright1, LOW);
    delay(400);
    digitalWrite(LEDBright2, HIGH);
    delay(100);
    digitalWrite(LEDBright2, LOW);
    delay(100);
    digitalWrite(LEDBright1, HIGH);
    digitalWrite(LEDBright2, HIGH);
    delay(50);
    digitalWrite(LEDBright1, LOW);
    digitalWrite(LEDBright2, LOW);
    delay(600);
    digitalWrite(LEDBright1, HIGH);
    digitalWrite(LEDBright2, HIGH);
    delay(80);
    digitalWrite(LEDBright1, LOW);
    digitalWrite(LEDBright2, LOW);
    delay(100);
    digitalWrite(LEDBright2, HIGH);
    delay(100);
    digitalWrite(LEDBright2, LOW);
    delay(400);
    digitalWrite(LEDBright1, HIGH);
    delay(30);
    digitalWrite(LEDBright1, LOW);
    delay(150);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void sun() {
  for (int x = 0; x < 7; x++) {
    for (int fadeValue = 5 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(LEDYellow, fadeValue);
      delay(50);
    }
    for (int fadeValue = 255 ; fadeValue >= 5; fadeValue -= 5) {
      analogWrite(LEDYellow, fadeValue);
      delay(50);
    }
  }
  analogWrite(LEDYellow, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void cloud() {
  for (int x = 0; x < 7; x++) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(LEDBlue1, fadeValue);
      analogWrite(LEDBlue2, 255 - fadeValue);
      delay(50);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(LEDBlue1, fadeValue);
      analogWrite(LEDBlue2, 255 - fadeValue);
      delay(50);
    }
  }
  analogWrite(LEDBlue1, 0);
  analogWrite(LEDBlue2, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void snow() {
  for (int x = 0; x < 7; x++) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(LEDBright1, fadeValue);
      analogWrite(LEDBright2, 255 - fadeValue);
      delay(50);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(LEDBright1, fadeValue);
      analogWrite(LEDBright2, 255 - fadeValue);
      delay(50);
    }
  }
  analogWrite(LEDBright1, 0);
  analogWrite(LEDBright2, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void fail() {
  for (int x = 0; x < 5; x++) {
    digitalWrite(LEDBright1, HIGH);
    delay(500);
    digitalWrite(LEDBright1, LOW);
    delay(500);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void night() {
  for (int x = 0; x < 4; x++) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(LEDBlue1, fadeValue);
      analogWrite(LEDBright1, fadeValue);
      analogWrite(LEDBright2, 255 - fadeValue);
      analogWrite(LEDBlue2, 255 - fadeValue);
      delay(50);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(LEDBlue1, fadeValue);
      analogWrite(LEDBright1, fadeValue);
      analogWrite(LEDBright2, 255 - fadeValue);
      analogWrite(LEDBlue2, 255 - fadeValue);
      delay(50);
    }
  }
  analogWrite(LEDBlue1, 0);
  analogWrite(LEDBlue2, 0);
  analogWrite(LEDBright1, 0);
  analogWrite(LEDBright2, 0);
}
