#include <PRIZM.h> // include PRIZM library
PRIZM prizm;       // instantiate a PRIZM object “prizm” so we can use its functions

void reverseAccelerate(float currentPower, int maxPower)
{
  int time = 0;
  float growthRate = 1.03;
  int motorSpeed;

  if (currentPower == 0 || currentPower == -1)
  {
    currentPower == -2;
  }
  // Calculation of acceleration using doubling time
  while (currentPower != maxPower)
  {
    currentPower = currentPower * pow(growthRate, time);
    if (currentPower < maxPower)
    {
      currentPower = maxPower;
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