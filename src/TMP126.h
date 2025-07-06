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

class TMP126
{
  private:
    volatile uint8_t _CS;
    volatile uint8_t _SI;
    volatile uint8_t _SO;
    volatile uint8_t _SCLK;

    const uint8_t tempResult    = 0x00;
    const uint8_t slewResult    = 0x01;
    const uint8_t alertStatus   = 0x02;
    const uint8_t configuration = 0x03;
    const uint8_t alertEnable   = 0x04;
    const uint8_t tLowLimit     = 0x05;
    const uint8_t tHighLimit    = 0x06;
    const uint8_t hysteresis    = 0x07;
    const uint8_t slewLimit     = 0x08;
    const uint8_t uniqueID1     = 0x09;
    const uint8_t uniqueID2     = 0x0A;
    const uint8_t uniqueID3     = 0x0B;
    const uint8_t deviceID      = 0x0C;

    void doClock(void);
    void riseClock(void);
    void fallClock(void);
    void startComm(void);
    void endComm(void);

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


}; // End of class TMP126

#endif
