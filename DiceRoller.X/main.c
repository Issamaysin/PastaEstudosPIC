/*
 * File:   main.c
 * Author: Renato Pepe
 * Description:     
 * Controlador:     
 * Created on 16 de novembro de 2021, 16:07
 */


#include "config.h"
#include <PIC16F687.h>
#include "utils.h"
/* Define dos pinos utilizados */




/* Variaveis globais */
//Timer counter, increments each milisecond 
unsigned long uiCounterms = 0;



/* *****************************************************************************/
 /* Method name:        my_isr_routine                                         */
 /* Method description: Rotina de interrupção ISR,                     l       */
 /* Input params:       n/a                                                    */
 /* Output params:      n/a                                                    */
 /* ****************************************************************************/
void __interrupt () my_isr_routine (void) {
    
   /* Modulo de interrupção do Timer0 */
    if(T0IF) // Timer flag has been triggered due to timer overflow
    {   
        T0IF = 0;     // Clear timer interrupt flag
        TMR0 = 133;     //Load the timer Value
        
        uiCounterms++;  //update global timer counter
    
        //Pra atualizar os displays:
        // 200Hz com interrup a cada 1ms: 
        //  a cada 5 interrupt (contador%5 == 0) troca pro outro display
    
    } 
}

void main(void) {
    
    /* 
     * Clock config:
     *  - SCS is internal oscilator
     *  - LTS  is not stable
     *  - HTS is stable   
     *  - OSTS is internal oscilator
     *  - IRCF at 8 MHz
    */
    OSCCON |= (1<<0);   
    OSCCON &= ~(1<<1);
    OSCCON |= (1<<2); 
    OSCCON &= ~(1<<3);   
    OSCCON |= (0b01110000); 
    
    
   /*
    *   Port Configuration for Timer0
    *   set timer0 reading external frequency with 16 prescaler and enables pullups
    *   set the TMR0 register at 131 to obtain the desired interruption time (1ms)
    *   enable global, peripherial, and timer0 interruptions
   */
    OPTION_REG = 0b00000011; 
    TMR0= 133;  
    // OPTION_REG = 0b0100011; 
    GIE=1;         
    PEIE=1;         
    T0IE=1;   
    INTE = 0; //disables ra2 interrupt
    T0IF = 0; //set interruption flag to 0.

    
    //TRISA = 0b100000; // set A5 to input -> button
    TRISB = 0x00; //set all port B pins as output
    TRISC = 0x00; //set all port C pins as output
    PORTB = 0b11100000; //set RB7~RB5 as high and RB4 as low
    PORTC = 0b11111111;  //turn on all segments.
    
    //contador local de tempo
    unsigned long uiContadorTempo = 0;

    char text[6];
    text[0] = 0b01110111; //A
    text[1] = 0b01111100; //b
    text[2] = 0b00111001; //C
    text[3] = 0b01011110; //d
    text[4] = 0b01111001; //E
    text[5] = 0b01110001; //F
    
    //char buttonStatus = 0;
    int indice = 0;
    PORTC = text[indice];
    indice++;
    
    while(1){
      
        //Checa se o contador global ultrapassou 1000ms do local.
        if((uiCounterms - uiContadorTempo) > 1000 ){
            PORTC = text[indice];
            indice++;
            if(indice > 5){
                indice = 0;
            }
            uiContadorTempo = uiCounterms; //atualiza contador local
        }
    }
        
        //end
}



