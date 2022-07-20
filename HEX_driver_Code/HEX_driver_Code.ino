#include <LiquidCrystal.h>

LiquidCrystal lcd (13, 12, 11, 10, 9, 8);

//PWM
int led1 = 2; // Pulse 1
int led2 = 3; // Pulse 2
int led3 = 4; // Pulse 3
int led4 = 5; // Pulse 4
int led5 = 6; // Pulse 5
int led6 = 7; // Pulse 6

//Status
int LED = 1; // State of Drive

//Analogs Inputs
int S_F = A0; // set RPM by frequency
int R = A1; // run button
int S = A2; // stop button
int speedm; // speed variable
float f = 0;
float val = 0;
float numb = 0;
int ke=1000; //Motor speed constant
int power;
int Rs; //Resistance
int analogPin = A8; // Current sensor output
int potValue;  // value from the analog pin
const int averageValue = 500;
long int sensorValue = 0;  // variable to store the sensor value read

float voltage_sense = 0; //value by current sensor
float current = 0;  //variable for current
float vt; // terminal voltage variable
float x=0;  //general variable
void setup()
{
  // initialize the digital pin as an output:
  pinMode(LED, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  // initialize the analog pin as an inputs:
  pinMode(R, INPUT);
  pinMode(S, INPUT);
  lcd.begin(20, 4);
  lcd.clear();
  digitalWrite(LED, LOW);

  update_Freq();
}


void run_forward()
{
  while (1)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(val);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(val);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
    delay(val);

    if ((digitalRead(R) == HIGH) && (digitalRead(S) == LOW))
    {
      stop_Drive();
      break;
    }
    
    update_Freq();
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(val);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(val);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, HIGH);
    delay(val);
  }
}


void loop() {
  vt=analogRead(A4);
  potValue = analogRead(A3);// reads the value of the potentiometer (value between 0 and 1023)
  x=potValue*(7.5/1023);
  vt=vt*(x/1023);
  for (int i = 0; i < averageValue; i++)
  {
    sensorValue += analogRead(analogPin);

    // wait 2 milliseconds before the next loop
    delay(2);
  }

  sensorValue = sensorValue / averageValue;
  voltage_sense = sensorValue * 5.0 / 1024.0;
  current = ( voltage_sense - 2.5 ) / 0.185;
  if ((digitalRead(R) == LOW) && (digitalRead(S) == HIGH) && f != 0)
  {
    digitalWrite(LED, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BLDC Speed Control");
    lcd.setCursor(0, 1);
    lcd.print("f (Hz) :");
    lcd.setCursor(0, 2);
    lcd.print("delay (ms) :");
    lcd.setCursor(0, 3);
    lcd.print("Running ~");
    run_forward();
  }
    lcd.setCursor(0, 0);
  lcd.print("BLDC Speed Control");
  lcd.setCursor(0, 1);
  lcd.print("f (Hz) :");
  lcd.setCursor(0, 2);
  lcd.print("delay (ms) :");
  lcd.setCursor(0, 3);
  lcd.print("Press RUN Key");
  update_Freq();
  speedm=ke*vt;
  power=vt*current;
  R=vt/current;
  lcd.setCursor(0,0);
  lcd.setCursor(8,1);
  lcd.print(current);
  lcd.print("A");
  delay(100);
  lcd.setCursor(0,0);
  lcd.print(vt);
  lcd.print("V");
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("power");
  lcd.print(power);
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("Resistance");
  lcd.print(Rs);
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("speed");
  lcd.print(speedm);
  delay(100);
  
  
}

void stop_Drive() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode: STOP");
  lcd.setCursor(0, 1);
  lcd.print("f (Hz) :");
  f = 0;
  lcd.print(f);
  val = 1000 / (f * 8);
  lcd.setCursor(0, 2);
  lcd.print("delay (ms) :");
  lcd.print(val);
  digitalWrite(LED, LOW);
  delay(1000);
}

void update_Freq() {
  int sensorValue = analogRead(S_F);
  f = sensorValue * (50.0 / 1023.0);
  val = 1000 / (f * 8);
  lcd.setCursor(8, 1);
  lcd.print(f);
  lcd.setCursor(12, 2);
  lcd.print(val);
}
