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

// Button toggle variables
bool lastButtonState = HIGH;
unsigned long lastButtonTime = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("System Starting...");
  
  //Setting pin modes
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Push button for motor
  pinMode(voltageButtonPin, INPUT_PULLUP); // Push button for voltage source
  
  //This will initialize the LCD
  lcd.begin(16, 2);
  lcd.print("System Ready");
  Serial.println("LCD initialized - System Ready");
  
  delay(2000);  // Wait 2 seconds before showing the next messages
  lcd.clear();
  
  //This will set the LCD to display my information
  lcd.print("By JM Tsie");
  lcd.setCursor(0, 1); // Move to the second row
  lcd.print(" ");
  Serial.println("My info: JM Tsie | Lets Connect: jaytm083@gmail.com ");
  
  delay(3000);  // Display for 3 seconds
  lcd.clear();  // Clear the display for the main loop
  Serial.println("Setup complete - entering main loop");
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
  
  // Simple button toggle with debouncing
  bool currentButtonState = digitalRead(buttonPin);
  
  // Check for button press (HIGH to LOW) with simple debouncing
  if (currentButtonState == LOW && lastButtonState == HIGH && (millis() - lastButtonTime) > 150) {
    motorState = !motorState;
    lastButtonTime = millis();
    Serial.print("BUTTON PRESSED! Motor state changed to: ");
    Serial.println(motorState ? "ON" : "OFF");
  }
  
  lastButtonState = currentButtonState;
  
  //This method read the voltage button state
  if (digitalRead(voltageButtonPin) == LOW) {
    voltageState = !voltageState; 
    Serial.print("Voltage button pressed - Voltage display state: ");
    Serial.println(voltageState ? "ON" : "OFF");
    delay(200);                   
  }

  //This method will control the motor SPEED(SPD) based on motorState
  lcd.setCursor(0, 0);
  if (motorState) {
    analogWrite(motorPin, motorSpeed); 
    lcd.print("MotorON SPD : ");
    Serial.print("Motor SPEED value set to: ");
    Serial.print(motorSpeedPercentage);
    Serial.println(" km/h");
    Serial.print("DEBUG: PWM output to pin 9: ");
    Serial.println(motorSpeed);
  } else {
    analogWrite(motorPin, 0);  // Simply set PWM to 0
    lcd.print("MotorOFFSPD: ");
    Serial.println("Motor SPEED value set to: 0 km/h");
    Serial.println("DEBUG: PWM output to pin 9: 0");
  }

  //This will control the LED
  analogWrite(ledPin, ledBrightness);
  
  //This will display the motor speed in percentage on the LCD
  lcd.setCursor(13, 0);
  if (motorState) {
    lcd.print(motorSpeedPercentage);
    lcd.print("%  ");
  } else {
    lcd.print("0%  ");
  }
  
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

  // Log system status to serial monitor every 1 second
  static unsigned long lastLogTime = 0;
  if (millis() - lastLogTime > 1000) {
    Serial.print("Motor: ");
    Serial.print(motorState ? "ON" : "OFF");
    Serial.print(" | Speed: ");
    Serial.print(motorState ? motorSpeedPercentage : 0);
    Serial.print("% | Voltage: ");
    Serial.print(actualVoltage, 2);
    Serial.print("V | Pot Value: ");
    Serial.print(potValue);
    Serial.print(" | Pin 9 State: ");
    Serial.println(digitalRead(motorPin));
    
    lastLogTime = millis();
  }

  delay(200);  // Short delay to smooth updates
}
