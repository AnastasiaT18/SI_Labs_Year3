#include "NTCSensor.h"
#include <math.h>

#define NTC_BETA      3950.0
#define NTC_R0        10000.0   // resistance at 25°C
#define NTC_T0        298.15    // 25°C in Kelvin
#define NTC_R_FIXED   10000.0   //  fixed resistor in voltage divider
#define ADC_MAX       1023.0

NTCSensor::NTCSensor(int pin) : _pin(pin) {}

void NTCSensor::begin() {
    pinMode(_pin, INPUT);
}

int NTCSensor::readRaw() {
    return analogRead(_pin);
}

float NTCSensor::rawToResistance(int raw) {
    // voltage divider formula: R_ntc = R_fixed * (Vcc/Vout - 1)
    // since Vout/Vcc = raw/ADC_MAX → R_ntc = R_fixed * (ADC_MAX/raw - 1)
    if (raw == 0) return 999999.0; // avoid division by zero
return NTC_R_FIXED * ((float)raw / (ADC_MAX - (float)raw));
}

float NTCSensor::resistanceToC(float resistance) {
    // Simplified Steinhart-Hart (Beta equation)
    float steinhart = log(resistance / NTC_R0) / NTC_BETA;
    steinhart += 1.0 / NTC_T0;
    return (1.0 / steinhart) - 273.15;
}

float NTCSensor::readTempC() {
    int raw = readRaw();
    float resistance = rawToResistance(raw);
    return resistanceToC(resistance);
}