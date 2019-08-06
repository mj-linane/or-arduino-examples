// Open up the Arduino environment. Then copy and paste it into a new sketch.
// Then upload the code to the Arduino board.

#include <Arduino.h>
#include <Servo.h>
Servo myservo;                                         //create servo object to control a servo

int ResetTimer=0;                                      //sets delay to reset position
int GoalPosition=2;                                    //stores the goal postion (1-3) where the person is standing
int GoalPositionDegrees;                               //stores the goal position in degrees (30-150)
int CurrentPositionDegrees=90;                         //stores the current position in degrees (30-150)
int AveragingSpeed=100;                                //sets how quickly the average values adjust (a lower value changes average value quickly)                                                                           //quickly. A value of 100 changes the average value slowly
                                                       // his effectively sets the speed at which the sensors recalibrate themselves to changing light conditions
int PinOneCurrent;                                     //stores current value of pins 1-3
int PinTwoCurrent;
int PinThreeCurrent;


float PinOneAverage;                                    //stores the average value of pins 1-5
float PinTwoAverage;
float PinThreeAverage;

float RatioPinOne=0.00;                                 //stores the ratio of current pin value to average pin value
float RatioPinTwo=0.00;
float RatioPinThree=0.00;


float Threshold=.95;                                    //sets minimum threshold for sensors

void setup()
{
myservo.attach(13);                                      //attaches servo to digital pin 13


PinOneAverage = analogRead(1);                           //reads from sensors to set initial average pin value
PinTwoAverage = analogRead(2);
PinThreeAverage = analogRead(3);
}




void loop()
{
                                                                                    //read analog pins 1-3 and set the result as current value  
   PinOneCurrent= analogRead(1);                                               
   PinTwoCurrent= analogRead(2); 
   PinThreeCurrent= analogRead(3);

                                                                                    //adjust average pin values
   PinOneAverage=PinOneAverage+(PinOneCurrent-PinOneAverage)/AveragingSpeed;
   PinTwoAverage=PinTwoAverage+(PinTwoCurrent-PinTwoAverage)/AveragingSpeed;
   PinThreeAverage=PinThreeAverage+(PinThreeCurrent-PinThreeAverage)/AveragingSpeed;
  

                                                                                    //calculates ratio of current pin value to average pin value
   RatioPinOne=(float)PinOneCurrent/PinOneAverage;
   RatioPinTwo=(float)PinTwoCurrent/PinTwoAverage;
   RatioPinThree=(float)PinThreeCurrent/PinThreeAverage;


                                                                                 //determine which ratio is the largest and sets the goal position
                                                                                 //set goal position

   if (RatioPinThree < Threshold && RatioPinThree < RatioPinOne && RatioPinThree < RatioPinTwo && RatioPinThree)
    {    GoalPosition=3;     
         ResetTimer=0;   }
   else if (RatioPinOne < Threshold && RatioPinOne < RatioPinTwo && RatioPinOne < RatioPinThree && RatioPinOne)
    {    GoalPosition=1;     
         ResetTimer=0;   }
   else if (RatioPinTwo < Threshold && RatioPinTwo < RatioPinOne && RatioPinTwo < RatioPinThree && RatioPinTwo)
    {    GoalPosition=2;     
         ResetTimer=0;   }
   else if (ResetTimer > 100)                                     //after delay resets to position 2
    {    GoalPosition=2;  
         ResetTimer=0;   }
   else
    {    ResetTimer=ResetTimer+1;  }


GoalPositionDegrees=GoalPosition*25+15;                               //converts the goal position to degrees
         
myservo.write(GoalPositionDegrees);                             //sets the servo position according to the scaled value

delay(30);                                                         //sets how quckly the servo turns (lower numbers turn more quickly)
                                 

}