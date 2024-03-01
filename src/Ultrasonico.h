#ifndef ULTRASONICO_H
#define ULTRASONICO_H

#include "Definicoes.h"

class Sensor_Ultrasonico
{
    private:
    uint8_t _PIN_ECHO, _PIN_TRIGGER;
    int16_t Ultima_Distancia_Medida = -1;
    unsigned long Temporizador_Inicio;
    
    public:
    Sensor_Ultrasonico(uint8_t PIN_ECHO, uint8_t PIN_TRIGGER);
    bool Efetuar_Medicao();
    unsigned long Pegar_Distancia();
};

#endif