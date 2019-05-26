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
#define POINT_1 PORTDbits.RD3
#define POINT_2 PORTDbits.RD4

void setup();
void clock();
void key();
void sendData(int data);
void sendDualData(int data1, int data2);
void setTimer(int minutos_dezena, int minutos_unidade, int segundos_dezena, int segundos_unidade);

int byte7seg[10] = {
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110, //6
    0b11100000, //7
    0b11111110, //8
    0b11110110  //9 
};

void main(void) {
    setup();
    int minutos_dezena = 0;
    int minutos_unidade = 0;
    int segundos_dezena = 0;
    int pontos1 = 0;
    int pontos2 = 0;
    while(1) {
        if(POINT_1 == 1) {
            pontos1++;
        }
        if(POINT_2 == 1) {
            pontos2++;
        }
        for(int i = 0; i < 10; i++) {
            sendData(byte7seg[pontos2]);
            sendData(byte7seg[pontos1]);
            setTimer(byte7seg[minutos_dezena], byte7seg[minutos_unidade], byte7seg[segundos_dezena], byte7seg[i]);
            key();
            __delay_ms(10);
        }
        segundos_dezena++;
        if(segundos_dezena > 5) {
            segundos_dezena = 0;
            minutos_unidade++;
            if(minutos_unidade > 9) {
                minutos_unidade = 0;
                minutos_dezena++;
            }
        }
    }
    return;
}

void setTimer(int minutos_dezena, int minutos_unidade, int segundos_dezena, int segundos_unidade) {
    for(int i = 0; i < 8; i++) {
        DATA = (minutos_dezena >> i) & 0x01;
        clock();
    }
    for(int i = 0; i < 8; i++) {
        DATA = (minutos_unidade >> i) & 0x01;
        clock();
    }for(int i = 0; i < 8; i++) {
        DATA = (segundos_dezena >> i) & 0x01;
        clock();
    }
    for(int i = 0; i < 8; i++) {
        DATA = (segundos_unidade >> i) & 0x01;
        clock();
    }
    //key();
}

void sendDualData(int data1, int data2) {
    for(int i = 0; i < 8; i++) {
        DATA = (data1 >> i) & 0x01;
        clock();
    }
    for(int i = 0; i < 8; i++) {
        DATA = (data2 >> i) & 0x01;
        clock();
    }
    key();
}

void sendData(int data) {
    for(int i = 0; i < 8; i++) {
        DATA = (data >> i) & 0x01;
        clock();
    }
    //key();
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
    ADCON1 = 0x0F;
    TRISD = 0b00011000;
}