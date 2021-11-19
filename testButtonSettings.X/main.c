/*
 * File:   main.c
 * Author: User
 *
 * Created on 18 de Novembro de 2021, 17:26
 */

//Testar pull up e interrupção nos botões.




// PIC16F687 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.




#include <xc.h>
#include <PIC16F687.h>


void __interrupt() interruptRoutine(){
    
    if(RABIF){
        
        PORTB ^= (1<<7);
        RABIF = 0;
    }
    
    
}


void main(void) {

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
    
    
   //Seta os pinos dos botoes como input e os demais como output
    ANSEL = 0x00;
    TRISB = 0b00000000; //todos como output, led está no RB7
    TRISA = 0x00 + (1<<2) ; //pino do botao RA2 como input
    PORTB = 0x00;

    
    GIE=1;         //global interruptions enabled
    PEIE=1;        //pheripherial interruptions enabled
    RABIE = 1;     //enables PORTA e PORTB interrupt on change.
    RABIF = 0;     //set port interruption flag to 0.
    
    IOCA = 0b00000100;   //enable interrupt on pin
    //Pull up enabled
    nRABPU = 0;
    
    
           //enables pull ups on buttons
    WPUA2 = 1;
    
    PORTB |= (1<<7);
    
    
    
    while(1){
     
       
    }
    
 
    return;
}
