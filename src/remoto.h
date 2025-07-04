#ifndef REMOTO_H
#define REMOTO_H

#include "Motor.h"
#include "Definicoes.h"
#include <SoftwareSerial.h>

extern SoftwareSerial BT;
extern Motor M_Direito;
extern Motor M_Esquerdo;

void controleRemoto() {
    if (BT.available()) {
        char comando = BT.read();

        switch (comando) {
            case 'F': // Frente
                M_Direito.Comandar(velocidadeMotor, FRENTE);
                M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
                break;
            case 'B': // Trás
                M_Direito.Comandar(velocidadeMotor, TRAS);
                M_Esquerdo.Comandar(velocidadeMotor, TRAS);
                break;
            case 'L': // Esquerda
                M_Direito.Comandar(velocidadeMotor, FRENTE);
                M_Esquerdo.Comandar(velocidadeMotor, TRAS);
                break;
            case 'R': // Direita
                M_Direito.Comandar(velocidadeMotor, TRAS);
                M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
                break;
            case 'S': // Parar
                M_Direito.Comandar(velocidadeMotor, FREIO);
                M_Esquerdo.Comandar(velocidadeMotor, FREIO);
                break;
        }
    }
}

#endif
