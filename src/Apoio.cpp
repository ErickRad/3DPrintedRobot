#include "Apoio.h"

// I2C Scanner
// Written by Nick Gammon
// Date: 20th April 2011

void Encontrar_Enderecos_i2c()
{
    Serial.println();
    Serial.println(F("I2C scanner. Procurando ..."));
    byte count = 0;

    Wire.begin();
    for (byte i = 8; i < 120; i++)
    {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0)
        {
            Serial.print(F("Endereco encontrado: "));
            Serial.print(i, DEC);
            Serial.print(F(" (0x"));
            Serial.print(i, HEX);
            Serial.println(F(")"));
            count++;
            delay(1); // maybe unneeded?
        }             // end of good response
    }                 // end of for loop
    Serial.println("Finanlizado.");
    Serial.print("Encontrado ");
    Serial.print(count, DEC);
    Serial.println(" dispositivos(s).");
}