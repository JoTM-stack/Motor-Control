#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 5, 4, 3, 2);

// Pin definitions
const int motorPin = 9;         
const int ledPin = 12;          
const int buttonPin = 6;        
const int potPin = A0;          
const int voltageButtonPin = 10; 

// Variables for motor control
bool motorState = false;        
int potValue = 0;               
int ledBrightness = 0;          
int motorSpeed = 0;             
int motorSpeedPercentage = 0;   
float actualVoltage = 0.0;      

bool voltageState = false;      

void setup() {
  //Setting pin modes
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Push button for motor
  pinMode(voltageButtonPin, INPUT_PULLUP); // Push button for voltage source
  
  //This will initialize the LCD
  lcd.begin(16, 2);
  lcd.print("System Ready");
  
  delay(2000);  // Wait 2 seconds before showing the next messages
  lcd.clear();
  
  //This will set the LCD to display my information
  lcd.print("By JM Tsie");
  lcd.setCursor(0, 1); // Move to the second row
  lcd.print("221134921");
  
  delay(3000);  // Display for 3 seconds
  lcd.clear();  // Clear the display for the main loop
}

void loop() {
  //The program will read the potentiometer value
  potValue = analogRead(potPin);      // Value from 0 to 1023
  
  //The program will convert potentiometer value to LED brightness and motor speed
  ledBrightness = map(potValue, 0, 1023, 0, 255);   
  motorSpeed = map(potValue, 0, 1023, 0, 255);      
  
  //Here the program will caculate the motor speed in percentage (0-100%)
  motorSpeedPercentage = map(potValue, 0, 1023, 0, 100);
  
  // This will calculate the actual voltage (0-5V)
  actualVoltage = (potValue / 1023.0) * 5.0; // Scale for voltage range
  
  //This will Read the motor button state (push-to-close)
  if (digitalRead(buttonPin) == LOW) {
    motorState = !motorState;     

    delay(200);                  
  }
  
  //This method read the voltage button state
  if (digitalRead(voltageButtonPin) == LOW) {
    voltageState = !voltageState; 
    delay(200);                   
  }

  //This method will control the motor SPEED(SPD) based on motorState
  if (motorState) {
    analogWrite(motorPin, motorSpeed); 
    lcd.setCursor(0, 0);
    lcd.print("MotorONSPD : ");
    
  } else {
    analogWrite(motorPin, 0);
    lcd.setCursor(0, 0);
    lcd.print("MotorOFFSPD: ");
  }

  //This will control the LED
  analogWrite(ledPin, ledBrightness);
  
  //This will display the motor speed in percentage on the LCD
  lcd.setCursor(13, 0);
  lcd.print(motorSpeedPercentage);
  lcd.print("%");
  
  //This will display the voltage source state on the LCD
  if (voltageState) {
    lcd.setCursor(0, 1);
    lcd.print("VOLTAGE:");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("VOLTAGE:");
  }
  
  //This will display the actual voltage value on the LCD
  lcd.setCursor(10, 1);
  lcd.print(actualVoltage, 2); 
  lcd.print(" V  ");

  delay(100);  // Short delay to smooth updates
}
