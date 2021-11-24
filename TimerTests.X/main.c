/*
 * File:   main.c
 * Author: Renato Pepe
 * Description:     Test dos módulos timer0 e timer2
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
 /* Method description: Rotina de interrupção ISR,                     l       */
 /* Input params:       n/a                                                    */
 /* Output params:      n/a                                                    */
 /* ****************************************************************************/
void __interrupt () my_isr_routine (void) {
    
    /* Modulo de interrupção do Timer0 */
    if(TMR0IF) // Timer flag has been triggered due to timer overflow
    {   
        TMR0 = 131+2;     //Load the timer Value
        TMR0IF = 0;     // Clear timer interrupt flag
        uiCounterms++;  //update global timer counter
    } 
    
    /* Modulo de interrupcao do Timer2 */
    if(TMR2IF){
        TMR2IF = 0;          //clear interrupt flag (TMR2 is cleared auto)
        uiCountermsTimer2++; //increase counter
    }
    
}

void main(void) {
    
    /* 
     * Clock config: 16Mhz at FOSC determined clock
    */
    OSCCON = 0b1111100;
    
   /*
    * Port Configuration for Timer0
    *   set timer0 reading external frequency with 32 prescaler and enables pullups
    *   set the TMR0 register at 133 to obtain the desired interruption time (1ms)
    *   enable global, peripherial, and timer0 interruptions
    */
    OPTION_REG = 0b0000100;  
    TMR0=131+2;      
    GIE=1;         
    PEIE=1;         
    TMR0IE=1;      

    
    /*
     * Port Configuration for Timer 2
     *  enble timer2 interruptions
     *  set timer2 postscaler as 8, prescaler as 4, and turn timer ON
     *  PR2 is set at 125 to obtain a interruption each 1ms
     */
    TMR2IE = 1;     
    T2CON = 0b00111101;  
    PR2 = 125; 
    
    /* 
     * Port configuration for inputs/outputs
     *  turn off ADC settings, set pins RA2 and RA0 to outputs
     *  clear PortA
     */
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
