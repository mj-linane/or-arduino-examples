#include <PRIZM.h> // include PRIZM library
PRIZM prizm;       // instantiate a PRIZM object “prizm” so we can use its functions

void decelerate(float currentPower, int minPower)
{
  int time = 0;
  float growthRate = 0.9;
  int motorSpeed;

  // Calculation of acceleration using doubling time
  while (currentPower != minPower)
  {
    currentPower = currentPower * pow(growthRate, time);
    if (currentPower == -1 || currentPower == 1)
    {
      currentPower = minPower;
    }
    time = time + 1;
    motorSpeed = int(currentPower);
    prizm.setMotorPowers(motorSpeed, motorSpeed); // Set motor power
    delay(100);                                   // Set delay in ms before next power increase
  };
}

void setup()
{
  prizm.PrizmBegin(); // initialize PRIZM

  prizm.setMotorInvert(1, 1); // invert the direction of DC Motor 1
  // to harmonize the direction of opposite facing drive motors
}

void loop()
{
  prizm.setMotorPowers(50, 50);
  delay(4000);
  prizm.PrizmEnd();
}