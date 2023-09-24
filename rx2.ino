#include<LoRa.h>
#include <SPI.h> // Not actually used but needed to compile
#include<string.h>
#include <Servo.h>

int disas,Q,QUO,FIN,R,REM,LIN;
Servo myservo;
float motor_angle;


void setup() {
  
Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
   //  LoRa.setTxPower(20);

}
myservo.attach(4); 
  
}


void loop() 
{
   // attaches the servo on pin 9 to the servo object
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize==1) 
  {
    // received a packet
    Serial.print("distance is ");

    // read packet
    while (LoRa.available()) 
    {
       disas=LoRa.read()-48; 
       Serial.print(disas) ;
       
     }

 
 Serial.print(" cm ");
 Serial.println(" ");

 float inputLow = 1 - (disas - 0) / (10 - 0);
  float inputMedium = max(0, min((disas - 11) / (20 - 11), (30 - disas) / (30 - 20)));
  float inputHigh = (disas - 21) / (30 - 21);

  float outputSlow = max(0, min(inputLow, 1));
  float outputMedium = max(0, min(inputMedium, 1));
  float outputFast = max(0, min(inputHigh, 1));

  float numerator = outputSlow * 25 + outputMedium * 75 + outputFast * 100;
  float denominator = outputSlow + outputMedium + outputFast;

  if (denominator > 0) {
    motor_angle = numerator / denominator;
  }
  
  myservo.write(motor_angle); // output motor angle
  delay(50);

  }
  else if (packetSize==2) 
  {
    // received a packet
    Serial.print("distance is ");

    // read packet
    while (LoRa.available()) 
    {
      FIN=LoRa.read(); 
      LIN=LoRa.read();
      //Serial.print(FIN) ;
      //Serial.print(LIN) ;
      //QUO=disas/100;
      Q=FIN-48;
      //REM=disas%100;
      R=LIN-48;
      disas=(10*Q)+R;
      Serial.print(disas) ;

     }
     float inputLow = 1 - (disas - 0) / (10 - 0);
  float inputMedium = max(0, min((disas - 11) / (20 - 11), (30 - disas) / (30 - 20)));
  float inputHigh = (disas - 21) / (30 - 21);

  float outputSlow = max(0, min(inputLow, 1));
  float outputMedium = max(0, min(inputMedium, 1));
  float outputFast = max(0, min(inputHigh, 1));

  float numerator = outputSlow * 25 + outputMedium * 75 + outputFast * 100;
  float denominator = outputSlow + outputMedium + outputFast;

  if (denominator > 0) {
    motor_angle = numerator / denominator;
  }
  
  myservo.write(motor_angle); // output motor angle
  delay(50);
  }
}