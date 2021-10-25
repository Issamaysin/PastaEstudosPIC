/*
 * File:            main.c
 * Author:          Renato Pepe
 * Description:     Programa Hello World, pisca um LED
 *                   na porta GP0 da PIC10F200
 *
 * Created on 20 de Outubro de 2021, 14:42
 */


#include "newxc8_header.h"
#include <pic10f200.h>
#define _XTAL_FREQ 4000000

//Definição dos pinos utilizados
#define GP0 0

void main(void) {
    
    /* Seta o pino GP0 como output e deixa o resto como input*/
    TRIS = 0b111110;
    
    while(1){
        
        GPIO |= (1<<GP0);  //set gp0 bit to 1, turning led on
        __delay_ms(1000); 
        
        
        GPIO &= ~(1<<GP0); //set gpo bit to 0, turning led off
        __delay_ms(1000);
    }
    
}
