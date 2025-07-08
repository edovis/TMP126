/*
  TMP126 library
  Datasheet: https://www.ti.com/lit/ds/symlink/tmp126.pdf
  NOTE: basic funtions implemented just to deal with VC2000_OCXO project and no more
  Created by LU6VED - Emmanuel M. Dovis - 2025-07-06
*/

#include "Arduino.h"
#include "TMP126.h"

TMP126::TMP126(uint8_t CS, uint8_t SI, uint8_t SO, uint8_t SCLK)
{
  _CS = CS;
  _SI = SI;
  _SO = SO;
  _SCLK = SCLK;
} // End of TMP126

/*
  Begins SPI bus
*/
void TMP126::begin(uint16_t configValue)
{
  // Pins assignations
  pinMode(_SCLK, OUTPUT);
  pinMode(_CS, OUTPUT);
  pinMode(_SI, OUTPUT);
  pinMode(_SO, INPUT);

  // Signals initial state
  digitalWrite(_CS, HIGH);
  digitalWrite(_SCLK, LOW);  // Data clocks into TMP126 on rising edge
                             // Data clocks out of TMP126 on falling edge
  
  // Writes Configuration Register
  config(configValue);
} // End of begin()

/*
  Generates a pulse clock.
*/
void TMP126::doClock(void)
{
  digitalWrite(_SCLK, HIGH);
  digitalWrite(_SCLK, LOW);
} // End of doClock()

/*
  Generates a clock rising edge.
*/
void TMP126::riseClock(void)
{
  digitalWrite(_SCLK, HIGH);
} // End of riseClock()

/*
  Generates a clock falling edge.
*/
void TMP126::fallClock(void)
{
  digitalWrite(_SCLK, LOW);
} // End of fallClock()

/*
  Starts communication
*/
void TMP126::startComm(void)
{
  digitalWrite(_CS, LOW);
} // End of startComm()

/*
  Ends communication
*/
void TMP126::endComm(void)
{
  digitalWrite(_CS, HIGH);
} // End of endComm()

/*
  Writes just one register
*/
void TMP126::write(uint8_t address, uint16_t data)
{
  /*
  Sends command word
  X = 0
  CRC = 0 -> no CRC check
  CRC data block lenght = 0
  A = 0 -> no auto increment
  R/W = 0 -> write request
  Sub-Address = address from argument
  */
  uint16_t commandWord = 0x00FF & uint16_t(address);

  // Initialize communication with TMP126
  startComm();

  // Sends command word
  for(int8_t i = 15; i >= 0; i--)
  {
    digitalWrite(_SI, (commandWord >> i) & 0x0001);
    doClock();
  }

  // Sends data word
  for(int8_t i = 15; i >= 0; i--)
  {
    digitalWrite(_SI, (data >> i) & 0x0001);
    doClock();
  }

  // Ends communication with TMP126
  endComm();

} // End of write()

/*
  Reads just one register
*/
uint16_t TMP126::read(uint8_t address)
{
  /*
  Sends command word
  X = 0
  CRC = 0 -> no CRC check
  CRC data block lenght = 0
  A = 0 -> no auto increment
  R/W = 1 -> read request
  Sub-Address = address from argument
  */
  uint16_t commandWord = 0x00FF & uint16_t(address);  
  bitSet(commandWord, 8); // Sets 8th bit for read request

  // Initialize communication with TMP126
  startComm();

  // Sends command word
  for(int8_t i = 15; i >= 0; i--)
  {
    digitalWrite(_SI, (commandWord >> i) & 0x0001);
    doClock();
  }

  // Reads register
  uint16_t data = 0x0000;
  for(uint8_t i = 0; i < 16; i++)
  {
    riseClock();    
    data <<= 1;
    data |= 0x01 & digitalRead(_SO);
    fallClock();
  }

  // Ends communication with TMP126
  endComm();

  return data;

} // End of read()

/*
  Configures TMP126
*/
void TMP126::config(uint16_t configValue)
{
  write(configuration, configValue);
} // End of config()

/*
  Gets status. 0 = ERROR; 1 = OK
*/
bool TMP126::getStatus(void)
{
  if( read(deviceID) == 0x2126 ) return 1;
  else return 0;
} // End of getStatus()

/*
  Gets temperature in Celsius
*/
float TMP126::getTemp(void)
{
  return (read(tempResult) >> 2) * 0.03125;
} // End of getTemp()

/*
  Gets Unique ID1
*/
uint16_t TMP126::getID1(void)
{
  return read(uniqueID1);
} // End of getID1()

/*
  Gets Unique ID2
*/
uint16_t TMP126::getID2(void)
{
  return read(uniqueID2);
} // End of getID2()

/*
  Gets Unique ID3
*/
uint16_t TMP126::getID3(void)
{
  return read(uniqueID3);
} // End of getID3()

/*
  Gets Devices ID
*/
uint16_t TMP126::getDevID(void)
{
  return read(deviceID);
} // End of getDevID()

/*
  Resets the device. 0 = ERROR; 1 = OK
*/
bool TMP126::reset(void)
{
  write(configuration, 0x0100);
  config(defaultConfig);
  return getStatus();
}
