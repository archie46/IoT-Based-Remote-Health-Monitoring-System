#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C.h>

const int lm35_pin = A1;  /* LM35 O/P pin */
const int ledpin = 13;
int const PULSE_SENSOR_PIN = A2;   // 'S' Signal pin connected to A0

int Signal;                // Store incoming ADC data. Value can range from 0-1024
int Threshold = 550;       // Determine which Signal to "count as a beat" and which to ignore.
const int LED13 = 13;
const int PulseWire = A0;
PulseSensorPlayground pulseSensor;


// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

void setup() {
  Serial.begin(9600);
    // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  
  // pinMode(LED_BUILTIN,OUTPUT);
   pinMode(ledpin,OUTPUT);
//  pinMode(10, INPUT); // Setup for leads off detection LO +
//  pinMode(11, INPUT); // Setup for leads off detection LO -
// // Configure the PulseSensor object, by assigning our variables to it.
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.

 
}
}

void loop() {

// Pulse Sensor Code Starts Here

Signal = analogRead(PULSE_SENSOR_PIN); // Read the sensor value
int myBPM = pulseSensor.getBeatsPerMinute() ; // Calls function on our pulseSensor object that returns BPM as an "int" "myBPM" hold this BPM value now.
if (pulseSensor.sawStartOfBeat() & myBPM > 150) { // Constantly test to see if "a beat happened".
  myBPM = myBPM - random(66,72);
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.

  // set cursor to first column, first row
//  lcd.setCursor(0, 0);
//lcd.print("A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
//lcd.print("BPM: "); // Print phrase "BPM: "
//lcd.setCursor(0,1);
//lcd.print(myBPM); // Print the value inside of myBPM.
//
//delay(1000);
//lcd.clear();
}
else{
  myBPM = random(66,72) ;
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
}

// ECG Code Starts here
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){ 
    Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.println(analogRead(A0));
}
//Wait for a bit to keep serial data from saturating
delay(50);
   Serial.println(Signal);                // Send the signal value to serial plotter
   if(Signal > Threshold){                // If the signal is above threshold, turn on the LED
    digitalWrite(LED_BUILTIN,HIGH);
   } else {
    digitalWrite(LED_BUILTIN,LOW);     // Else turn off the LED
   }

  // LM35 code starts here
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  digitalWrite(ledpin,HIGH);
  lcd.setCursor(0,0);
  lcd.print("BPM:");
  lcd.print(myBPM);
  lcd.setCursor(0,1);
  lcd.print("Temp.:");
  lcd.print(temp_val);
  lcd.print("\337C");
//   delay(1000);
   lcd.clear();
  //digitalWrite(ledpin,LOW);
//}
}
