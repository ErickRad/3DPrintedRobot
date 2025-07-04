#ifndef VOICE_H
#define VOICE_H

#include "Motor.h"
#include "Definicoes.h"
#include <SoftwareSerial.h>

extern SoftwareSerial BT;
extern Motor M_Direito;
extern Motor M_Esquerdo;

void controleVoz() {
    if (BT.available()) {
        String comando = BT.readStringUntil('\n');
        comando.trim();
        comando.toLowerCase();

        if (comando == "go ahead" || comando == "go forward") {
            M_Direito.Comandar(velocidadeMotor, FRENTE);
            M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
        } else if (comando == "back" || comando == "go back") {
            M_Direito.Comandar(velocidadeMotor, TRAS);
            M_Esquerdo.Comandar(velocidadeMotor, TRAS);
        } else if (comando == "left") {
            M_Direito.Comandar(velocidadeMotor, FRENTE);
            M_Esquerdo.Comandar(velocidadeMotor, TRAS);
        } else if (comando == "right") {
            M_Direito.Comandar(velocidadeMotor, TRAS);
            M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
        } else if (comando == "stop") {
            M_Direito.Comandar(velocidadeMotor, FREIO);
            M_Esquerdo.Comandar(velocidadeMotor, FREIO);
        } else if (comando == "come here" || comando == "follow me") {
            M_Direito.Comandar(velocidadeMotor / 2, FRENTE);
            M_Esquerdo.Comandar(velocidadeMotor / 2, FRENTE);
        }
    }
}

#endif
