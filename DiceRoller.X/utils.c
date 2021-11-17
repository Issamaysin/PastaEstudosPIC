/*
 * File:   utils.c
 * Author: User
 *
 * Created on 16 de Novembro de 2021, 17:09
 */

#include <xc.h>
#include <PIC16F687.h>
#include "utils.h"
//set input pin as high (on portA)
void setPin(int iPin){
    
    //switch com portas A, B, C
    // A -> botoes
    // B -> digito 7 seg
    // C -> caracter 7 seg
    
    if(0 <= iPin && 5 >= iPin){ //placa só tem pins RA0~RA5
        PORTA |= (1<<iPin);
    }
}
//clear pin
void clearPin(int iPin){
    if(0 <= iPin && 5 >= iPin){
        PORTA &= ~(1<<iPin);
    }
}
//toogle pin
void togglePin(int iPin){
    if(0 <= iPin && 5 >= iPin){
        PORTA ^= (1<<iPin);
    }
}
