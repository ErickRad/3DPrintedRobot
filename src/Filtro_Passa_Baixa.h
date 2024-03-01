#ifndef FILTRO_PASSA_BAIXA_H
#define FILTRO_PASSA_BAIXA_H

#include <Definicoes.h>

class Filtro_Passa_Baixa
{
private:
    double _Constante_Tempo_Subida;
    double _Constante_Tempo_Descida;
    double Saida;
    bool Limitar_Maximo, Limitar_Minimo;
    double _Limite_Maximo, _Limite_Minimo;

protected:
    unsigned long Tempo_Ultima_Execucao;

public:
    // Contrutores
    Filtro_Passa_Baixa(double tau);
    Filtro_Passa_Baixa(double tau_Subida, double tau_Descida);
    
    // Configurações extras
    void Limite_Maximo(double Limite);
    void Limite_Minimo(double Limite);
    void Limites(double Minimo, double Maximo);
    
    // Executa o filtro
    double Executar_Filtro(double Entrada);
};

#endif