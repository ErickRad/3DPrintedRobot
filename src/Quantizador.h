#ifndef QUANTIZADOR_H
#define QUANTIZADOR_H

#include "Definicoes.h"

class Quantizador {
    private:
    unsigned long _Intervalo;
    unsigned long Tempo_Proxima_Quantizacao;
    bool _Quantizou = false;

    public:
    Quantizador(unsigned long Intervalo);
    void Loop();
    bool Quantizou();
    void Reset_Temporizador();
};

#endif