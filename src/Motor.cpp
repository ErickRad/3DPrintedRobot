#include "Motor.h"

Motor::Motor(uint8_t PIN_N1, uint8_t PIN_N2, uint8_t PIN_PWM) : Filtro_Passa_Baixa(1.0, 0.001)
{
    _PIN_N1 = PIN_N1;
    _PIN_N2 = PIN_N2;
    _PIN_PWM = PIN_PWM;
}

void Motor::Inicializar()
{
    pinMode(_PIN_N1, OUTPUT);
    pinMode(_PIN_N2, OUTPUT);
    pinMode(_PIN_PWM, OUTPUT);
}

void Motor::Comandar(uint8_t Potencia, ESTADO_MOTOR Estado)
{
#ifdef TESTE_SEM_MOTOR
    Potencia = 0;
    Estado = LIVRE;
#endif

    switch (Estado)
    {
    default:
    case FRENTE:
        digitalWrite(_PIN_N1, HIGH);
        digitalWrite(_PIN_N2, LOW);
        break;
    
    case TRAS:
        digitalWrite(_PIN_N1, LOW);
        digitalWrite(_PIN_N2, HIGH);
        break;

    case FREIO:
        digitalWrite(_PIN_N1, HIGH);
        digitalWrite(_PIN_N2, HIGH);
        break;

    case LIVRE:
        digitalWrite(_PIN_N1, LOW);
        digitalWrite(_PIN_N2, LOW);
        break;
    }

    _Potencia = Executar_Filtro(Potencia);
    analogWrite(_PIN_PWM, _Potencia);
}

uint8_t Motor::Obter_Potencia()
{
    return _Potencia;
}