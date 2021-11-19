/*
 * File:   utils.h
 * Author: Renato Pepe
 * Description: Aquivo para defclarações de funções básicas
 * Created on 16 de Novembro de 2021
 */

#ifndef UTILS_H
#define	UTILS_H


typedef enum state { ROLL, MENU} state;



/*
 * Defines e types.
 */

//Representa um digito do display de 7seg, nodulo de uma lista circular que representa
// o estado atual de cada display.
typedef struct Display{
    unsigned char pin; //pino que controla display
    unsigned char port; //port que display está ligado
    unsigned char data; //instrução do caracter que será mostrado no display  
}Display;

//Representa um botao.
typedef struct Button {
    unsigned char pin;     //pino que o botao esta conectado
    unsigned char port;    //port que o botao esta conectado
    unsigned char status; //status da ultima leitura do botao (0 = off)
}Button;



/*
 * Variaveis globais
 */
//vetor que representa os 4 dos displays
Display Display7seg4digitsVetor[4];

//Vetor que representa os 5 botoes do dispositivo.
Button Botoes[5];

/* Estado do dispositivo. 
  * MENU: player vê e pode trocar os valores da jogada com botões 2~5,
           botao 1 troca estado para ROLL e faz uma aposta.
  * ROLL: player vê o valor da ultima jogada e pode continuar jogando com botao 1
           botoes 2~5 apenas retornam o estado para MENU
*/
state deviceCurrentState = MENU;

/*
 * Estado dos dados, o primeiro elemento representa o numero de dados que serão jogados [1,9]
 *  o segundo elemento representa o dado que será rolado (2, 3, 4, 5, 6, 8, 10, 12, 20)
 */
unsigned char diceState[2] = {1,6};  
  
  
/*
 * Funções
 */

//troca qual display está ligado para o proximo da lista, é chamada a cada 5ms pela interrupção do timer.
void shiftDisplays();

//Inicializa display, escreve portas e pinos no vetor de displays
void initDisplay();

//Escreve o char no display [0,3]
void writeCharOnDisplay(unsigned char ucCharacter, unsigned char ucDisplay);

void initButtons();

void configBoard();

void setPin(unsigned char ucPin, unsigned char ucPort);
void clearPin(unsigned char ucPin, unsigned char ucPort);
void togglePin(unsigned char ucPin, unsigned char ucPort);



#endif

