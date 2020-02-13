#include <xc.h>
#include "LCD.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _XTAL_FREQ 4000000
float voltaje;
int V1;
int POT1A;
int POT1B;
int POT1C;
char POT1SA[5];
char POT1SB[5];
char POT1SC[5];
char PUNTO1[5];
uint8_t adc;
float voltaje3;
uint8_t adc2;
int V2;
int POT2A;
int POT2B;
int POT2C;
char POT2SA[5];
char POT2SB[5];
char POT2SC[5];
char PUNTO2[5];
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
        voltaje = (adc*5.0)/255.0;
        V1 = (voltaje)*100;
        POT1A = V1%10;
        itoa(POT1SA,POT1A,10);
        POT1B = (V1/10)%10;
        itoa(POT1SB,POT1B,10);
        POT1C = (V1/100)%10;
        itoa(POT1SC,POT1C,10);
        strcat(POT1SB,POT1SA);
        strcpy(PUNTO1,".");
        strcat(PUNTO1,POT1SB);
        strcat(POT1SC,PUNTO1);
        
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
        V2 = (voltaje3)*100;
        POT2A = V2%10;
        itoa(POT2SA,POT2A,10);
        POT2B = (V2/10)%10;
        itoa(POT2SB,POT2B,10);
        POT2C = (V2/100)%10;
        itoa(POT2SC,POT2C,10);
        strcat(POT2SB,POT2SA);
        strcpy(PUNTO2,".");
        strcat(PUNTO2,POT2SB);
        strcat(POT2SC,PUNTO2);
        
        strcat(POT2SC, " ");
        strcat(POT1SC, POT2SC);
        lcd_cmd(0xC0); 
        lcd_msg(POT1SC);
    }
    }
    return;
}

