#ifndef _THERMO_H
#define _THERMO_H

#include <Arduino.h>
#include <math.h>
#include <avr/io.h>
#include <stdint.h>

#define CALIBRATE         0 // variable que contiene el valor de calibracion del termometro
#define X                 7 // varilble utilizada por el flitro, x=2^n - 1, 'n' cuanto mas grande
                            // mas inmune al ruido

#define Av              270 // Ganancia del AMP OP
#define Vcc             5.0 // VRef

//#define NO_BUILTIN_LP_FILTER     1

    class kThermocouple{

    public:
        kThermocouple(uint8_t pin_thermocouple);
        float    getTemp(uint16_t adc=1024);
#ifndef NO_BUILTIN_LP_FILTER
        float    getTempWithFilter();
#endif
        uint16_t tempToAdc(uint16_t temp);
        float    getCalibrate();
        void     setCalibrate(float calibrate);

    private:    
        float    _mv2temp(float mv);
        float    _adc2mv(uint16_t adc);
        
        uint8_t  _pin_thermocouple;
        uint16_t _adc;
#ifndef NO_BUILTIN_LP_FILTER
        long     _adcAnt;             // variable que contiene la muestra anterior desde _pin_thermocouple
#endif
        uint8_t  _calibrate = CALIBRATE;
    };

#endif
