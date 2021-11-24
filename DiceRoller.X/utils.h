/*
 * File:   utils.h
 * Author: Renato Pepe
 * Description: Aquivo para defclara��es de fun��es e data types do programa
 * Created on 16 de Novembro de 2021
 */

#ifndef UTILS_H
#define	UTILS_H

/****** Defines e types ******/
/*
 * Estados do dispositivo. ROLL: Usu�rio est� rolando o dado
 *                         MENU: Usu�rio est� escolhendo os dados
 */
typedef enum state { ROLL, MENU} state;

/*
 * Representa um digito do display de 7seg, contem o pino no qual o display est� conectado
 *  e o dado do caracter que ele deve mostrar.
 */
typedef struct Display{
    unsigned char pin; //pino que controla display
    unsigned char data; //instru��o do caracter que ser� mostrado no display  
}Display;

/*
 * Representa um botao, contem o pino no qual est� conetado e o status.
 *  obs: status = 1 significa que o bot�o n�o est� apertado, pois os bot�es
 *      est�o conetados utilizando o built in pull-up do controlador
 */
typedef struct Button {
    unsigned char pin;     //pino que o botao esta conectado
    unsigned char status; //status da ultima leitura do botao 
}Button;



/****** Variaveis globais ******/
//vetor que representa os 4 dos displays
Display Display7seg4digitsVetor[4];

//Vetor que representa os 5 botoes do dispositivo.
Button Botoes[5];

/* Estado do dispositivo. 
  * MENU: player v� e pode trocar os valores da jogada com bot�es 2~5,
           botao 1 troca estado para ROLL e faz uma aposta.
  * ROLL: player v� o valor da ultima jogada e pode continuar jogando com botao 1
           botoes 2~5 apenas retornam o estado para MENU
*/
state deviceCurrentState = MENU;

/*
 * Estado dos dados, o primeiro elemento representa o numero de dados que ser�o jogados [1,9]
 *  o segundo elemento representa o dado que ser� rolado (2, 3, 4, 5, 6, 8, 10, 12, 20)
 */
unsigned char diceState[2] = {1,6};  
  
  
/****** Fun��es ******/

 /********************************************************************************************/
 /* Method name:        shiftDisplays                                                        */
 /* Method description: Atualiza os displays de 7 segs. Desliga o display que estava         */
 /*                      ligado anteriormente, escreve o dado do character na porta de dados */
 /*                      e liga o display atual. � chamada a cada 5ms, com 4 displays        */
 /*                      resulta em uma taxa de 50Hz                                         */
 /* Input params:       n/a                                                                  */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void shiftDisplays();

 /********************************************************************************************/
 /* Method name:        initDisplays                                                         */
 /* Method description: Inicializa a variavel global que representa os 4 digitos do display  */
 /* Input params:       n/a                                                                  */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void initDisplay();

 /****************************************************************************************************************/
 /* Method name:        writeCharOnDisplay                                                                       */
 /* Method description: Escreve o caracter desejado no display desejado. O caracter precisa pertencer a [0,9]    */
 /*                      ou ser a letra 'd', e os displays s�o representados de [0,3]. Fun��o apenas atualiza    */
 /*                      o dado na variavel do display, o digito apenas ser� mudado no mostrador quando a fun��o */
 /*                      shiftDisplays() completar um ciclo                                                      */
 /* Input params:       ucCharacter:   Caracter a ser escrito                                                    */
 /*                     ucDisplay: Display onde o caracter ser� mostrado. displays 1~4 -> input 0~3              */
 /* Output params:      n/a                                                                                      */
 /* **************************************************************************************************************/
void writeCharOnDisplay(unsigned char ucCharacter, unsigned char ucDisplay);

 /****************************************************************************************************** */
 /* Method name:        initButtons                                                                      */
 /* Method description: Inicializa o vetor que representa os 5 botoes, escreve os pinos e status inicial */
 /* Input params:       n/a                                                                              */
 /* Output params:      n/a                                                                              */
 /* ******************************************************************************************************/
void initButtons();

 /************************************************************************************** */
 /* Method name:        configBoard                                                      */
 /* Method description: Faz todas as configura��es necess�rias do controlador para que o */
 /*                      programa funcione, mais detalhes em cada bloco dentro da funcao */
 /* Input params:       n/a                                                              */
 /* Output params:      n/a                                                              */
 /* **************************************************************************************/
void configBoard();


 /****************************************************************************************** */
 /* Method name:        setPin                                                               */
 /* Method description: Muda para 1 (HIGH) o pino passado de parametro na porta especificada */
 /* Input params:       ucPin: Pino que mudar� para high                                     */
 /*                     ucPort: Porta onde est� esse pino                                    */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
void setPin(unsigned char ucPin, unsigned char ucPort);

 /***************************************************************************************** */
 /* Method name:        clearPin                                                            */
 /* Method description: Muda para 0 (LOW) o pino passado de parametro na porta especificada */
 /* Input params:       ucPin: Pino que mudar� para low                                     */
 /*                     ucPort: Porta onde est� esse pino                                   */
 /* Output params:      n/a                                                                 */
 /* *****************************************************************************************/
void clearPin(unsigned char ucPin, unsigned char ucPort);


 /********************************************************************************** */
 /* Method name:        deviceStateMachine                                           */
 /* Method description: Funcao que responde ao pressionamento dos bot�es.            */
 /*                       -Botao 1: Faz a rolagem dos dados                          */
 /*                       -Bot�o 2: Aumenta o numero de dados                        */
 /*                       -Botao 3: Diminui o numero de dados                        */
 /*                       -Botao 4: Aumenta o numero de lados do dado                */
 /*                       -Botao 5: Diminui o numero de lados do dado                */
 /*                     Alterna entre estados MENU, onde os dados sao selecionados e */
 /*                      ROLL, onde os dados sao rolados                             */
 /* Input params:       ucButton: Bot�o que foi apertado [1,5]                       */
 /* Output params:      n/a                                                          */
 /* **********************************************************************************/
void deviceStateMachine(unsigned char ucButton);

 /**************************************************************************** */
 /* Method name:        randomNumber                                           */
 /* Method description: Gerador de numeros aleat�rios                          */
 /* Input params:       n/a                                                    */
 /* Output params:      unsgined long: Numero aleatorio                        */
 /* ****************************************************************************/
unsigned long randomNumber();

 /*******************************************************************************/
 /* Method name:        rollDice                                                */
 /* Method description: Rola os dados que est�o selecionados no estado do dados */
 /*                      e escreve o resultado no display                       */
 /* Input params:       n/a                                                     */
 /* Output params:      n/a                                                     */
 /* *****************************************************************************/
void rollDice();

#endif
