#include "Definicoes.h"
#include "Motor.h"
#include "Encoder_Roda.h"
#include "Ultrasonico.h"
#include "Quantizador.h"
#include "LiquidCrystal_I2C.h"
#include "Apoio.h"
#include <Wire.h>
#include "Remoto.h"
#include "Voice.h"
#include <SoftwareSerial.h>

Motor M_Direito(motorDireitoN1, motorDireitoN2, motorDireitoPWM);
Motor M_Esquerdo(motorEsquerdoN1, motorEsquerdoN2, motorEsquerdoPWM);

Encoder_Roda Roda_Direita(encoderMotorDireito);
Encoder_Roda Roda_Esquerda(encoderMotorEsquerdo);

LiquidCrystal_I2C LCD(0x3F, 16, 2);
SoftwareSerial BT(12, 13);
Sensor_Ultrasonico S_Distancia(Echo, Trigger);
int leitura, modo = 1;
void modos(){
    LCD.setCursor(0,0);
    if(modo == 1){
        LCD.clear();
        LCD.print("      Mode      ");
        LCD.setCursor(0,1);
        LCD.print(" *--   Follower ");
    }
    if(modo == 2){
        LCD.clear();
        LCD.print("      Mode      ");
        LCD.setCursor(0,1);
        LCD.print(" -*-   Remote   ");
    }
    if(modo == 3){
        LCD.clear();
        LCD.print("      Mode      ");
        LCD.setCursor(0,1);
        LCD.print(" --*   FBI      ");
    }
    if (modo > 3){
        modo = 3;
    }
    if (modo < 1){
        modo = 1;
    }
}

void kali(){
    byte KALI1[8] = {B00000, B01111,B00000,B01111,B10000,B00111,B01000,B00000};
    byte KALI2[8] = {B00000,B10000,B01100,B11100,B01110,B10011,B00010,B00010};
    byte KALI3[8] = {B00000,B00000,B01110,B00001,B11111,B00000,B00000,B00000};
    byte KALI4[8] = {B00000,B00000,B00000,B00000,B10000,B11000,B00000,B00000};
    byte KALI5[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};
    byte KALI6[8] = {B00010,B00010,B00001,B00000,B00000,B00000,B00000,B00000};
    byte KALI7[8] = {B00000,B00000,B00000,B11111,B00010,B00001,B00000,B00000};
    byte KALI8[8] = {B00000,B00000,B00000,B10000,B01000,B00100,B10100,B10000};

    LCD.createChar(0, KALI1);
    LCD.createChar(1, KALI2);
    LCD.createChar(2, KALI3);
    LCD.createChar(3, KALI4);   
    LCD.createChar(4, KALI5);
    LCD.createChar(5, KALI6);
    LCD.createChar(6, KALI7);
    LCD.createChar(7, KALI8);

    LCD.clear();
    LCD.setCursor(6,0);
    LCD.write(0);
    LCD.write(1);
    LCD.write(2);
    LCD.write(3);

    LCD.setCursor(6,1);
    LCD.write(4);
    LCD.write(5);
    LCD.write(6);
    LCD.write(7);

}


void intro(){
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("   Bem-vindo   ");
    LCD.setCursor(0,1);
    LCD.print("    Erick R.   ");
    delay(2000);
    
    modos();
}

void Seguir_Linha(){
    bool S_Esquerdo = digitalRead(sensorEsquerdo);
    bool S_Direito = digitalRead(sensorDireito);

    if (S_Esquerdo and (S_Direito)){
        M_Direito.Comandar(velocidadeMotor, FRENTE);
        M_Esquerdo.Comandar(velocidadeMotor, FRENTE);

    }else{
        if(S_Esquerdo and not (S_Direito)){
            M_Direito.Comandar(velocidadeMotor, FRENTE);
            M_Esquerdo.Comandar(velocidadeMotor/6, TRAS);
        }
        if(S_Direito and not (S_Esquerdo)){
            M_Esquerdo.Comandar(velocidadeMotor, FRENTE);
            M_Direito.Comandar(velocidadeMotor/6, TRAS);
        }
        if (!S_Esquerdo and (!S_Direito)){
            M_Direito.Comandar(velocidadeMotor, FREIO);
            M_Esquerdo.Comandar(velocidadeMotor, FREIO);    

        }
    }   
}

void setup()
{   

    M_Direito.Inicializar();
    M_Esquerdo.Inicializar();
    BT.begin(9600);
    LCD.init();

    pinMode(sensorDireito, INPUT);
    pinMode(sensorEsquerdo, INPUT);

    Encontrar_Enderecos_i2c();
    intro();
    
}    

void loop()
{   
    while(true){
        leitura = analogRead(A3);
        Serial.print(leitura);

        if(leitura < 50 && leitura > -50){
            modo++;
            modos();
        }
        if(leitura > 380 && leitura < 500){
            modo--;
            modos();
        }
        if(leitura > 550 && leitura < 700){
            LCD.clear();
            LCD.setCursor(0,0);
            if(modo == 1){
                LCD.print("Follower");
            }else if(modo == 2){
                LCD.print("Remote");
            }else if(modo == 3){
                LCD.print("FBI");
            }

            LCD.setCursor(0,1);
            LCD.print("UP - Main menu");                             
            break;
        }
        delay(90);
    }
    while(true){
        if (leitura > 50 && leitura < 195){
            break;
        }else{
           if(modo == 1){
                Seguir_Linha();
            }else if(modo == 2){
                ControleRemoto();
            }else if(modo == 3){
                ControleVoz();
            }
        }
        delay(10);
    }
}




