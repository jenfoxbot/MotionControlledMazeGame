/*Code written by  jenfoxbot <jenfoxbot@gmail.com> 
with servo motor help from "Sweep" by BARRAGAN <http://barraganstudio.com> 
and modified by Scott Fitzgerald

* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jenfoxbot@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------

*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int signal = 9; //servo pin number

int lightPin1 = 0;  //define pin for photoresistor 1
int lightPin2 = 1; //define pin for photoresistor 2

int lightSig1;
int lightSig2;
int lightSig3;
int lightSig4;

double sigRound;
int sigSteps1;
int sigSteps2;
int sigDelay;
int lastSig;

unsigned long lastPost;

void setup() {
  Serial.begin(9600);
  myservo.attach(signal);  // attaches the servo on pin 9 to the servo object
}

void loop() {
 // digitalWrite(A0, HIGH);  // OPTIONAL: to increase photoresistor signal, set pullup on analog pin 0
  
  lightSig1 = analogRead(lightPin1);
  lightSig2 = analogRead(lightPin2);
  
  Serial.println(lightSig1);
  Serial.println(lightSig2);
  
  sigSteps1 = motorSpeed(lightSig1);
  sigSteps2 = motorSpeed(lightSig2);
  Serial.println(sigSteps1);
  Serial.println(sigSteps2);
  
  
  lastSig = moveMotor(lightSig1, sigSteps1, sigSteps2);
  Serial.println(lastSig);

  lightSig3 = analogRead(lightPin1)/100;
  lightSig4 = analogRead(lightPin2)/100;
  if(lastSig != lightSig3 && lastSig != lightSig4){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);     // tell servo to go to position in variable 'pos'
      delay(1);     // waits 1ms for the servo to reach the position
  }
    }
  

}

int motorSpeed(int signal){
  int deg;
   
  if(signal <= 400) deg = 30; //convert photoresistor signal into number of degree steps
    //larger degree steps equate to faster rotation
  else if(signal >= 401 && signal < 500) deg = 25; 
  else if(signal >= 501 && signal < 600) deg = 20; 
  else if(signal >= 601 && signal < 650) deg = 15; 
  else if(signal >= 651 && signal < 700) deg = 12; 
  else if(signal >= 701 && signal < 750) deg = 10; 
  else if(signal >= 751 && signal < 800) deg = 8; 
  else if(signal >= 801 && signal < 850) deg = 6;
  else if(signal >= 851 && signal < 900) deg = 4;
  else if(signal >= 901 && signal < 950) deg = 3;
  else if(signal >= 951 && signal < 1000) deg = 2;
  else if(signal >= 1001) deg = 1;
  else(deg = 1);

  return(deg);  
}


int moveMotor(int sig, int sigSteps1, int sigSteps2){
  double sigRound;
  double lastSig;
 
  sigRound = sig/100;
 
  for (pos = 0; pos <= 180; pos += sigSteps1) { //degree steps given by photoresistor signal (e.g. 30 = 30 degree steps)
    myservo.write(pos);     //write servo to variable position pos
    delay(10);     // waits 10ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= sigSteps2) { 
    myservo.write(pos);              
    delay(10);    // waits 10ms for the servo to reach the position
  }
  lastSig = sigRound;  

  return sigRound;  
}

