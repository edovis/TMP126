# TMP126
Arduino library for [Texas Instruments TMP126 Temperature Sensor](https://www.ti.com/lit/gpn/TMP126)

*NOTE: basic funtions implemented just to deal with VC2000_OCXO project and no more*

## Constructor
- **TMP126**: CS, SI (MOSI), SO (MISO) and SCLK must be declared

## List of functions
- **begin**: initializes device with default configuration, unless custom one it's passed through its argument
- **write**: writes a 16-bit word to a single register
- **read**: reads a 16-bit word from a single register
- **config**: writes a custom 16-bit configuration word to Configuration Register
- **getStatus**: returns bool '0' if device does not respond or '1' if it does
- **getTemp**: returns temperature (float) in Celsius
- **getID1**: returns 16-bit Unique ID1 value
- **getID2**: returns 16-bit Unique ID2 value
- **getID3**: returns 16-bit Unique ID3 value
- **getDevID**: returns 16-bit Device ID
- **reset**: resets device anr return bool '0' if device does not respond or '1' if it does
