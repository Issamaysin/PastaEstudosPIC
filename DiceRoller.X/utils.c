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


extern int indiceDisplay;
extern unsigned long randomSeed;

//set input pin as high on port
void setPin(unsigned char ucPin, unsigned char ucPort){

    /*  Liga o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
            if(ucPin >= 0 && ucPin <= 5){
                PORTA |= (1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(ucPin >= 4 && ucPin <= 7){
                PORTB |= (1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(ucPin >= 0 && ucPin <= 7){
                PORTC |= (1<<ucPin);
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
void clearPin(unsigned char ucPin, unsigned char ucPort){
   /*  Desliga o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
            if(ucPin >= 0 && ucPin <= 5){
                PORTA &= ~(1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(ucPin >= 4 && ucPin <= 7){
                PORTB &= ~(1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(ucPin >= 0 && ucPin <= 7){
                PORTC &= ~(1<<ucPin);
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
void togglePin(unsigned char ucPin, unsigned char ucPort){
     /*  Toggle o bit correspondente aos pino e porta passados por parametro */
    switch(ucPort){
        case PORT_A:
            if(ucPin >= 0 && ucPin <= 5){
                PORTA ^= (1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_B:
             if(ucPin >= 4 && ucPin <= 7){
                PORTB ^= (1<<ucPin);
            }else{
                return;
            }
            break;
        case PORT_C:
             if(ucPin >= 0 && ucPin <= 7){
                PORTC ^= (1<<ucPin);
            }else{
                return;
            }
            break;
        default:
            return;
            break;
    }
}


    
//Inicializa display, escreve pins e portas no vetor de displays.
void initDisplay(){
        
    Display7seg4digitsVetor[0].data = 0x00;
    Display7seg4digitsVetor[0].pin = pinDisplay1;
    Display7seg4digitsVetor[0].port = portDisplay1;
    
    Display7seg4digitsVetor[1].data = 0x00;
    Display7seg4digitsVetor[1].pin = pinDisplay2;
    Display7seg4digitsVetor[1].port = portDisplay2;
      
    Display7seg4digitsVetor[2].data = 0x00;
    Display7seg4digitsVetor[2].pin = pinDisplay3;
    Display7seg4digitsVetor[2].port = portDisplay3;
      
    Display7seg4digitsVetor[3].data = 0x00;
    Display7seg4digitsVetor[3].pin = pinDisplay4;
    Display7seg4digitsVetor[3].port = portDisplay4;
}

//Inicializa os botões, escreve os pins e portas no vetor de botoes.
void initButtons(){
    Botoes[0].pin = pinBotao1;
    Botoes[0].port = portBotao1;
    Botoes[0].status = 1;
    
    Botoes[1].pin = pinBotao2;
    Botoes[1].port = portBotao2;
    Botoes[1].status = 1;
    
    Botoes[2].pin = pinBotao3;
    Botoes[2].port = portBotao3;
    Botoes[2].status = 1;
    
    Botoes[3].pin = pinBotao4;
    Botoes[3].port = portBotao4;
    Botoes[3].status = 1;
    
    Botoes[4].pin = pinBotao5;
    Botoes[4].port = portBotao5;
    Botoes[4].status = 1;
     
}



void shiftDisplays(){
    
    //desliga display que está ligado atualmente
    setPin(Display7seg4digitsVetor[indiceDisplay].pin, Display7seg4digitsVetor[indiceDisplay].port);
    
    indiceDisplay++; 
    
    //atualiza qual display está em execução
    if(indiceDisplay > 3){
        indiceDisplay = 0;
    }
    
    //escreve o caracter na porta C (dados dos displays).
    PORTC = (Display7seg4digitsVetor[indiceDisplay].data);
    
    //liga display
    clearPin(Display7seg4digitsVetor[indiceDisplay].pin, Display7seg4digitsVetor[indiceDisplay].port);
    
    
    //Obs: dispay 1 aparenta ter 1 bug:
    //  ao dar clear no bit de um outro display, mesmo que em outra PORT, o display1 liga
    //  testei exaustivamente as funçoes clear e set, mas só consegui resolver ligando/desligando forçadamente o display1.
    if(0 != indiceDisplay){
        //PORTA |= (1<<0);
        setPin(pinDisplay1, portDisplay1);
    }else{
        clearPin(pinDisplay1, portDisplay1);
        //PORTA &= ~(1<<0);
    }
     
     
}
    



void writeCharOnDisplay(unsigned char ucCharacter, unsigned char ucDisplay){
    /* End method if display is not [0,3] */
    if(ucDisplay < 0 || ucDisplay > 3){
        return;
    }
    
    /* 
     * Writes the character on the respective display
     *  will write 'A' if no character matches for debugging 
     */
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
        default:
            Display7seg4digitsVetor[ucDisplay].data = 0b01110111;
            break;
    } 
}



// Faz a configuração das portas e pinos, timer, clock...
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
    
    //Seta todos pinos do adc como i/o
    ANSEL = 0x00;
    ANSELH = 0x00;
    //Seta os pinos dos botoes como input e os demais como output
    //TRISA = 0b010111; // set A3 e A5 como output e resto como INPUT
    //TRISB = 0b00100000; //set all port B pins, but RB5, as output
    //TRISC = 0x00; //set all port C pins as output
    
    TRISA = 0b00010000;             //Botao em RA4 como input, resto como output
    TRISB = 0b11110000;             //R4 ~ RB7 como input (botoes)
    TRISC = 0x00;                   //Todos como output, controla os leds.
    
    //PORTA = 0b100111;
    PORTA = 0xff;
    PORTB = 0xff;
    PORTC = 0x00;
            
        
    
    
    /*
    *   Port Configuration for Timer0
    *   set timer0 reading external frequency with 16 prescaler and enables pullups
    *   set the TMR0 register at 133 to obtain the desired interruption time (1ms)
    *   enable global, peripherial, and timer0 interruptions
   */
  
    
    //Pull up enabled
    nRABPU = 0;
    //Timer0 source is internal clock
    T0CS = 0;
    //Prescaler assigned to timer0
    PSA = 0;   
    //timer0 prescarler is 16
    PS0 = 1;
    PS1 = 1;
    PS2 = 0;
    
    //Timer0 initial value
    TMR0= 133;  
    GIE=1;         //global interruptions enabled
    PEIE=1;        //pheripherial interruptions enabled
    T0IE=1;        //timer0 interrup enabled 
    RABIE = 1;     //enables PORTA e PORTB interrupt on change.
    T0IF = 0;      //set timer0 interruption flag to 0.
    RABIF = 0;     //set port interruption flag to 0.
    

           //enables pull ups on buttons
    WPUA4 = 1;
    WPUB4 = 1;
    WPUB5 = 1;
    WPUB6 = 1;
    WPUB7 = 1;
    
    
    
    IOCA = 0b00010000;   //enable interrupt on change para RA4.
    IOCB = 0b11110000; //enable interrupt on change para RB4~RB7.
    
}





//Maquina de estados do programa, é chamada quando um botao é pressionado.
void deviceStateMachine(unsigned char ucButton){
    
    //Se o primeiro botão foi pressionado: rola o dado e imprime o dado na tela, depois muda o estado para ROLL
    if(1 == ucButton){
        deviceCurrentState = ROLL;
        //Chamar aqui função que rola os dados com o valor da variavel global e escreve no display o resultado.
        int ulTotalRoll = 0;
        
        int i;
        for(i = 0; i < diceState[0]; i++){
            ulTotalRoll += (int)(randomNumber())%diceState[1]; //randomNumber();
        }
        
        
        
        return; //Encera a funcao, já rolou o dado e imprimiu o valor no display
    }else if (deviceCurrentState == ROLL){
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
    
        writeCharOnDisplay('0' + diceState[0], 0);
        writeCharOnDisplay('d', 1);
        writeCharOnDisplay('0' + diceState[1]/10, 2);
        writeCharOnDisplay('0' + diceState[1]%10, 3);
    
       
}

unsigned long randomNumber(){
    randomSeed = (37*randomSeed + 98)%1373;
    return randomSeed;
}









