/*
 * File:   main.c
 * Author: samer
 *
 * Created on 4 de Abril de 2019, 21:50
 */


#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 8000000

// Teclado
#define X_1 LATBbits.LATB0
#define X_2 LATBbits.LATB1
#define X_3 LATBbits.LATB2
#define X_4 LATBbits.LATB3

#define Y_1 PORTBbits.RB4
#define Y_2 PORTBbits.RB5
#define Y_3 PORTBbits.RB6

// LCD
#define RS LATCbits.LATC0
#define RW LATCbits.LATC1
#define E LATCbits.LATC2


// Funçoes LCD
void setup();
void envia_char(char dado);
void clear_lcd();
void inicia_lcd();
void envia_frase(char frase[]);

// Funções Teclado
char switch_press_scan();
void initKeypad();
char keypad_scanner();

void main(void) {
    setup();
    initKeypad();
    inicia_lcd();
    char key = 'n';
    while(1) {
        key = switch_press_scan();
        envia_char(key);
        
        
    }
    return;
}

char switch_press_scan(void) {
    char key = 'n';              // Assume no key pressed
    while(key=='n')              // Wait untill a key is pressed
    key = keypad_scanner();   // Scan the keys again and again
    return key;                  //when key pressed then return its value
}

char keypad_scanner(void) {           
    X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); return '1'; }
    if (Y_2 == 0) { __delay_ms(100); return '2'; }
    if (Y_3 == 0) { __delay_ms(100); return '3'; }
  
    X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); return '4'; }
    if (Y_2 == 0) { __delay_ms(100); return '5'; }
    if (Y_3 == 0) { __delay_ms(100); return '6'; }

    X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); return '7'; }
    if (Y_2 == 0) { __delay_ms(100); return '8'; }
    if (Y_3 == 0) { __delay_ms(100); return '9'; }
    
    X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
    if (Y_1 == 0) { __delay_ms(100); return '*'; }
    if (Y_2 == 0) { __delay_ms(100); return '0'; }
    if (Y_3 == 0) { __delay_ms(100); return '#'; }
            
    return 'n';                   
}

void initKeypad() {
    PORTB = 0x00;        // Set Keypad port pin values zero
    TRISB = 0xF0;      // Last 4 pins input, First 4 pins output
}

void setup() {
    PORTB = 0b11100000;
    TRISB = 0xF0;
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
