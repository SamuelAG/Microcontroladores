/*
 * File:   main.c
 * Author: samer
 *
 * Created on 22 de Abril de 2019, 22:53
 */

#include <xc.h>
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
#define CLOCK LATDbits.LATD0
#define DATA LATDbits.LATD1
#define KEY LATDbits.LATD2

void setup();
void clock();
void key();
void sendData(int data);

void main(void) {
    setup();
    while(1){
        sendData(0b11111100); // 0
        __delay_ms(500);
        sendData(0b01100000); // 1
        __delay_ms(500);
        sendData(0b11011010); // 2
        __delay_ms(500);
        sendData(0b11110010); // 3
        __delay_ms(500);
        sendData(0b01100110); // 4
        __delay_ms(500);
        sendData(0b10110110); // 5
        __delay_ms(500);        
        sendData(0b10111110); // 6
        __delay_ms(500);
        sendData(0b11100000); // 7
        __delay_ms(500);
        sendData(0b11111111); // 8
        __delay_ms(500);
        sendData(0b11110111); // 9   
        __delay_ms(500);
     }
    return;
}

void sendData(int data) {
    for(int i = 0; i < 8; i++) {
        DATA = (data >> i) & 0x01;
        clock();
    }
    key();
}

void clock() {
    CLOCK = 1;
    __delay_us(500);
    CLOCK = 0;
    __delay_us(500);
}

void key() {
    KEY = 1;
    __delay_us(500);
    KEY = 0;
}

void setup() {
    TRISD = 0x00;
}