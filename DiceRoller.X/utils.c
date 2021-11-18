/*
 * File:   utils.c
 * Author: Renato Pepe
 * Description: Aquivo para definições de funções básicas.
 * Created on 16 de Novembro de 2021
 */

#include <xc.h>
#include <PIC16F687.h>
#include "board.h"
#include "utils.h"

//set input pin as high on port
void setPin(int iPin, int iPort){
    
    /*  Liga o bit correspondente aos pino e porta passados por parametro */
    switch(iPort){
        case PORT_A:
            if(iPin >= 0 && iPin <= 5){
                PORTA |= (1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(iPin >= 4 && iPin <= 7){
                PORTB |= (1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(iPin >= 0 && iPin <= 7){
                PORTC |= (1<<iPin);
            }else{
                return;
            }
            break;
        default:
            return;
            break;
    }
    
}
//clear pin
void clearPin(int iPin, int iPort){
     
    /*  Desliga o bit correspondente aos pino e porta passados por parametro */
    switch(iPort){
        case PORT_A:
            if(iPin >= 0 && iPin <= 5){
                PORTA &= ~(1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(iPin >= 4 && iPin <= 7){
                PORTB &= ~(1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(iPin >= 0 && iPin <= 7){
                PORTC &= ~(1<<iPin);
            }else{
                return;
            }
            break;
        default:
            return;
            break;
    }
}


//toogle pin
void togglePin(int iPin, int iPort){
 /*  Toggle o bit correspondente aos pino e porta passados por parametro */
    switch(iPort){
        case PORT_A:
            if(iPin >= 0 && iPin <= 5){
                PORTA ^= (1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(iPin >= 4 && iPin <= 7){
                 
                PORTB ^= (1<<iPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(iPin >= 0 && iPin <= 7){
                PORTC ^= (1<<iPin);
            }else{
                return;
            }
            break;
        default:
            return;
            break;
    }
}

void shiftDisplays(){
    
    //desliga display que está ligado atualmente
    setPin((Display7seg4digitsVetor+indiceDisplay)->pin, (Display7seg4digitsVetor+indiceDisplay)->port);
    
    //atualiza qual display está em execução
    if(++indiceDisplay > 3){
        indiceDisplay = 0;
    }
    
    //escreve o caracter na porta C (dados dos displays).
    PORTC = (Display7seg4digitsVetor+indiceDisplay)->data;
    
    //liga display
    clearPin((Display7seg4digitsVetor+indiceDisplay)->pin, (Display7seg4digitsVetor+indiceDisplay)->port);
}
    
    
   
void initDisplay(){
        
    Display7seg4digitsVetor[0].data = 0b01110111;
    Display7seg4digitsVetor[0].pin = pinDisplay1;
    Display7seg4digitsVetor[0].port = portDisplay1;
    
    Display7seg4digitsVetor[1].data = 0b01111100;
    Display7seg4digitsVetor[1].pin = pinDisplay2;
    Display7seg4digitsVetor[1].port = portDisplay2;
      
    Display7seg4digitsVetor[2].data = 0b00111111;
    Display7seg4digitsVetor[2].pin = pinDisplay3;
    Display7seg4digitsVetor[2].port = portDisplay3;
      
    Display7seg4digitsVetor[3].data = 0b00000110;
    Display7seg4digitsVetor[3].pin = pinDisplay4;
    Display7seg4digitsVetor[3].port = portDisplay4;
}

void writeCharOnDisplay(char chCharacter, int iDisplay){
    /* End method if display is not [0,3] */
    if(iDisplay < 0 || iDisplay > 3){
        return;
    }
    
    /* 
     * Writes the character on the respective display
     *  will write 'A' if no character matches for debugging 
     */
    switch(chCharacter){
        case '0':
            Display7seg4digitsVetor[iDisplay].data = 0b00111111;
            break;
        case '1':
            Display7seg4digitsVetor[iDisplay].data = 0b00000110;
            break;
        case '2':
            Display7seg4digitsVetor[iDisplay].data = 0b01011011;
            break;
        case '3':
            Display7seg4digitsVetor[iDisplay].data = 0b01001111;
            break;
        case '4':
            Display7seg4digitsVetor[iDisplay].data = 0b01100110;
            break;
        case '5':
            Display7seg4digitsVetor[iDisplay].data = 0b01101101;
            break;
        case '6':
            Display7seg4digitsVetor[iDisplay].data = 0b01111101;
            break;
        case '7':
            Display7seg4digitsVetor[iDisplay].data = 0b01000111;
            break;
        case'8':
            Display7seg4digitsVetor[iDisplay].data = 0b01111111;
            break;
        case '9':
            Display7seg4digitsVetor[iDisplay].data = 0b01100111;
            break;
        case 'd':
            Display7seg4digitsVetor[iDisplay].data = 0b01011110;
            break;
        default:
            Display7seg4digitsVetor[iDisplay].data = 0b01110111;
            break;
    } 
}



