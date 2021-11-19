/*
 * File:   main.c
 * Author: Renato Pepe
 * Description:  Dice Roller gadget: dispositivo com 5 botoes e um display
 *                  de 7 segmentos e 4 digitos, controlados por uma PIC16F687,
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

//Qual indice está aceso no momento (ver função shiftDisplays())
int indiceDisplay = 0; 

//Tempo que o leitor de botão fica em cooldown para evitar debounce bugs
unsigned long uiButtonDebounce = 0;

//guarda o estado dos botoes, é atualizado chamando a leitura dos botoes na interrupção
// e é usado no loop para comparar com o estado anterior dos botoes
unsigned char readButtonStatus[5] = {1, 1, 1, 1, 1};

/* *****************************************************************************/
 /* Method name:        my_isr_routine                                         */
 /* Method description: Rotina de interrupção ISR, trata do timer0 e botoes    */
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

    } 
    
    //buttons interruption
    if(RABIF){
        //Só chama esse bloco a cada 20ms
        if(uiCounterms - uiButtonDebounce > 19){
            //Atualiza status atual dos botões com a lida do pin
            readButtonStatus[0] = (PORTB & (1<<pinBotao1))>>pinBotao1; 
            readButtonStatus[1] = (PORTB & (1<<pinBotao2))>>pinBotao2;
            readButtonStatus[2] = (PORTB & (1<<pinBotao3))>>pinBotao3;
            readButtonStatus[3] = (PORTA & (1<<pinBotao4))>>pinBotao4;
            readButtonStatus[4] = (PORTB & (1<<pinBotao5))>>pinBotao5;

            //reseta contador
            uiButtonDebounce = uiCounterms;
        }
        
        RABIF = 0; //obs: flag precisa ser limpa depois do read na port A
    }
}

void main(void) {
    
    //Faz a configuração inicial do controlador
    configBoard();
   
    //Inicializa vetores que representam os displays e botoes.
    initDisplay();
    initButtons();
    
    //Escreve pra testes, tirar daqui dps
    writeCharOnDisplay('1', 0);
    writeCharOnDisplay('d', 1);
    writeCharOnDisplay('0', 2);
    writeCharOnDisplay('6', 3);
 
    
    
    while(1){
        
        
        //Chama função de atualizar os displays a cada 5ms, (com 4 displays = 50Hz)
        if(0 == (uiCounterms%5)){
            shiftDisplays();
        }
        
       
     
        //Checa se algum botão foi lido e chama a função necessária para a operação do botão.
        
        /*
         * Botão 1: Rola o dado. Independentemente do estado atual este botão
         *           vai rolar o dado, e entrar o programa no estado ROLL
        */
        if((readButtonStatus[0] != Botoes[0].status) && readButtonStatus[0] == 0){
            writeCharOnDisplay('d', 2);
            Botoes[0].status = readButtonStatus[0];
        }else if((readButtonStatus[0] != Botoes[0].status) && readButtonStatus[0] == 1){
            Botoes[0].status = readButtonStatus[0];
        }
        
        if((readButtonStatus[1] != Botoes[1].status) && readButtonStatus[1] == 0){
            writeCharOnDisplay('9', 2);
            Botoes[1].status = readButtonStatus[1];
        }else if((readButtonStatus[1] != Botoes[1].status) && readButtonStatus[1] == 1){
            Botoes[1].status = readButtonStatus[1];
        }
        
        if((readButtonStatus[2] != Botoes[2].status) && readButtonStatus[2] == 0){
            writeCharOnDisplay('0', 2);
            Botoes[2].status = readButtonStatus[2];
        }else if((readButtonStatus[2] != Botoes[2].status) && readButtonStatus[2] == 1){
            Botoes[2].status = readButtonStatus[2];
        }
        
        
        if((readButtonStatus[3] != Botoes[3].status) && readButtonStatus[3] == 0){
            writeCharOnDisplay('6', 2);
            Botoes[3].status = readButtonStatus[3];
        }else if((readButtonStatus[0] != Botoes[3].status) && readButtonStatus[3] == 1){
            Botoes[3].status = readButtonStatus[3];
        }
        
        if((readButtonStatus[4] != Botoes[4].status) && readButtonStatus[4] == 0){
            writeCharOnDisplay('8', 2);
            Botoes[4].status = readButtonStatus[4];
        }else if((readButtonStatus[4] != Botoes[4].status) && readButtonStatus[4] == 1){
            Botoes[4].status = readButtonStatus[4];
        }
        
       
        
      
    }
        
        //end
}







