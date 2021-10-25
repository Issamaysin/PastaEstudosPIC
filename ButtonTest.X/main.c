/*
 * File:            main.c
 * Author:          Renato Pepe
 * Description:     Programa que liga/desliga (toggle) o LED quando o botão
 *                   é apertado
 * Controlador:     PIC16F630
 * Created on:      20 de Outubro de 2021, 14:42
 */

#include "CONFIG.h"
#include <pic16f630.h>

//Frequencia do clock
#define _XTAL_FREQ 4000000

/* Definição dos pinos utilizados */
#define pin_Led 0
#define pin_Button 1 //pulled down



 /* *****************************************************************************/
 /* Method name:        readButton                                              */
 /* Method description: Lê o botão do pino desejado da porta C                  */
 /* Input params:       int iPinButton: pin onde o botão esta conectado         */
 /* Output params:      char: 0 -> não pressionado , 1 -> pressionado           */
 /* *****************************************************************************/
char readButton(int iPinButton);


void main(void) {
    /* Seta o pino do LED como output e o resto como input */
    TRISC = 0b1111110; 
    
    /* Variaveis para guardar o estado do botão */
    char cButtonPreviousStatus = 0;
    char cReadButtonBuffer = 0;
  
    /*inicia com LED desligado */
    PORTC &= ~(1<<pin_Led); 
        
    while(1){
        /* salva a leitura do botao na variavel buffer */
        cReadButtonBuffer = readButton(pin_Button); 
        
        /* se ele foi apertado toggle o led */
        if(cReadButtonBuffer != cButtonPreviousStatus && cReadButtonBuffer){ 
            PORTC ^= (1<<pin_Led);                      //toggle led
            __delay_ms(10);                             //espera tempo de debounce
            cButtonPreviousStatus = cReadButtonBuffer;  //atualiza status do botão
        
        /* se foi desapertado apenas atualiza o status */
        }else if(cReadButtonBuffer != cButtonPreviousStatus && !cReadButtonBuffer){ 
            cButtonPreviousStatus = cReadButtonBuffer; //atualiza status do botão
        }   
    }
}


char readButton(int iPinButton){
    /*
     * Retorna o valor lido no pino desejado da porta C se ele está entre
     *  os valor 0 e 5 (RC0~RC5)
    */
    if(0 <= iPinButton && 5 >= iPinButton){
        return (PORTC & (1<<iPinButton))>>iPinButton;
    }else{
        return 0x00;
    }
}