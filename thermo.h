#ifndef _THERMO_H
#define _THERMO_H

#include <stdint.h>
#include <math.h>
#include <Arduino.h>
#include <avr/io.h>

#define CALIBRATE         0 // variable que contiene el valor de calibracion del termometro
#define X                31 // varilble utilizada por el flitro, x=2^n - 1, 'n' cuanto mas grande
                            // mas inmune al ruido

#define Av              270 // Ganancia del AMP OP
#define Vcc             5.0 // VRef

    class kThermocouple{

    public:
        kThermocouple(uint8_t pin_thermocouple);
        float getTempDirect();
        float getTempWithFilter();
        float getCalibrate();
        void  setCalibrate(float calibrate);

        
    private:    
        float _mv2temp(float mv);
        float _adc2mv(uint16_t adc);
        
        uint8_t _pin_thermocouple;
        float  _adc;
        float _adcAnt = 45;             // variable que contiene la muestra anterior desde _pin_thermocouple        
        uint8_t _calibrate = CALIBRATE;
    };

#endif
