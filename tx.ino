// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module


#include<LoRa.h>
//#include <SPI.h> // Not actually used but needed to compile

#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.




void setup(){
Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);

// LoRa.setTxPower(20);
  }  
}

void loop(){


  
delay(2000);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
Serial.print("Distance is: ");
Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
Serial.println(" cm");
LoRa.beginPacket(); ///send packet
LoRa.print(sonar.ping_cm());
LoRa.endPacket();
delay(20);
}