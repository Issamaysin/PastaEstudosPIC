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

unsigned long randomSeed = 0;

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
            readButtonStatus[0] = (PORTA & (1<<pinBotao1))>>pinBotao1; 
            readButtonStatus[1] = (PORTA & (1<<pinBotao2))>>pinBotao2;
            readButtonStatus[2] = (PORTA & (1<<pinBotao3))>>pinBotao3;
            readButtonStatus[3] = (PORTA & (1<<pinBotao4))>>pinBotao4;
            readButtonStatus[4] = (PORTA & (1<<pinBotao5))>>pinBotao5;
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
    

     while(1){
         
           if(0 == (uiCounterms%5)){
                shiftDisplays();
            }
            if((readButtonStatus[0] != Botoes[0].status) && readButtonStatus[0] == 0){
                randomSeed = uiCounterms + 47;
                Botoes[0].status = readButtonStatus[0];
                break;
            }else if((readButtonStatus[0] != Botoes[0].status) && readButtonStatus[0] == 1){
                Botoes[0].status = readButtonStatus[0];
            }
     }
     
   randomNumber();
   randomNumber();
     
      while(1){
        
        
        //Chama função de atualizar os displays a cada 5ms, (com 4 displays = 50Hz)
        if(0 == (uiCounterms%5)){
            shiftDisplays();
        }
        
        int i;
        //Checa se algum botão foi lido e chama a função necessária para a operação do botão.
        for (i = 0; i < 5; i++){
            
            if((readButtonStatus[i] != Botoes[i].status) && readButtonStatus[i] == 0){
            
                deviceStateMachine(i + 1);
            
                Botoes[i].status = readButtonStatus[i];
            }else if((readButtonStatus[i] != Botoes[i].status) && readButtonStatus[i] == 1){
                Botoes[i].status = readButtonStatus[i];
            }
            
        }
    }
   

}

