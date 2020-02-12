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
#include <stdio.h>
#define  LCD PORTB
#define  RS  RC4
#define  RW  RC5
#define  EN  RC6
#define _XTAL_FREQ  4000000
/*inicializacion de LCD obtenida de https://www.youtube.com/watch?v=ve1PcD6Cegw&feature=youtu.be*/
void lcd_cmd(unsigned char x);
void lcd_dwr(unsigned char x);
void lcd_msg(unsigned char *c);
void lcd_ready();
void lcd_lat();
void lcd_init();
void voltaje1 (void);
float voltaje;
int adc;
signed char buffer[16];
float voltaje3;
int adc2;
unsigned char buffer_dos[16];


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
       while(1){
           lcd_cmd(0x00);
           __delay_ms(100);
       }
       return;
    }
}


void voltaje1 (void){
    while(1){
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    lcd_msg("S1    S2   cont.");
    while(1){
        __delay_ms(1);
        ADCON0bits.CHS0 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS3 = 0;
        ADCON0bits.ADON = 1;
        ADCON0bits.GO = 1;
        PIR1bits.ADIF = 0;
        adc = ADRESH;
        voltaje = adc*5.0/255.0;
        
        __delay_us(600);
        ADCON0bits.CHS0 = 1;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS3 = 0;
        ADCON0bits.ADON = 1;   // adc on
        ADCON0bits.GO = 1;
        PIR1bits.ADIF = 0;
        adc2 = ADRESH;
        voltaje3 = adc2*5.0/255.0;

        lcd_cmd(0xC0); 
        sprintf(buffer, "%04.2f %04.2f", voltaje, voltaje3);
        lcd_msg(buffer);
    }
    }
    return;
}
