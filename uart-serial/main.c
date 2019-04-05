/*
 * File:   main.c
 * Author: samer
 *
 * Created on 4 de Abril de 2019, 21:42
 */


#include <xc.h>

#define _XTAL_FREQ 8000000
#define ENVIA LATDbits.LATD0
#define RECEBE PORTDbits.RD1


void setup() {
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 1;
    ADCON1 = 0x0F;
}

void envia_serial(char dado) {
    ENVIA = 1;
    int n = 8;
    ENVIA = 0;
    __delay_us(833);
    while(n > 0) {
        ENVIA = dado;
        dado = dado >> 1;
        __delay_us(833);
        n--;
    }
    
    ENVIA = 1;
    __delay_us(833);
}

char recebe_serial() {
    char byte[8] = "01000001";
    
    __delay_us(416);
    __delay_us(833);
    for(int i = 7; i >= 0; i--) {
        byte[i] = RECEBE;
        __delay_us(810);
    }
    
    unsigned char dado = 0;
    
    for(int i = 0; i < 8; i++) {
        dado = dado << 1;
        dado = dado + byte[i];
    }
     
    return dado;
}

void main() {
    setup();
    char dado;
    
    while(1) {
        if(RECEBE == 0){
            dado = recebe_serial(); 
            envia_serial(dado);
        }
    }
}