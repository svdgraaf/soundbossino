#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

// Set the host where Soundboss is running
char server[] = "192.168.1.16";
char path[] = "/";
int port = 8080;

// Set the command which is send to the server
char message[] = "{ \"action\": \"playAudio\", \"args\": { \"sound\": \"doh\", \"versions\": false } }";

// The mac adress of your Arduino network shield (or any)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x0A, 0x87 };


WebSocketClient client;
int buttonState = 0;
bool pressed = false;

int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;     // the time (msec) in which button should be depressed
const int buttonPin = 2;     // the port where the button will be HIGH

// Setup the client
void setup() {
  // Setup the serial port for easy debugging
  Serial.begin(9600);

  // Connect your network shield
  Ethernet.begin(mac);
  
  // We need to read from the button
  pinMode(buttonPin, INPUT);

  // Connecting could take some time, let's say so
  Serial.println("connecting");
  client.connect(server, path, port);

  // Set a delegate to 
  client.setDataArrivedDelegate(dataArrived);
}

// every loop, we check if the button was pressed
// because buttons have a 'floating' value when pressed
// we need to check if the button is pressed for a 
// set amount of time
void loop() {
  // read the port
  int reading = digitalRead(buttonPin);
  
  // check if the readout is different from last measurement
  // if so, set the timer to now
  if(reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }
  
  // if the button was pressed long enough, we set the 
  // actual buttonstate to the value
  if((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading; 
  }
  
  // if the button was pressed (HIGH), we send the message
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

// print the date we got back on the serial debugging port
void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
