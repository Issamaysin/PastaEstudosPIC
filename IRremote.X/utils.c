#include <xc.h>
#include <PIC12F1822.h>
#include "utils.h"

//set input pin as high (on portA)
void setPin(int iPin){
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

