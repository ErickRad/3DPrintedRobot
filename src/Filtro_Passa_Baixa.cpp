#include "Filtro_Passa_Baixa.h"

Filtro_Passa_Baixa::Filtro_Passa_Baixa(double tau) : Filtro_Passa_Baixa(tau, tau)
{
    //this.Filtro_Passa_Baixa(tau, tau);
}

Filtro_Passa_Baixa::Filtro_Passa_Baixa(double tau_Subida, double tau_Descida)
{
    Tempo_Ultima_Execucao = 0;
    _Constante_Tempo_Subida = 1.0 / tau_Subida;
    _Constante_Tempo_Descida = 1.0 / tau_Descida;
    Limitar_Maximo = false;
    Limitar_Minimo = false;
}

void Filtro_Passa_Baixa::Limite_Maximo(double Limite)
{
    _Limite_Maximo = Limite;
    Limitar_Maximo = true;
}

void Filtro_Passa_Baixa::Limite_Minimo(double Limite)
{
    _Limite_Minimo = Limite;
    Limitar_Minimo = true;
}

void Filtro_Passa_Baixa::Limites(double Minimo, double Maximo)
{
    Limite_Minimo(Minimo);
    Limite_Maximo(Maximo);
}

double Filtro_Passa_Baixa::Executar_Filtro(double Entrada)
{
    if (Tempo_Ultima_Execucao == 0 ||             // indica que é a primeira vez que o filtro está sendo executado
        (millis() - Tempo_Ultima_Execucao) > 100) // Indica que se passou muito tempo entre as execuções e os efeitos do filtro podem ser inesperados
    {
        Saida = Entrada;
    }
    else
    {
        // Obtendo o passo
        double Passo = ((double)(millis() - Tempo_Ultima_Execucao)) / 1000.0;
        if (Passo == 0.0)
        {
            Passo = 0.001;
        }

        // Verificando qual a constante de tempo que se deve utilizar
        double Constante_Tempo;
        if (Entrada > Saida)
        {
            Constante_Tempo = _Constante_Tempo_Subida;
        }
        else
        {
            Constante_Tempo = _Constante_Tempo_Descida;
        }

        // Aplicando o filtro
        double Resultado = Constante_Tempo * ((double)(Entrada - Saida)) * Passo;

        /*
        PRINT_VARIAVEL(_Constante_Tempo_Subida);
        PRINT_VARIAVEL(_Constante_Tempo_Descida);
        PRINT_VARIAVEL(Constante_Tempo);
        PRINT_VARIAVEL(Entrada);
        PRINT_VARIAVEL(Saida);
        PRINT_VARIAVEL(Passo);
        PRINT_VARIAVEL(Resultado);
        */

        // Somando o resultado do filtro
        Saida += Resultado;

        // Limitando a saida
        if ((Limitar_Maximo == true) &&
            (_Limite_Maximo < Saida))
        {
            Saida = _Limite_Maximo;
        }

        if ((Limitar_Minimo == true) &&
            (_Limite_Minimo > Saida))
        {
            Saida = _Limite_Minimo;
        }
    }

    // Salva o tempo em que o calculo foi executado
    Tempo_Ultima_Execucao = millis();
    return Saida;
}