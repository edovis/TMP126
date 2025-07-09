/*
 *  Example for TMP126 library
 *  Author: Emmanuel M. Dovis
 *  2025-08-07
 */

#include "TMP126.h"

#define SCLK  9
#define CS    10
#define SI    11
#define SO    12

TMP126 myTMP(CS, SI, SO, SCLK);

void setup() {

  // Initialize sensor
  myTMP.begin();

  // Initialize serial communication at 921600 bits per second:
  Serial.begin(921600);

} // End of setup()

void loop() {

  Serial.print("Temperature: ");
  // Reads temperature from sensor
  Serial.print(myTMP.getTemp(), 1);
  Serial.println(" ºC");
  
  delay(100);
}
