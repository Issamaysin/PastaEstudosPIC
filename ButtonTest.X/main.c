/*
 * File:            main.c
 * Author:          Renato Pepe
 * Description:     Programa que mantem o LED aceso
 *                   enquanto o botão está pressionado
 * Controlador:     PIC16F630
 * Created on:      20 de Outubro de 2021, 14:42
 */

#include "CONFIG.h"
#include <pic16f630.h>

/* Definição dos pinos utilizados */
#define pin_Led 0
#define pin_Button 1 //pulled down

void main(void) {
    
    /* Seta o pino do LED como output e o resto como input */
    TRISC = 0b1111110; 
    
    while(1){
        
        if(PORTC & (1<<pin_Button)){ //Lê o valor do botão
            PORTC |= (1<<pin_Led); //Aciona LED
        }else{
            PORTC &= ~(1<<pin_Led); //Desliga LED
        }
    }
}
