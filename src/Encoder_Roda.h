#ifndef ENCODER_RODA_H
#define ENCODER_RODA_H

#include "Definicoes.h"

class Encoder_Roda
{
private:
    uint8_t _PIN;
    float _Pulsos_por_Revolucao;    // float para calculos
    bool Ultimo_Estado_Conhecido;
    unsigned long Tempo_Ultima_Borda_Detectada;
    unsigned long Contador_Bordas = 0;
    float Velocidade = 0.0f;

    float Calcular_Velocidade();
    
public:
    Encoder_Roda(uint8_t PIN, uint8_t Pulsos_por_Revolucao = 24);
    void Inicializar();
    void Loop();
    unsigned long Pegar_Contagem();
    float Pegar_Velocidade();
};


#endif