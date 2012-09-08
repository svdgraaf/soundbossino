#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

char server[] = "192.168.1.16";
char path[] = "/";
int port = 8080;
char message[] = "{ \"action\": \"playAudio\", \"args\": { \"sound\": \"doh\", \"versions\": false } }";
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x0A, 0x87 };


WebSocketClient client;
int buttonState = 0;
bool pressed = false;


int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  Serial.println(Ethernet.begin(mac));
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT); 
  Serial.println("connecting");
  client.connect(server, path, port);
  client.setDataArrivedDelegate(dataArrived);
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if(reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }
  
  if((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading; 
  }
  
  if (buttonState == HIGH && pressed == false) {
    Serial.println("Pressed!");
    pressed = true;
    client.send(message);
    digitalWrite(ledPin, HIGH);
  }
  if(buttonState == LOW && pressed == true) {
    Serial.println("loose");
    digitalWrite(ledPin, LOW);  
    pressed = false; 
  }
  
  lastButtonState = reading;
  
  client.monitor();
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
