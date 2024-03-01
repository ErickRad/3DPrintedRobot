#ifndef MOTOR_H
#define MOTOR_H

#include <Definicoes.h>
#include "Motor.h"
#include "Filtro_Passa_Baixa.h"

typedef enum {
    FRENTE,
    TRAS,
    FREIO,
    LIVRE,
} ESTADO_MOTOR;

class Motor : Filtro_Passa_Baixa
{
private:
    uint8_t _PIN_N1;
    uint8_t _PIN_N2;
    uint8_t _PIN_PWM;
    uint8_t _Potencia;

public:
    Motor(uint8_t PIN_N1, uint8_t PIN_N2, uint8_t PIN_PWM);
    void Inicializar();
    void Comandar(uint8_t Potencia, ESTADO_MOTOR Estado = FRENTE);
    uint8_t Obter_Potencia();
};

#endif