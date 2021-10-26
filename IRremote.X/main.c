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

/* Variaveis globais */
//Timer counter, increments each milisecond 
unsigned long uiCounterms = 0;

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
}

void main(void) {
    
    /* 
     * Clock config: 16Mhz at FOSC determined clock
    */
    OSCCON = 0b1111100;
    
   /*****Port Configuration for Timer ******/
    OPTION_REG = 0b0000100;  // Timer0 with external freq and 32 as prescaler // Also Enables PULL UPs
    TMR0=131;       //16Mhz clock with 32 prescalar and TMR0 = 125 -> interrupt each 1ms 
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    /***********______***********/ 
    
    /***** Port configuration for inputs/outputs ******/
    ANSELA = 0x00;         //set pin as i/o
    TRISA = 0b1111011;     //set RA2 as output and the rest as input
    PORTA = 0x00;          //clear latch
    
    //contador local de tempo
    unsigned long uiContadorTempo = 0;
    
    while(1){
        if((uiCounterms - uiContadorTempo) > 1000){
            togglePin(pin_Led);   //toggle led (RA2)
        
        //Espera 1s
        //while((uiCounterms - uiContadorTempo) < 500){}
        
        //atualiza contador de tempo
            uiContadorTempo = uiCounterms;
        }
    }    
}
