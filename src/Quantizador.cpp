#include "Quantizador.h"

Quantizador::Quantizador(unsigned long Intervalo)
{
    _Intervalo = Intervalo;
    Reset_Temporizador();
}

void Quantizador::Loop()
{
    unsigned long Tempo_Atual = millis();
    _Quantizou = false;
    if (Tempo_Atual >= Tempo_Proxima_Quantizacao)
    {
        Tempo_Proxima_Quantizacao = Tempo_Atual + _Intervalo;
        _Quantizou = true;
    }
}

bool Quantizador::Quantizou()
{
    return _Quantizou;
}

void Quantizador::Reset_Temporizador()
{
    Tempo_Proxima_Quantizacao = millis() + _Intervalo;
}