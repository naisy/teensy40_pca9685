//i2c library: https://github.com/Richard-Gemmell/teensy4_i2c
//install library: copy teensy4_i2c directory into your arudino libraries
//remove arduino1.8.1/library/Servo for use arduino-1.8.11/hardware/teensy/avr/libraries/Servo
#include <Arduino.h>
#include <Servo.h>
#include "PCA9685Emulator.h"
#include "TeensyThreads.h"

/*
 * Teensy 4.0 PINs
 * PIN 18: SDA connect to Jetson Nano PIN 3
 * PIN 19: SCL connect to Jetson Nano PIN 5
 * PIN GND: GND connect to Jetson Nano PIN GND
 * PIN 16: PWM CH1 OUTPUT
 * PIN 15: PWM CH2 OUTPUT
 */
const int PCA9685_I2C_ADDRESS = 0x40;
const int PWM_OUT_PIN = {16, 15};
const int OUTPUT_CH1 = 0; // array index of PWM_OUTPUT_PIN
const int OUTPUT_CH2 = 1; // array index of PWM_OUTPUT_PIN


PCA9685Emulator pwmEmulation;
Servo svoSteer;
Servo svoThrottle;

void setup()
{
  // PCA9685 Emulator
  pinMode(PWM_OUTPUT_PIN[OUTPUT_CH1] OUTPUT);
  pinMode(PWM_OUTPUT_PIN[OUTPUT_CH2], OUTPUT);
  svoSteer.attach(PWM_OUTPUT_PIN[OUTPUT_CH1]);
  svoThrottle.attach(PWM_OUTPUT_PIN[OUTPUT_CH2]);
  pwmEmulation.begin(PCA9685_I2C_ADDRESS);
}

void loop()
{
  // Output
  pwmEmulation.step(millis());
  svoSteer.writeMicroseconds(pwmEmulation.readChannelUs(OUTPUT_CH1));
  svoThrottle.writeMicroseconds(pwmEmulation.readChannelUs(OUTPUT_CH2));
}
