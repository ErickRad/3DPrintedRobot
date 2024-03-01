#include "Ultrasonico.h"

Sensor_Ultrasonico::Sensor_Ultrasonico(uint8_t PIN_ECHO, uint8_t PIN_TRIGGER)
{
    _PIN_ECHO = PIN_ECHO;
    _PIN_TRIGGER = PIN_TRIGGER;
    pinMode(_PIN_TRIGGER, OUTPUT);
    pinMode(_PIN_ECHO, INPUT);
}

bool Sensor_Ultrasonico::Efetuar_Medicao()
{
    digitalWrite(_PIN_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(_PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(_PIN_TRIGGER, LOW);

    unsigned long Distancia_Medida = pulseIn(_PIN_ECHO, HIGH, 6000) / 58;
    
    if (Distancia_Medida > 0)
    {
        Ultima_Distancia_Medida = Distancia_Medida;
        return true;
    }
    return false;
}

unsigned long Sensor_Ultrasonico::Pegar_Distancia()
{
    return Ultima_Distancia_Medida;
}