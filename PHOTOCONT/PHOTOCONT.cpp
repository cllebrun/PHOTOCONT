#include "PHOTOCONT.h"
#include "MQTTLogging.h"
// types are defined in PHOTOCONT.h
struct __attribute__((packed)) data_str {
    WORD DAC_Value; 
    BYTE state; 
    DWORD power; 
    DWORD old_power; 
    WORD v_iphoto; 
    WORD v_vphoto; 
    short v_bat; 
    BYTE rotary_mode; 
    BYTE bNuit; 
    WORD wJourTimer; 
    WORD wNuitTimer; 
    WORD wCurrentTimer; 
}data;


PHOTOCONT::PHOTOCONT(PinName sda, PinName scl) : ph_i2c(sda, scl)
{
    ph_i2c.frequency(100000);
}



int PHOTOCONT::getTrame() {
    char cmd[2];
    cmd[0] = 0x00;

    int res_write = ph_i2c.write(PHOTOCONT_ADDRESS, cmd, 1, true);
    int res_read = ph_i2c.read(PHOTOCONT_ADDRESS, (char*)(&data), 25);
    
    DEBUG("Res_write %i, Res_read %i\n", res_write, res_read);
    DEBUG("GET TRAM :::: DAC_Value: %hu ; State: %#x ; Power: %u ; Old_Power: %u ; v_iphoto: %#hx ; v_vphoto: %#hx ; v_bat: %#hx ; Rotary_mode: %#x ; bNuit: %#x ; wJourTimer: %hu ; wNuitTimer: %hu ; wCurrentTimer: %hu \n", data.DAC_Value, data.state, data.power, data.old_power, data.v_iphoto, data.v_vphoto, data.v_bat, data.rotary_mode, data.bNuit, data.wJourTimer, data.wNuitTimer, data.wCurrentTimer);
    DEBUG("Sizeof %i\n", sizeof(data));
  
    return res_read; 
}
unsigned short PHOTOCONT::getDAC_Value( void )
{
    return data.DAC_Value;
}

char PHOTOCONT::getState( void )
{
    return data.state;
}

unsigned int PHOTOCONT::getPower( void )
{
    return data.power;
}
unsigned int PHOTOCONT::getOld_power( void )
{
    return data.old_power;
}
unsigned short PHOTOCONT::getV_iphoto( void )
{
    return data.v_iphoto;
}
unsigned short PHOTOCONT::getV_vphoto( void )
{
    return data.v_iphoto;
}
char PHOTOCONT::getRotary_mode( void )
{
    return data.rotary_mode;
}
short PHOTOCONT::getV_bat( void )
{
    return data.v_bat;
}
char PHOTOCONT::getBNuit( void )
{
    return data.bNuit;
}
unsigned int PHOTOCONT::getWJourTimer( void )
{
    return data.wJourTimer;
}
unsigned int PHOTOCONT::getWNuitTimer( void )
{
    return data.wNuitTimer;
}
unsigned int PHOTOCONT::getWCurrentTimer( void )
{
    return data.wCurrentTimer;
}


//////////////////////////////////////////////
///////////////PRIVATE////////////////////////
//////////////////////////////////////////////


void PHOTOCONT::write(char address, char data)
{
    char temp[2];
    temp[0]=address;
    temp[1]=data;

    ph_i2c.write(PHOTOCONT_ADDRESS, temp, 2);
}

char PHOTOCONT::read(char address)
{
    char retval;
    ph_i2c.write(PHOTOCONT_ADDRESS, &address, 1, true);
    ph_i2c.read(PHOTOCONT_ADDRESS, &retval, 1);
    return retval;
}

void PHOTOCONT::read(char address, char *data, int length)
{
    ph_i2c.write(PHOTOCONT_ADDRESS, &address, 1, true);
    ph_i2c.read(PHOTOCONT_ADDRESS, data, length);
}

