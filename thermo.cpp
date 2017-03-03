#include "thermo.h"


kThermocouple::kThermocouple(uint8_t pin_thermocouple)
{
    _pin_thermocouple = pin_thermocouple;    
    pinMode(_pin_thermocouple, INPUT);
    _calibrate= CALIBRATE;
    
    // ELiminar lecturas y fluctuaciones iniciales
    for(int i=0; i<100; i++){
        _adc = (uint16_t)analogRead(_pin_thermocouple);
        _adc = (float)((X*_adcAnt + _adc)/(X+1));
        _adcAnt = _adc;
    }
}

float kThermocouple::_mv2temp(float mv)
{
    double c[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};             // Coefficients Thermocouples
    uint8_t lenC;
    uint8_t i;
    float temp;

    if (mv >= -5.891 && mv <= 0)
    {
        c[0]= 0;
        c[1]= 25.173462;
        c[2]= -1.1662878;
        c[3]= -1.0833638;
        c[4]= -0.8977354;
        c[5]= -0.37342377;
        c[6]= -0.086632643;
        c[7]= -0.010450598;
        c[8]= -0.00051920577;
        c[9]= 0;
        lenC = 10;
    }

    else if (mv > 0 && mv <= 20.644)
    {
        c[0]= 0;
        c[1]= 25.08355;
        c[2]= 0.07860106;
        c[3]= -0.2503131;
        c[4]= 0.0831527;
        c[5]= -0.01228034;
        c[6]= 0.0009804036;
        c[7]= -0.0000441303;
        c[8]= 0.000001057734;
        c[9]= -0.00000001052755;
        lenC = 10;
    }

    else if (mv > 20.644 && mv <= 54.886)
    {
        c[0]= -131.8058;
        c[1]= 48.30222;
        c[2]= -1.646031;
        c[3]= 0.05464731;
        c[4]= -0.0009650715;
        c[5]= 0.000008802193;
        c[6]= -0.0000000311081;
        lenC = 7;
    }
    else
    {
        lenC = 0;
    }
    // ------------------------------------------
    //  Calculs
    // ------------------------------------------
    if (lenC > 0)
    {
        for(i=0, temp=0; i<lenC; i++)
        {
            temp = (float)(temp + c[i] * pow(mv,i));
        }
    }
    else
        temp = 0;

    return temp;
}

float kThermocouple::_adc2mv(uint16_t adc)
{
    double Vout, Vin;
    Vout = (float)((Vcc/1024)*adc);
    Vin = (float)((Vout/Av)*1000);
    
    return (float)Vin;
}
float kThermocouple::getTempDirect()
{
    float vin, temp;
    _adc = (uint16_t)analogRead(_pin_thermocouple);

    vin = _adc2mv(_adc);
    temp = _mv2temp(vin) - _calibrate;
    if(temp>=0) // Solo para temp > 0ºC
      return temp;
    else
      return 0;
}

float kThermocouple::getTempWithFilter()
{
    float vin, temp;
    _adc = (uint16_t)analogRead(_pin_thermocouple);
    
    _adc = (float)((X*_adcAnt + _adc)/(X+1)); // Filtro digital pasa bajos
    _adcAnt = _adc;
    vin = _adc2mv(_adc);
    temp = _mv2temp(vin) - _calibrate;
    if(temp>=0) // Solo para temp > 0ºC
      return temp;
    else
      return 0;
}
float kThermocouple::getCalibrate()
{
    return _calibrate;
}

void kThermocouple::setCalibrate(float calibrate)
{
    _calibrate= calibrate;
}
