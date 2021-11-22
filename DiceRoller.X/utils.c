/*
 * File:   utils.c
 * Author: Renato Pepe
 * Description: Aquivo para definições de funções do programa
 * Created on 16 de Novembro de 2021
 */

#include <xc.h>
#include <PIC16F687.h>
#include "board.h"
#include "utils.h"

/****** Variaveis globais ******/
extern int indiceDisplay;
extern unsigned long randomSeed;

 /********************************************************************************************/
 /* Method name:        shiftDisplays                                                        */
 /* Method description: Atualiza os displays de 7 segs. Desliga o display que estava         */
 /*                      ligado anteriormente, escreve o dado do character na porta de dados */
 /*                      e liga o display atual. É chamada a cada 5ms, com 4 displays        */
 /*                      resulta em uma taxa de 50Hz                                         */
 /* Input params:       n/a                                                                  */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void shiftDisplays(){
    
    //desliga display que está ligado atualmente
    setPin(Display7seg4digitsVetor[indiceDisplay].pin, portDisplay);
    
    //atualiza qual display está em execução
    if(++indiceDisplay > 3){
        indiceDisplay = 0;
    }
    
    //escreve o caracter na porta C (dados dos displays).
    PORTC = (Display7seg4digitsVetor[indiceDisplay].data);
    
    //liga display atual
    clearPin(Display7seg4digitsVetor[indiceDisplay].pin, portDisplay);
}

 /********************************************************************************************/
 /* Method name:        initDisplays                                                         */
 /* Method description: Inicializa a variavel global que representa os 4 digitos do display  */
 /* Input params:       n/a                                                                  */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void initDisplay(){
        
    //Inicializa os pinos dos displays, já com os dados para mostrar 1d06
    Display7seg4digitsVetor[0].data = 0b00000110;
    Display7seg4digitsVetor[0].pin = pinDisplay1;
    
    Display7seg4digitsVetor[1].data = 0b01011110;
    Display7seg4digitsVetor[1].pin = pinDisplay2;
      
    Display7seg4digitsVetor[2].data = 0b00111111;
    Display7seg4digitsVetor[2].pin = pinDisplay3;
      
    Display7seg4digitsVetor[3].data = 0b01111101;
    Display7seg4digitsVetor[3].pin = pinDisplay4;
}

 /****************************************************************************************************************/
 /* Method name:        writeCharOnDisplay                                                                       */
 /* Method description: Escreve o caracter desejado no display desejado. O caracter precisa pertencer a [0,9]    */
 /*                      ou ser a letra 'd', e os displays são representados de [0,3]. Função apenas atualiza    */
 /*                      o dado na variavel do display, o digito apenas será mudado no mostrador quando a função */
 /*                      shiftDisplays() completar um ciclo                                                      */
 /* Input params:       ucCharacter:   Caracter a ser escrito                                                    */
 /*                     ucDisplay: Display onde o caracter será mostrado. displays 1~4 -> input 0~3              */
 /* Output params:      n/a                                                                                      */
 /* **************************************************************************************************************/
void writeCharOnDisplay(unsigned char ucCharacter, unsigned char ucDisplay){
    
    //Escreve o código do caracter desejado no dado do display desejado
    switch(ucCharacter){
        case '0':
            Display7seg4digitsVetor[ucDisplay].data = 0b00111111;
            break;
        case '1':
            Display7seg4digitsVetor[ucDisplay].data = 0b00000110;
            break;
        case '2':
            Display7seg4digitsVetor[ucDisplay].data = 0b01011011;
            break;
        case '3':
            Display7seg4digitsVetor[ucDisplay].data = 0b01001111;
            break;
        case '4':
            Display7seg4digitsVetor[ucDisplay].data = 0b01100110;
            break;
        case '5':
            Display7seg4digitsVetor[ucDisplay].data = 0b01101101;
            break;
        case '6':
            Display7seg4digitsVetor[ucDisplay].data = 0b01111101;
            break;
        case '7':
            Display7seg4digitsVetor[ucDisplay].data = 0b00000111;
            break;
        case'8':
            Display7seg4digitsVetor[ucDisplay].data = 0b01111111;
            break;
        case '9':
            Display7seg4digitsVetor[ucDisplay].data = 0b01100111;
            break;
        case 'd':
            Display7seg4digitsVetor[ucDisplay].data = 0b01011110;
            break;
    } 
}


 /****************************************************************************************************** */
 /* Method name:        initButtons                                                                      */
 /* Method description: Inicializa o vetor que representa os 5 botoes, escreve os pinos e status inicial */
 /* Input params:       n/a                                                                              */
 /* Output params:      n/a                                                                              */
 /* ******************************************************************************************************/
void initButtons(){
    Botoes[0].pin = pinBotao1;
    Botoes[0].status = 1;
    
    Botoes[1].pin = pinBotao2;
    Botoes[1].status = 1;
    
    Botoes[2].pin = pinBotao3;
    Botoes[2].status = 1;
    
    Botoes[3].pin = pinBotao4;
    Botoes[3].status = 1;
    
    Botoes[4].pin = pinBotao5;
    Botoes[4].status = 1;
     
}


/************************************************************************************** */
 /* Method name:        configBoard                                                      */
 /* Method description: Faz todas as configurações necessárias do controlador para que o */
 /*                      programa funcione, mais detalhes em cada bloco dentro da funcao */
 /* Input params:       n/a                                                              */
 /* Output params:      n/a                                                              */
 /* **************************************************************************************/
void configBoard(){
    
    /* 
     * Clock config:
     *  - SCS is internal oscilator
     *  - LTS  is not stable
     *  - HTS is stable   
     *  - OSTS is internal oscilator
     *  - IRCF at 8 MHz
    */
    OSCCON |= (1<<0);   
    OSCCON &= ~(1<<1);
    OSCCON |= (1<<2); 
    OSCCON &= ~(1<<3);   
    OSCCON |= (0b01110000); 
    
    //Seta todos pinos do adc da porta A como i/o
    ANSEL = 0x00;
    
    //Seta os pinos dos botoes como input e os demais como output
    TRISA = 0b00110111;             //Botoes em RA0, RA1, RA2, RA4, RA5 como input
    TRISB = 0x00;                   //R4 ~ RB7 como output (controle display)
    TRISC = 0x00;                   //Todos como output, controla os leds.
    
    //Inicializa pinos da porta B como 0 para o display começar ligado
    PORTA = 0xff;
    PORTB = 0x00;
    PORTC = 0xff;

    //Habilida a possibilidade de pull-up nas portas A e B.
    nRABPU = 0;
    
    /*
     * Configurações para o timer 0.
     *  -Clock source -> clock interno
     *  -Prescaler está atrelado ao timer 0
     *  -Prescaler tem valor 16 (PS<0,2> = 0b011)
     */
    T0CS = 0;
    PSA = 0;   
    PS0 = 1;
    PS1 = 1;
    PS2 = 0;
    
    /*  Valor inicial do contador do timer 0.
     *   Com 8Mhz de clock, prescaler de 16, e TMR0 = 133 temos uma interrupção
     *   do timer a cada 1 milisegundo.
     */
    TMR0= 133;
    
    /* Configurações de interrupcao
     *  -Habilita flag global de interrupcao
     *  -Habilita flag de interrupcoes de perifericos
     *  -Habilita flag de interruocao do timer0
     *  -Habilita flag de interrupcao das portas A e B
     */
    GIE=1;         //global interruptions enabled
    PEIE=1;        //pheripherial interruptions enabled
    T0IE=1;        //timer0 interrup enabled 
    RABIE = 1;     //enables PORTA e PORTB interrupt on change.
    
    //Seta valor inicial das flags de interrupcoes
    T0IF = 0;      //set timer0 interruption flag to 0.
    RABIF = 0;     //set port interruption flag to 0.

    //Permite o pull-up nas portas dos botões
    WPUA = 0b111111;
    
    //Permite interrupcoes quando algum pino do botao mudar de estado
    IOCA = 0b00110111; 
    
}



 /****************************************************************************************** */
 /* Method name:        setPin                                                               */
 /* Method description: Muda para 1 (HIGH) o pino passado de parametro na porta especificada */
 /* Input params:       ucPin: Pino que mudará para high                                     */
 /*                     ucPort: Porta onde está esse pino                                    */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void setPin(unsigned char ucPin, unsigned char ucPort){

    /*  Liga o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
                PORTA |= (1<<ucPin);
            break;
        case PORT_B:
                PORTB |= (1<<ucPin);
            break;
        case PORT_C:
                PORTC |= (1<<ucPin);
            break;
        default:
            return;
            break;
    }
 
}

 /***************************************************************************************** */
 /* Method name:        clearPin                                                            */
 /* Method description: Muda para 0 (LOW) o pino passado de parametro na porta especificada */
 /* Input params:       ucPin: Pino que mudará para low                                     */
 /*                     ucPort: Porta onde está esse pino                                   */
 /* Output params:      n/a                                                                 */
 /* *****************************************************************************************/
void clearPin(unsigned char ucPin, unsigned char ucPort){
   /*  Desliga o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
                PORTA &= ~(1<<ucPin);
            break;
        case PORT_B:
                PORTB &= ~(1<<ucPin);
            break;
        case PORT_C:
                PORTC &= ~(1<<ucPin);
            break;
        default:
            return;
            break;
    }
}


 /***************************************************************************************** */
 /* Method name:        togglePin                                                           */
 /* Method description: Inverte o valor do pino passado de parametro na porta especificada  */
 /* Input params:       ucPin: Pino que terá o valor invertido                              */
 /*                     ucPort: Porta onde está esse pino                                   */
 /* Output params:      n/a                                                                 */
 /* *****************************************************************************************/
void togglePin(unsigned char ucPin, unsigned char ucPort){
     /*  Toggle o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
                PORTA ^= (1<<ucPin);
            break;
        case PORT_B:
                PORTB ^= (1<<ucPin);
            break;
        case PORT_C:
                PORTC ^= (1<<ucPin);
            break;
        default:
            return;
            break;
    }
}




 /********************************************************************************** */
 /* Method name:        deviceStateMachine                                           */
 /* Method description: Funcao que responde ao pressionamento dos botões.            */
 /*                       -Botao 1: Faz a rolagem dos dados                          */
 /*                       -Botão 2: Aumenta o numero de dados                        */
 /*                       -Botao 3: Diminui o numero de dados                        */
 /*                       -Botao 4: Aumenta o numero de lados do dado                */
 /*                       -Botao 5: Diminui o numero de lados do dado                */
 /*                     Alterna entre estados MENU, onde os dados sao selecionados e */
 /*                      ROLL, onde os dados sao rolados                             */
 /* Input params:       ucButton: Botão que foi apertado [1,5]                       */
 /* Output params:      n/a                                                          */
 /* **********************************************************************************/
void deviceStateMachine(unsigned char ucButton){
    
    //Se o primeiro botão foi pressionado: rola o dado e imprime o dado na tela, depois muda o estado para ROLL
    if(1 == ucButton){
        deviceCurrentState = ROLL;
        //Rola os dados
        rollDice();
        return; //Encera a funcao, já rolou o dado e imprimiu o valor no display
    }//Se outro botao foi pressionado e estava no estado ROLL, apenas muda para MENU
    else if (deviceCurrentState == ROLL){
        deviceCurrentState = MENU;
        //Print o XdYY na tela
        writeCharOnDisplay('0' + diceState[0], 0);
        writeCharOnDisplay('d', 1);
        writeCharOnDisplay('0' + diceState[1]/10, 2);
        writeCharOnDisplay('0' + diceState[1]%10, 3);
        return; //Encera a funcao, apenas muda o estado e atualiza display para mostrar os dados
    }
    
    
    
    switch(ucButton){
        case 2: //Aumenta o numero de dados jogados
            if(diceState[0] < 9 ){
                diceState[0]++;
            }
            break;
            
        case 3: //diminui o numero de dados jogados
            if(diceState[0] > 1){
                diceState[0]--;
            }
            break;
            
        case 4: //muda para um dado de mais lados
            if(diceState[1] < 20){
                switch(diceState[1]){
                    case 12:
                        diceState[1] = 20;
                        break;
                    case 10:
                        diceState[1] = 12;
                        break;
                    case 8:
                        diceState[1] = 10;
                        break;
                    case 6:
                        diceState[1] = 8;
                        break;
                    default:
                        diceState[1]++;
                        break;
                }
            }
            
            break;
        case 5: //muda para um dado de menos lados.
                
            if(diceState[1] > 2){
                switch(diceState[1]){
                    case 20:
                        diceState[1] = 12;
                        break;
                    case 12:
                        diceState[1] = 10;
                        break;
                    case 10:
                        diceState[1] = 8;
                        break;
                    case 8:
                        diceState[1] = 6;
                        break;
                    default:
                        diceState[1]--;
                        break;
                }
            }
            break;        
        default:
            break;
    }
        
        //Atualiza dados no display
        writeCharOnDisplay('0' + diceState[0], 0);
        writeCharOnDisplay('d', 1);
        writeCharOnDisplay('0' + diceState[1]/10, 2);
        writeCharOnDisplay('0' + diceState[1]%10, 3);
    
       
}


 /**************************************************************************** */
 /* Method name:        randomNumber                                           */
 /* Method description: Gerador de numeros aleatórios (DATA STILL UNDER TESTS) */
 /* Input params:       n/a                                                    */
 /* Output params:      unsgined long: Numero aleatorio                        */
 /* ****************************************************************************/
unsigned long randomNumber(){
    randomSeed = (37*randomSeed + 98)%1373;
    return randomSeed;
}



 /*******************************************************************************/
 /* Method name:        rollDice                                                */
 /* Method description: Rola os dados que estão selecionados no estado do dados */
 /*                      e escreve o resultado no display                       */
 /* Input params:       n/a                                                     */
 /* Output params:      n/a                                                     */
 /* *****************************************************************************/
void rollDice(){
    unsigned char i;
    unsigned int ulTotal = 0;
    //Rola os dados e soma o total
    for(i = 0; i < diceState[0]; i++){
        ulTotal += ((unsigned int)randomNumber())%diceState[1] + 1;
    }
    //Imprime o valor total da rolagem no display
    writeCharOnDisplay('0' + (unsigned char)(ulTotal%10) ,3);
    writeCharOnDisplay('0' + (unsigned char)((ulTotal/10)%10) ,2);
    writeCharOnDisplay('0' + (unsigned char)((ulTotal/100)%10) ,1);
    writeCharOnDisplay('0' + (unsigned char)((ulTotal/1000)%10) ,0);
}




