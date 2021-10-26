/*
 * File:   main.c
 * Author: Renato Pepe
 * Description:     Atuar como um controle remoto IR
 *                   utilizando protocolo NEC
 * Controlador:     PIC12F1822
 * Created on 25 de Outubro de 2021, 16:37
 */


#include "config.h"
#include <PIC12F1822.h>
#include "utils.h"

/* Define dos pinos utilizados */
#define pin_Led 2   
#define pin_Led2 0

/* Variaveis globais */
//Timer counter, increments each milisecond 
unsigned long uiCounterms = 0;
unsigned long uiCountermsTimer2 = 0;
/* *****************************************************************************/
 /* Method name:        my_isr_routine                                         */
 /* Method description: Rotina de interrupção ISR, é chamada de acordo com     */
 /*                      o timer 0 e atuailza o contador de tempo global       */
 /* Input params:       n/a                                                    */
 /* Output params:      n/a                                                    */
 /* ****************************************************************************/
void __interrupt () my_isr_routine (void) {
    if(TMR0IF) // Timer flag has been triggered due to timer overflow
    {   
        TMR0 = 131;     //Load the timer Value
        TMR0IF = 0;     // Clear timer interrupt flag
        uiCounterms++;  //update global timer counter
    } 
    if(TMR2IF){
        TMR2IF = 0;
        uiCountermsTimer2++;
    }
    
}

void main(void) {
    
    /* 
     * Clock config: 16Mhz at FOSC determined clock
    */
    OSCCON = 0b1111100;
    
   /*****Port Configuration for Timer0 ******/
    OPTION_REG = 0b0000100;  // Timer0 with external freq and 32 as prescaler // Also Enables PULL UPs
    TMR0=131;       //16Mhz clock with 32 prescalar and TMR0 = 125 -> interrupt each 1ms 
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    /***********______***********/ 
    
    /*****Port Configuration for Timer 2 ******/
    TMR2IE = 1;     //allow interruptions
    T2CON = 0b00111101;  //config: postscaler as 8, timer start as on, prescaler as 4
    PR2 = 125; /*
                * 16Mhz clock / 4 cycles per instruction
                *  4 prescaler and 8 postscaler
                *  with PR2 = 125 -> interrupt will be triggered every 1ms
               */
    
    /***** Port configuration for inputs/outputs ******/
    ANSELA = 0x00;         //set pin as i/o
    TRISA = 0b1111010;     //set RA2 and RA0 as output and the rest as input
    PORTA = 0x00;          //clear latch
    
    //contador local de tempo
    unsigned long uiContadorTempo = 0;
    unsigned long uiContadorTempo2 = 0;
    
    while(1){
        
        //liga/desliga o LED a cada 1ms (baseado no timer0)
        if((uiCounterms - uiContadorTempo) > 1000){
            togglePin(pin_Led);   //toggle led (RA2)
     
        //atualiza contador de tempo
            uiContadorTempo = uiCounterms;
        }
        
         //liga/desliga o LED a cada 1ms (baseado no timer2)
        if((uiCountermsTimer2 - uiContadorTempo2) > 1000){
            togglePin(pin_Led2);   //toggle led (RA0)
     
        //atualiza contador de tempo
            uiContadorTempo2 = uiCountermsTimer2;
        }
    }    
}
