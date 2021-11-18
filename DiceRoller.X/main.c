/*
 * File:   main.c
 * Author: Renato Pepe
 * Description:  Dice Roller gadget: dispositivo com 5 botoes e um display
 *                  de 7 segmentos de 4 digitos, controlados por uma PIC16F687,
 *                  que emula digitalmente uma jogada de dados, range de 1d2 até 9d20.   
 * Controlador:  PIC16F687
 * Created on 16 de novembro de 2021
 */

/* Includes */
#include "config.h"
#include <PIC16F687.h>
#include "board.h"
#include "utils.h"




/* Variaveis globais */
//Timer counter, incrementa a cada milisegundo
unsigned long uiCounterms = 0;

/* *****************************************************************************/
 /* Method name:        my_isr_routine                                         */
 /* Method description: Rotina de interrupção ISR, trata do timer0             */
 /* Input params:       n/a                                                    */
 /* Output params:      n/a                                                    */
 /* ****************************************************************************/
void __interrupt () my_isr_routine (void) {
    
   /* Modulo de interrupção do Timer0 */
    if(T0IF) // Timer flag triggered
    {   
        T0IF = 0;      // Clear interrupt flag
        TMR0 = 133;    //Carrega o valor para resetar o timer.
        
        uiCounterms++; //atualiza contador global de tempo
    
        //Chama função de atualizar os displays a cada 5ms, (com 4 displays = 50Hz)
        if(0 == (uiCounterms%5)){
            shiftDisplays();
        }
    } 
    
    //add buttons interrupt
}

void configBoard();


void main(void) {
    
    configBoard();
   
    //inicializa valores nos pinos de output
    PORTB = 0b11100000; //set RB7~RB6 and RB4 as high (display off)
    PORTA = 0b100000; //RA5 turned on (display is off)
    PORTC = 0x00;  //turn off all segments.
    
    
    //Cria e inicializa vetor que representa o display de 7 segmentos e 4 digitos
    Display display7seg[4];
    Display7seg4digitsVetor = display7seg;
    initDisplay();

    
    writeCharOnDisplay('4', 0);
    writeCharOnDisplay('d', 1);
    writeCharOnDisplay('9', 2);
    writeCharOnDisplay('p', 3);
    
    while(1){
      
       
    }
        
        //end
}

// Faz a configuração das portas e pinos, timer, clock...
void configBoard(){
    
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
    *   set the TMR0 register at 133 to obtain the desired interruption time (1ms)
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

    //Seta os pinos dos botoes como input e os demais como output
    TRISA = 0b010111; // set A5 to input -> button
    TRISB = 0b00100000; //set all port B pins, but RB5, as output
    TRISC = 0x00; //set all port C pins as output
    
}







