
// Attention: pin number != internal analog pin order. Cf http://digistump.com/wiki/digispark/tutorials/basics
const int analogPin = 0; //P5 !

const int ledPin = 1; // model A

const int servoPin = 0;

int soundLevel = 0;
const int nbSamples = 1;

int armLevel;

// manual servo control
void rotate(int deg)
{
   if (deg > 90) deg = 90;
   if (deg < -85) deg = -85;
   int us = 1450 + (deg * 95 / 9);
   
   for (int i = 0; i < 15; i++)
   {
    digitalWrite(servoPin,HIGH);
    delayMicroseconds(us);
    digitalWrite(servoPin,LOW);
    delayMicroseconds(5000 - us);
    delay(15);
   }
}


void blink()
{
   digitalWrite(ledPin,HIGH);
   delay(200);
   digitalWrite(ledPin,LOW);
   delay(200);
}

void move_arms(int level = 1)
{
  
  for (int i = 0; i < level + 2 ; i++)
  {
    
    //rotate(10 + level * 10);
    rotate(-20);
    delay(200);

    //rotate(-30 - level * 10);
    rotate(30);
    delay(200);
  }
}

void setup()
{
 pinMode(ledPin,OUTPUT);
 digitalWrite(ledPin,LOW);

 pinMode(servoPin,OUTPUT);
 digitalWrite(servoPin,LOW);
 
 blink(); blink(); blink(); blink(); blink(); 

 rotate(0);

}

void loop()
{

  soundLevel = 0;

  for (int i = 0 ; i < nbSamples ; i++)
  {
    soundLevel += analogRead(analogPin);
    delay(2);
  }
  soundLevel = soundLevel / nbSamples;
  
  armLevel = 1;
  if (soundLevel > 45) armLevel = 2;
  if (soundLevel > 60) armLevel = 3;  
  
  if (soundLevel > 30)
  {
    move_arms(armLevel);  
  }
  
}
