// Remixed from: https://create.arduino.cc/projecthub/DCamino

int sensor = A0;
int output = 9;

void setup()
{
  pinMode(output, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  // Take main reading
  int reading = analogRead(sensor);
  // If it is bright
  if (reading > 450)
  {
    Serial.println("It is very bright!");
    Serial.println(reading);
    digitalWrite(output, LOW); //turn left LED off
  }
  // If it is average light
  else if (reading > 229 && reading < 451)
  {
    Serial.println("It is average light!");
    Serial.println(reading);
    digitalWrite(output, HIGH); // turn left LED on
  }
  // If it's dark
  else
  {
    Serial.println("It is pretty dark!");
    digitalWrite(output, HIGH); // Turn left LED on
  }
  delay(1000); // Wait
}
