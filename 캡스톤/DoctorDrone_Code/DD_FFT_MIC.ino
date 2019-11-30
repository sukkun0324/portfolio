int BUZZER = 2;
const int SOUND_SENSOR_PIN = A0;
int sensorValue;
int del = 1000;

void setup()
{                
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(SOUND_SENSOR_PIN, INPUT);
}


void loop() 
{
  sensorValue = 0;
  sensorValue =  analogRead(SOUND_SENSOR_PIN);
  tone(BUZZER,1900);
  if(sensorValue >71){
  //digitalWrite(BUZZER, HIGH); 
  tone(BUZZER,2400);
  Serial.println(sensorValue);
  delay(500);
  sensorValue =0;

  noTone(BUZZER);
  }
  delay(1);
}
