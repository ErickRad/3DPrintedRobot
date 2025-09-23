#ifndef VOICE_H
#define VOICE_H

#include "Motor.h"
#include "Definicoes.h"
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include "Ultrassonico.h"
#include "Encoder_Roda.h"

SoftwareSerial voiceSerial(10, 11);
VR myVoice(&voiceSerial);

extern Motor M_Direito;
extern Motor M_Esquerdo;

Ultrassonico frontSensor;
Ultrassonico leftSensor;
Ultrassonico rightSensor;

Encoder_Roda encoderDireita(2, 20);
Encoder_Roda encoderEsquerda(3, 20);

#define VELOCIDADE_MAX 150
#define DISTANCIA_MIN 10

void inicializarModuloVoz() {
    voiceSerial.begin(9600);
    if (!myVoice.begin()) while (1);
    if (myVoice.load((uint8_t)0) < 0) while (1);
    encoderDireita.Inicializar();
    encoderEsquerda.Inicializar();
}

void atualizarEncoders() {
    encoderDireita.Loop();
    encoderEsquerda.Loop();
}

void andarSeguindoCaminho() {
    while(true) {
        int distFront = frontSensor.getDistance();
        int distLeft = leftSensor.getDistance();
        int distRight = rightSensor.getDistance();

        if(distFront < DISTANCIA_MIN) {
            M_Direito.Comandar(0, FREIO);
            M_Esquerdo.Comandar(0, FREIO);
            break;
        }

        float ajuste = 0;
        if(distLeft < distRight) ajuste = (distRight - distLeft) * 0.5;
        else ajuste = -(distLeft - distRight) * 0.5;

        int velDireito = VELOCIDADE_MAX - ajuste;
        int velEsquerdo = VELOCIDADE_MAX + ajuste;

        if(velDireito > VELOCIDADE_MAX) velDireito = VELOCIDADE_MAX;
        if(velEsquerdo > VELOCIDADE_MAX) velEsquerdo = VELOCIDADE_MAX;
        if(velDireito < 0) velDireito = 0;
        if(velEsquerdo < 0) velEsquerdo = 0;

        M_Direito.Comandar(velDireito, FRENTE);
        M_Esquerdo.Comandar(velEsquerdo, FRENTE);

        atualizarEncoders();
    }
}

void girar90Graus(bool sentidoHorario) {
    unsigned long contagemInicialDireita = encoderDireita.Pegar_Contagem();
    unsigned long contagemInicialEsquerda = encoderEsquerda.Pegar_Contagem();
    const unsigned long PULSOS_90GRAUS = 50;

    while(true) {
        atualizarEncoders();
        unsigned long deltaDireita = encoderDireita.Pegar_Contagem() - contagemInicialDireita;
        unsigned long deltaEsquerda = encoderEsquerda.Pegar_Contagem() - contagemInicialEsquerda;

        if(deltaDireita >= PULSOS_90GRAUS && deltaEsquerda >= PULSOS_90GRAUS) break;

        if(sentidoHorario) {
            M_Direito.Comandar(100, TRAS);
            M_Esquerdo.Comandar(100, FRENTE);
        } else {
            M_Direito.Comandar(100, FRENTE);
            M_Esquerdo.Comandar(100, TRAS);
        }
    }

    M_Direito.Comandar(0, FREIO);
    M_Esquerdo.Comandar(0, FREIO);
}

void controleVoz() {
    uint8_t records[7];
    uint8_t commandCount;
    int8_t resultado = myVoice.recognize(records, &commandCount);

    if(resultado > 0) {
        switch(records[0]) {
            case 0:
                andarSeguindoCaminho();
                break;
            case 1:
                M_Direito.Comandar(150, TRAS);
                M_Esquerdo.Comandar(150, TRAS);
                delay(500);
                M_Direito.Comandar(0, FREIO);
                M_Esquerdo.Comandar(0, FREIO);
                break;
            case 2:
                girar90Graus(false);
                break;
            case 3:
                girar90Graus(true);
                break;
            case 4:
                M_Direito.Comandar(0, FREIO);
                M_Esquerdo.Comandar(0, FREIO);
                break;
            default:
                break;
        }
    }
}

#endif
