/*
 * File:   utils.h
 * Author: Renato Pepe
 * Description: Aquivo para defclarações de funções básicas
 * Created on 16 de Novembro de 2021
 */

#ifndef UTILS_H
#define	UTILS_H

//O que está escrito em cada display.


//Representa um digito do display de 7seg, nodulo de uma lista circular que representa
// o estado atual de cada display.
typedef struct Display{
    int pin; //pino que controla display
    int port; //port que display está ligado
    char data; //instrução do caracter que será mostrado no display  
}Display;

//lista que guarda os 4 elementos que representam os displays
Display *Display7seg4digitsVetor;
int indiceDisplay = 0;

//troca qual display está ligado para o proximo da lista, é chamada a cada 5ms pela interrupção do timer.
void shiftDisplays();

//Inicializa display, escreve portas e pinos no vetor de displays
void initDisplay();

//Escreve o char no display
void writeCharOnDisplay(char chCharacter, int iDisplay);


void setPin(int iPin, int iPort);
void clearPin(int iPin, int iPort);
void togglePin(int iPin, int iPort);


#endif

