//
//  Honey_Bottling_Machine.ino
//  Description: Complete code for Liquid Gold Rush, an automatic honey bottling
//               machine for Urban Toronto Beekeepers
//  Created by Maliha Islam on 2016-04-04.
//

#include <Servo.h>

Servo servo1;
int pos = 50;

int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int forceInit;
int forceCurr;
int forceDiff;

const int pushLowPin = 6;   // choose the input pin (for a pushbutton)
const int pushMedPin = 7;
const int pushHighPin = 8;
const int pushCustPin = 5;
int pushLowState = 0;     // variable for reading the pin status
int pushMedState = 0;
int pushHighState = 0;
int pushCustState = 0;


void setup(void) {
  Serial.begin(9600);
  servo1.attach(9);  // pin the servo is connected to  
  pinMode(pushLowPin, INPUT);
  pinMode(pushMedPin, INPUT);
  pinMode(pushHighPin, INPUT);
  pinMode(pushCustPin, INPUT); 
}
 
void loop(void) {
  pushLowState = digitalRead(pushLowPin); //read the state of the pushbutton value
  pushMedState = digitalRead(pushMedPin);
  pushHighState = digitalRead(pushHighPin);
  pushCustState = digitalRead(pushCustPin);
  fsrReading = analogRead(fsrPin);  
  
  Serial.print("Analog reading  = ");
  Serial.println(fsrReading); 
 delay(1000);
    
  if (pushLowState == HIGH){ //if button is pressed (HIGH)
    forceInit = analogRead(fsrPin);
    servo1.write(20); //open valve
    forceCurr = analogRead(fsrPin);
    forceDiff = forceCurr - forceInit;
    while (forceDiff < 100){
      Serial.print("Analog reading  = ");
      Serial.println(analogRead(fsrPin));
      delay(1000);
      forceCurr = analogRead(fsrPin);
      forceDiff = forceCurr - forceInit; 
    }
    Serial.print("Analog reading (difference) = ");
    Serial.println(forceDiff);     // the raw analog reading
    delay(1000);
    servo1.write(180);
    Serial.println("150g of honey bottled");
  }
  
  else if (pushMedState == HIGH){
    forceInit = analogRead(fsrPin);
    servo1.write(20); //open valve
    forceCurr = analogRead(fsrPin);
    forceDiff = forceCurr - forceInit;
    while (forceDiff < 50){
      Serial.print("Analog reading  = ");
      Serial.println(analogRead(fsrPin));
      delay(1000);
      forceCurr = analogRead(fsrPin);
      forceDiff = forceCurr - forceInit; 
    } 
    Serial.print("Analog reading (difference) = ");
    Serial.println(forceDiff);     // the raw analog reading
    delay(1000);
    servo1.write(180);
    Serial.println("250g of honey bottled");
  }
  
  else if (pushHighState == HIGH){
    forceInit = analogRead(fsrPin);
    servo1.write(20); //open valve
    forceCurr = analogRead(fsrPin);
    forceDiff = forceCurr - forceInit;
    Serial.print("Analog reading  = ");
    Serial.println(analogRead(fsrPin)); 
    while (forceDiff < 500){
      Serial.print("Analog reading  = ");
      Serial.println(analogRead(fsrPin));
      delay(1000);
      forceCurr = analogRead(fsrPin);
      forceDiff = forceCurr - forceInit; 
    }
    Serial.print("Analog reading (difference) = ");
    Serial.println(forceDiff);     // the raw analog reading
    delay(1000);
    servo1.write(180);
    Serial.println("500g of honey bottled");
  }
  
  if (pushCustState == HIGH){
    forceInit = analogRead(fsrPin);
    servo1.write(20); //open valve
    pushCustState = digitalRead(pushCustPin);
    while (pushCustState == HIGH){
      pushCustState = digitalRead(pushCustPin);
      forceCurr = analogRead(fsrPin);
      forceDiff = forceCurr-forceInit;
    }
    Serial.print("Analog reading (difference) = ");
    Serial.println(forceDiff);     // the raw analog reading
    delay(1000);
    servo1.write(180);
    Serial.println("Desired amount of honey bottled");
  }
  
} 
