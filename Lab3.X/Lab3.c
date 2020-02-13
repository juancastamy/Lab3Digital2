/*
 * Second lab for Digital 2 course
 * File:   lab_2.c
 * Author: Juan Diego Castillo Amaya
 * Student ID: 17074
 *
 * Created on Feb. 7, 2020
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "ADC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*inicializacion de LCD obtenida de https://www.youtube.com/watch?v=ve1PcD6Cegw&feature=youtu.be*/
/*void SERIAL_INT(void);
uint8_t SERIAL_READ(void);
void SERIAL_READTX(char *output, unsigned int length);
void SERIAL_WRITE(char data);
void SERIAL_WRITETX(char* tx);*/
void main(void) {
      //entradas, salidas, entradas digitales o analogicas
    ANSEL = 0b00001001;
    ANSELH= 0b00000000;
    TRISA = 0b00001001;
    TRISB = 0b00000000; 
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;  
    
    while(1){
       lcd_init();
       voltaje1();
       //SERIAL_INT(); 
       //SERIAL_READ();
       while(1){
           lcd_cmd(0x00);
           __delay_ms(100);
       }
       return;
    }
}

/*void SERIAL_INT(void){
    SPBRG = 25;
    // EL QUE TX
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    //RX
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
}
uint8_t SERIAL_READ(void){
    if(PIR1bits.RCIF == 1){
        return RCREG;
    }
}
void SERIAL_READTX(char *output, unsigned int length){
    unsigned int x;
    for(int x=0; x<length; x++){
        output[x] = SERIAL_READ();
    }
}
void SERIAL_WRITE(char data){
    while(TXSTAbits.TRMT !=1){
        TXREG = data;
    }
}
void SERIAL_WRITETX(char* tx){
    int y;
    for(y=0;tx[y]!='\0';y++){
        SERIAL_WRITE(tx[y]);
    }
}*/