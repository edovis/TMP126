/*
  TMP126 library
  Datasheet: https://www.ti.com/lit/ds/symlink/tmp126.pdf
  NOTE: basic funtions implemented just to deal with VC2000_OCXO project and no more
  Created by LU6VED - Emmanuel M. Dovis - 2025-07-06
*/

#ifndef TMP126_h
#define TMP126_h

#include "Arduino.h"

#define defaultConfig 0x0081 // AVG on, 32 SPS

#define tempResult    0x00
#define slewResult    0x01
#define alertStatus   0x02
#define configuration 0x03
#define alertEnable   0x04
#define tLowLimit     0x05
#define tHighLimit    0x06
#define hysteresis    0x07
#define slewLimit     0x08
#define uniqueID1     0x09
#define uniqueID2     0x0A
#define uniqueID3     0x0B
#define deviceID      0x0C

class TMP126
{
  public:
    TMP126(uint8_t CS, uint8_t SI, uint8_t SO, uint8_t SCLK);
    void begin(uint16_t configValue = defaultConfig);
    void write(uint8_t address, uint16_t data);
    uint16_t read(uint8_t address);
    void config(uint16_t configValue);
    bool getStatus(void);
    float getTemp(void);
    uint16_t getID1(void);
    uint16_t getID2(void);
    uint16_t getID3(void);
    uint16_t getDevID(void);
    bool reset(void);

  private:
    volatile uint8_t _CS;
    volatile uint8_t _SI;
    volatile uint8_t _SO;
    volatile uint8_t _SCLK;

    void doClock(void);
    void riseClock(void);
    void fallClock(void);
    void startComm(void);
    void endComm(void);

}; // End of class TMP126

#endif
