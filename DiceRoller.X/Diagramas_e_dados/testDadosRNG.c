
/*
 * File:   testDadoRNG
 * Author: Renato Pepe
 * Description: Pequeno codigo para testar como está o equilibrio da função que gera numeros aleatorios.
 * Created on 23 de Novembro
 */

#include <stdio.h>

//Seed usada para gerar numeros aleatorios
int randomSeed = 0;

//Funcao que retorna um numero aleatorio
int randomNumber();

int main(){

    //Inicializa seed
    randomSeed = 1234;

    //Imprime o valor da seed no terminal
    printf("seed: %d | ", randomSeed);

    //Descarta os dois primeiros numeros gerados
    randomNumber();
    randomNumber();

    //D20 data 
    int data[20] = {0};

    //Rola o d20 20mil vezes utilizando a funcao de RNG
    int i;
    for(i = 0; i < 20000; i++){
        int rolledNumber = randomNumber()%20;
        data[rolledNumber]++;
    }


    //Imprime no terminal quantas vezes o numero foi sorteado, em ordem 1~20
    printf("Data: ");
    for(i = 0; i < 20; i++){
        printf(" %d ", data[i]);
    }

    return 0;
}



 /********************************************************************************************/
 /* Method name:        randomNumber                                                         */
 /* Method description: Utiliza a seed definida globalmente para gerar um numero aleatorio   */
 /* Input params:       n/a                                                                  */
 /* Output params:      n/a                                                                  */
 /* ******************************************************************************************/
int randomNumber(){
    randomSeed = (733*randomSeed + 1237)%7393;
    return randomSeed;
}