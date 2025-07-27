#ifndef VOICE_H
#define VOICE_H

#include "Motor.h"
#include "Definicoes.h"
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

// Pinos para o módulo de voz (ajuste conforme necessário)
SoftwareSerial voiceSerial(10, 11); // RX, TX
VR myVoice(&voiceSerial);

extern Motor M_Direito;
extern Motor M_Esquerdo;

void inicializarModuloVoz() {
    voiceSerial.begin(9600);

    if (myVoice.begin()) {
        Serial.println("Modulo de voz iniciado com sucesso.");
    } else {
        Serial.println("Falha ao iniciar modulo de voz.");
        while (1); // trava o sistema se falhar
    }

    // Carrega os comandos gravados (Group 0)
    if (myVoice.load((uint8_t)0) >= 0) {
        Serial.println("Comandos carregados.");
    } else {
        Serial.println("Falha ao carregar comandos.");
        while (1);
    }
}

void controleVoz() {
    uint8_t records[7]; // buffer para IDs dos comandos
    uint8_t commandCount;
    int8_t resultado = myVoice.recognize(records, &commandCount);

    if (resultado > 0) {
        switch (records[0]) {
            case 0: // go forward
                M_Direito.Comandar(velocidadeMotor, FRENTE);
                M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
                break;

            case 1: // go back
                M_Direito.Comandar(velocidadeMotor, TRAS);
                M_Esquerdo.Comandar(velocidadeMotor, TRAS);
                break;

            case 2: // left
                M_Direito.Comandar(velocidadeMotor, FRENTE);
                M_Esquerdo.Comandar(velocidadeMotor, TRAS);
                break;

            case 3: // right
                M_Direito.Comandar(velocidadeMotor, TRAS);
                M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
                break;

            case 4: // stop
                M_Direito.Comandar(velocidadeMotor, FREIO);
                M_Esquerdo.Comandar(velocidadeMotor, FREIO);
                break;

            case 5: // follow me
                M_Direito.Comandar(velocidadeMotor / 2, FRENTE);
                M_Esquerdo.Comandar(velocidadeMotor / 2, FRENTE);
                break;

            default:
                Serial.println("Comando não reconhecido.");
                break;
        }
    }
}

#endif
