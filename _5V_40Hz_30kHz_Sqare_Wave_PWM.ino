/*
This is a tiny 5V 20mA square wave generator and PWM duty cycle. 
It is a convienient tool for testing stuff that needs more chooch factor than mobile phone wave generators can provide.
Copyleft AvE 2016. Use, abuse and correct as you see fit.
Tested and working on digispark 16.5MHz using Arduino IDE and micronucleus bootloader.
USB 2.0 only, does NOT work on USB 3.0
 */

int sensorPin = A1;  //Pin "P2" on digispark board
int squarepulsePin = 0;   // Pin "P0" on digispark board
int pwmPin = 1; // Pin "P1" on digispark board select the pin for the LED
int sensorValue = 1; // variable to store the value of the 0-5V analog potentiometer input
int pwmValue = 0; // variable to store the value of the PWM duty cycle. Set to 0 initially
int delayValue = 1; // variable to store the 50% duty cycle square wave pulse on/off time. Set to 1 initially
int elapsed = 0; // variable to store the elapsed time in micro seconds so we don't slow down the works. Set to 0 initially

void setup() {
  // define I/O of each pin used
  pinMode(sensorPin, INPUT);
  pinMode(squarepulsePin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
    if (elapsed > 10000) // Only do this part after 10 ish milliseconds has elapsed
    {
        elapsed = 0; // resets the elapsed time to zero
        sensorValue = analogRead(sensorPin); // reads the analog value of pot and converts it to a value between 0 at 0 volts and 1024 at 5 volts
        pwmValue = map(sensorValue, 0, 1024, 0, 255); // asigns a value to pwm by converting the 0-1024 value above to 0-255 that the pwmPin uses to determine duty cycle 0 = 0%; 255 = 100
        delayValue = map(sensorValue, 0, 1024, 10, 10000); // asigns a value to the delay by converting the 0-1024 sensorValue to 10-10000 which gives us a output frequency of 30kHz to 40Hz
        analogWrite (pwmPin, pwmValue); // this sets the duty cycle of the pwm pin to whatever the pot is set to between 0 and 100 percent
    }

    digitalWrite(squarepulsePin, HIGH); // this is the on pulse
    delayMicroseconds(delayValue); // this is how long the on pulse is active in microseconds (0.001 milliseconds)
    digitalWrite(squarepulsePin, LOW); // this turns the pulse off
    delayMicroseconds(delayValue); // this is how long the pulse remains off
    elapsed += 2 * delayValue; // this adds the time spent doing on/off to the elapsed time. 
}
