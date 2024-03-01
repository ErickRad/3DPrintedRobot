#include "Encoder_Roda.h"

Encoder_Roda::Encoder_Roda(uint8_t PIN, uint8_t Pulsos_por_Revolucao)
{
    _PIN = PIN;
    _Pulsos_por_Revolucao = Pulsos_por_Revolucao;
    pinMode(_PIN, INPUT);
    Ultimo_Estado_Conhecido = digitalRead(_PIN);
    Tempo_Ultima_Borda_Detectada = millis();
}

void Encoder_Roda::Inicializar()
{

}

/*
* Calcula velocidade entre o registro da ocorrencia da ultima borda e o tempo atual 
*/
float Encoder_Roda::Calcular_Velocidade()
{
    float Tempo_Entre_Bordas = millis() - Tempo_Ultima_Borda_Detectada;
    return 1000.0f / (Tempo_Entre_Bordas * _Pulsos_por_Revolucao);
}

void Encoder_Roda::Loop()
{
    bool Estado_Atual = digitalRead(_PIN);
    if (Estado_Atual != Ultimo_Estado_Conhecido)
    {
        Contador_Bordas++;
        Velocidade = Calcular_Velocidade();
        Tempo_Ultima_Borda_Detectada = millis();
        Ultimo_Estado_Conhecido = Estado_Atual;
    }
}

unsigned long Encoder_Roda::Pegar_Contagem()
{
    return Contador_Bordas;
}

float Encoder_Roda::Pegar_Velocidade()
{
    // Se a roda parou de girar a velocidade medida vai diminuindo
    float Testar_Velocidade = Calcular_Velocidade();
    if (Testar_Velocidade < Velocidade)
    {
        return Testar_Velocidade;
    }
    return Velocidade;
}