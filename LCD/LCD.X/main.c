/*
 * File:   main.c
 * Author: Home
 *
 * Created on 3 de Abril de 2019, 10:42
 */


#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 8000000

#define RS LATCbits.LATC0
#define RW LATCbits.LATC1
#define E LATCbits.LATC2

void setup();
void envia_char(char dado);
void clear_lcd();
void inicia_lcd();
void envia_frase(char frase[]);

void main() {
    setup();
    inicia_lcd();
    envia_frase("Samuel Alves");
    clear_lcd();
    envia_frase("tá dando loop");
    return;
}

void setup() {
    TRISD = 0b00000000;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    ADCON1 = 0x0F;
}

void envia_char(char dado) {
    E = 0;
    RS = 1;
    LATD = dado;
    E = 1;
    E = 0;
    __delay_ms(100);
}

void clear_lcd() {
    RS = 0;
    LATD = 0b00000001; // Display clear
    E = 1;
    E = 0;
    __delay_ms(100);
}

void inicia_lcd() {
    __delay_ms(100);
    E = 0;
    RS = 0;
    LATD = 0b00111100; // Function set
    __delay_ms(100);
    E = 1;
    E = 0;
    LATD = 0b00001111; // Display on/off control
    __delay_ms(100);
    E = 1;
    E = 0;
    LATD = 0b00000001; // Display clear
    __delay_ms(100);
    E = 1;
    E = 0;
    __delay_ms(100);
}

void envia_frase(char frase[]) {
    int len = strlen(frase);
    for(int i = 0; i < len; i++)
        envia_char(frase[i]);
}
