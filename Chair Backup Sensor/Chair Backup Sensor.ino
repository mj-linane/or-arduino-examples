/*
  CHAIR BACKUP SENSOR 
  Remixed from: Ping))) Sensor

  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
  - +V connection of the PING))) attached to +5V
  - GND connection of the PING))) attached to ground
  - SIG connection of the PING))) attached to digital pin 7

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Ping
  
*/

// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;
const int numReadings = 30;

int rangeArray[numReadings]; // the readings from the analog input
int readIndex = 0;           // the index of the current reading
int total = 0;               // the running total
int average = 0;             // the average

// Function to report range output
void indicateRange(int inches)
{

  if (inches >= 70)
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    noTone(2);
  }
  else if (inches >= 40 && inches <= 69)
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    noTone(2);
  }
  else if (inches >= 15 && inches <= 39)
  {
    tone(2, 65);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else
  {
    tone(2, 250, 50);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}

// Add to rangeArray
void addReadingToRangeArray(int reading)
{
  // Collect data in datasheet
  // subtract the last reading:
  total = total - rangeArray[readIndex];
  // read from the sensor:
  rangeArray[readIndex] = reading;
  // add the reading to the total:
  total = total + rangeArray[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings)
  {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
}

// Function to Calculate Average
int rangeArrayCalculateAverage()
{
  return total / numReadings;
}

// Function to Calculate Mode
int rangeArrayCalculateMode()
{
  int modeguess = 0; // unlikely number.
  int count = 0;
  int valmax = 0;

  for (int i = 0; i < numReadings; i++)
  {
    if (rangeArray[i] == modeguess)
    {
      count++;
    }
    Serial.print(modeguess) if (count > valmax)
    { // Check to see if there is a new max
      modeguess = rangeArray[i];
      valmax = count;
    }
  }
  return modeguess;
}

int readSensors()
{
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a inches
  int inchesRange = microsecondsToInches(duration);

  delay(1); // delay in between reads for stability
  return inchesRange;
}

// Setup the arduino
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);

  // initialize serial communication:
  Serial.begin(9600);

  // initialize all the readings to 0 for average:
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    rangeArray[thisReading] = 0;
  }
}

// Main loop
void loop()
{
  // Get data from sensors
  int range = readSensors();

  // Add to the array
  addReadingToRangeArray(range);

  // Get smoothing calculations calculation
  int mode = rangeArrayCalculateMode();
  int average = rangeArrayCalculateAverage();

  // Output to lights & tone
  // indicateRange(range);

  // Display to serial monitor
  Serial.println(mode);
  Serial.print("mode, ");
  Serial.println(average);
  Serial.print("average, ");
  Serial.print(range);
  Serial.print("in, ");
  Serial.println();
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
