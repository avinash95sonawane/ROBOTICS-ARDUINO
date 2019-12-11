/*copyright @ Skynet Robotics
 * no ultrasonic library needed
 */

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // use lcd address 0x27 in the place of 0x3F ,if LCD not workd
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance;
int tol=5;
int h=0;
int avgDist=0;
int avcount=0;
int Height=0;
int Sensor_h=175; //install sensor more on height than 175cm
int MinHeight=100;  //miniumum height of person for better result ,you can change it upto 30
void setup()
{    pinMode(11, OUTPUT); 
     pinMode(12, INPUT); 
     lcd.begin(16, 2);
     lcd.print("Plz Stay away");
     lcd.setCursor(0, 1);
     lcd.print("calibrating");
     delay(1000);  
    for(int i=0;i<5;i++)
    {
      h=distCal();
      if(h>=Sensor_h)
       { lcd.print(".");
         avgDist=avgDist+h;
         avcount++;}
         delay(200);
       }
      h=avgDist/avcount;
      if(h>=Sensor_h)
        {lcd.setCursor(0, 1);
         lcd.print("DONE CALIBRATION");
         lcd.setCursor(0, 0);
         lcd.print("Max Distance: ");lcd.print(h);lcd.print("cm");     
        }
    else{
         lcd.setCursor(0, 0);
         lcd.print("ERROR !!!!!!!!!");
         lcd.setCursor(0, 1);
         lcd.print("CALIBRATE AGAIN");
         delay(1000);
         setup();
         }
         }

void loop()
  {   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Plz Stand below");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Max="); lcd.print(h);
    Height=h-(distCal())+tol;
    
    if(Height>=MinHeight)
       {  
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("Your height is");
         lcd.setCursor(0, 1);
         lcd.print(Height);lcd.print(" CM");
   
       }
    
     delay(500);
  }

  int distCal()
  {
    digitalWrite(trigPin, LOW);
delayMicroseconds(7);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

return distance;}
