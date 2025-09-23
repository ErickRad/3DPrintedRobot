#ifndef REMOTO_H
#define REMOTO_H

#include "Motor.h"
#include "Definicoes.h"
#include <SoftwareSerial.h>

extern SoftwareSerial BT;
extern Motor M_Direito;
extern Motor M_Esquerdo;

#define VELOCIDADE_MAX 200
#define VELOCIDADE_MIN 50
#define AJUSTE_CURVA 50

char ultimoComando = 'S';

void controleRemoto() {
    if(BT.available()) {
        char comando = BT.read();
        if(comando == ultimoComando) return;
        ultimoComando = comando;

        int velDireito = VELOCIDADE_MAX;
        int velEsquerdo = VELOCIDADE_MAX;

        switch(comando) {
            case 'F':
                M_Direito.Comandar(velDireito, FRENTE);
                M_Esquerdo.Comandar(velEsquerdo, FRENTE);
                break;
            case 'f':
                M_Direito.Comandar(VELOCIDADE_MIN, FRENTE);
                M_Esquerdo.Comandar(VELOCIDADE_MIN, FRENTE);
                break;
            case 'B':
                M_Direito.Comandar(velDireito, TRAS);
                M_Esquerdo.Comandar(velEsquerdo, TRAS);
                break;
            case 'b':
                M_Direito.Comandar(VELOCIDADE_MIN, TRAS);
                M_Esquerdo.Comandar(VELOCIDADE_MIN, TRAS);
                break;
            case 'L':
                M_Direito.Comandar(velDireito - AJUSTE_CURVA, FRENTE);
                M_Esquerdo.Comandar(velEsquerdo, FRENTE);
                break;
            case 'R':
                M_Direito.Comandar(velDireito, FRENTE);
                M_Esquerdo.Comandar(velEsquerdo - AJUSTE_CURVA, FRENTE);
                break;
            case 'S':
                M_Direito.Comandar(0, FREIO);
                M_Esquerdo.Comandar(0, FREIO);
                break;
            default:
                break;
        }
    }
}

#endif
