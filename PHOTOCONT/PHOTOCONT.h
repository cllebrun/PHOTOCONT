/* Copyright (c) <year> <copyright holders>, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"


#ifndef PHOTOCONT_H
#define PHOTOCONT_H

#define PHOTOCONT_ADDRESS     0x10

// 
typedef char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;



/** An interface for the PHOTOCONT 
 *
 * @code
 * //Uses the measured z-acceleration to drive leds 2 and 3 of the mbed
 *
 * #include "mbed.h"
 * #include "PHOTOCONT.h"
 *
 * PHOTOCONT MMA(p28, p27);
 *
 * DigitalOut connectionLed(LED1);
 * PwmOut Zaxis_p(LED2);
 * PwmOut Zaxis_n(LED3);
 *
 * int main() {
 *     if (MMA.testConnection())
 *         connectionLed = 1;
 *
 *     while(1) {
 *         Zaxis_p = MMA.z();
 *         Zaxis_n = -MMA.z();
 *     }
 *
 * }
 * @endcode
 */
class PHOTOCONT
{
public:
    
    
    /**
    * Creates a new PHOTOCONT object
    *
    * @param sda - I2C data pin
    * @param scl - I2C clock pin
    * @param active - true (default) to enable the device, false to keep it standby
    */
    PHOTOCONT(PinName sda, PinName scl);

    /**
    * Tests if communication is possible with the PHOTOCONT
    *
    * Because the PHOTOCONT lacks a WHO_AM_I register, this function can only check
    * if there is an I2C device that responds to the PHOTOCONT address
    *
    * @param return - true for successfull connection, false for no connection
    */

    int getTrame();
    char getBNuit( void );

    unsigned int getWJourTimer( void );

    unsigned int getWNuitTimer( void );

    unsigned int getWCurrentTimer( void );
    unsigned short getV_iphoto( void );

    unsigned short getV_vphoto( void );

    char getRotary_mode( void );

    short getV_bat( void );
    unsigned short getDAC_Value( void );

    char getState( void );

    unsigned int getPower( void );

    unsigned int getOld_power( void );


    /**
    * Sets the active state of the PHOTOCONT
    *
    * Note: This is unrelated to awake/sleep mode
    *
    * @param state - true for active, false for standby
    */
    //void setActive( bool state);

    /**
    * Reads acceleration data from the sensor
    *
    * When the parameter is a pointer to an integer array it will be the raw data.
    * When it is a pointer to a float array it will be the acceleration in g's
    *
    * @param data - pointer to array with length 3 where the acceleration data will be stored, X-Y-Z
    */
    //void readData( int *data);
    //void readData( float *data);



private:

    /**
    * Writes data to the device
    *
    * @param adress - register address to write to
    * @param data - data to write
    */
    void write( char address, char data);

    /**
    * Read data from the device
    *
    * @param adress - register address to write to
    * @return - data from the register specified by RA
    */
    char read( char adress);

    /**
     * Read multiple regigsters from the device, more efficient than using multiple normal reads.
     *
     * @param adress - register address to write to
     * @param length - number of bytes to read
     * @param data - pointer where the data needs to be written to
     */
    void read( char adress, char *data, int length);


    I2C ph_i2c;
    bool active;
    float samplerate;
};


#endif
