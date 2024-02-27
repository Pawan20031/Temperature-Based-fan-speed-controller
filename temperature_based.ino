const int fanPin = 9;
const int tempPin = A0;
float w0 = 0.87390129;
float w1 = 1.99226074;
void setup()
{
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);  
  while (!Serial);     
}
int calculateFanSpeed(float temperature, float w0, float w1)
{
  int fanSpeed = constrain(int(w0 + w1 * temperature), 0, 255);
  
  return fanSpeed;
}
void loop()
{
  int reading = analogRead(tempPin);
  float voltage = reading *(5.0/1024.0);
  float temp = (voltage-0.5)*100;
  
  // Use linear regression coefficients to determine fan speed
  int fanSpeed = calculateFanSpeed(temp, w0, w1);
  
  Serial.println("------------------------------------------------");
  Serial.println("               Temperature Control System");
  Serial.println("------------------------------------------------");
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.write(0xB0);  
  Serial.println("C");
  Serial.print("Estimated Fan Speed: ");
  Serial.println(fanSpeed);

  analogWrite(fanPin, fanSpeed);

  delay(1000);
  
}