/*
 * File:   main.c
 * Author: samer
 *
 * Created on 22 de Abril de 2019, 22:53
 */

#include "config.c"

#define CLOCK LATDbits.LATD0
#define DATA LATDbits.LATD1
#define KEY LATDbits.LATD2
#define POINT_1 PORTDbits.RD3
#define POINT_2 PORTDbits.RD4

// Protótipo das funções
void setup();
void clock();
void key();

void sendData(int data);
void setTimer(int minutos_dezena, int minutos_unidade, int segundos_dezena, int segundos_unidade);
void setScore(int centena, int dezena, int unidade);

// Vetor para armazenar os códigos do display 7 segmentos.
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
    // Variaveis para controlar o relógio.
    int minutos_dezena = 0;
    int minutos_unidade = 0;
    int segundos_dezena = 0;
    // Vetores para armazenar a dezena e unidade dos pontos de cada time, a posição 0 armezena a unidade e a posição 1 a dezena.
    int pontos1[3] = {0, 0, 0};
    int pontos2[3] = {0, 0, 0};
    
    while(1) {
        // Loop para contabilizar os segundos e enviar os dados para os displays.
        // O primeiro byte a ser enviado corresponde ao ultimo display cascateado e assim por diante.
        for(int segundos = 0; segundos < 10; segundos++) {
            setScore(byte7seg[pontos2[2]], byte7seg[pontos2[1]], byte7seg[pontos2[0]]); // Envia os bytes de pontos do time 2
            setTimer(byte7seg[minutos_dezena], byte7seg[minutos_unidade], byte7seg[segundos_dezena], byte7seg[segundos]); // Envia os bytes do relógio
            setScore(byte7seg[pontos2[2]], byte7seg[pontos1[1]], byte7seg[pontos1[0]]); // Envia os bytes de pontos do time 1
            key();
            pontos1[0]++;
            pontos2[0]++;
            __delay_ms(10);
        }
        
        // Incrementa os pontos a cada 10 segundos apenas para testes.
        //pontos1[0]++;
        //pontos2[0]++;
        
        // Lógica de incrementar dezena e centena dos pontos.
        if(pontos2[0] > 9) {
            pontos2[1]++;
            pontos2[0] = 0;
            if(pontos2[1] > 9) {
                pontos2[1] = 0;
                pontos2[2]++;
            }
        }
        if(pontos1[0] > 9) {
            pontos1[1]++;
            pontos1[0] = 0;
            if(pontos1[1] > 9) {
                pontos1[1] = 0;
                pontos1[2]++;
            }
        }
        
        // Lógica para incrementar dezena de segundos e minutos do relógio 
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
}

void setScore(int centena, int dezena, int unidade) {
    for(int i = 0; i < 8; i++) {
        DATA = (centena >> i) & 0x01;
        clock();
    }
    for(int i = 0; i < 8; i++) {
        DATA = (dezena >> i) & 0x01;
        clock();
    }
    for(int i = 0; i < 8; i++) {
        DATA = (unidade >> i) & 0x01;
        clock();
    }
}

void sendData(int data) {
    for(int i = 0; i < 8; i++) {
        DATA = (data >> i) & 0x01;
        clock();
    }
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