

*********************************

Nome:  Gadget Dado digital. 

Autor: Renato Pepe  (https://github.com/Issamaysin/)

Data:  Novembro de 2021.

*********************************

Com esse gadget o usuário pode simular a rolagem de dados com o aperto de um botão. Pensado para facilitar a vida dos jogadores de RPG de mesa, com esse dispositivo é possível escolher entre os dados de 2, 3, 4, 5, 6, 8, 10, 12, e 20 lados para rolar, o usuário pode rolar apenas um dado ou até nove de uma vez.	


Ao ligar o dispositivo o sistema irá esperar até o usuário pressionar o Botão 1 para começar o funcionamento (espera necessária para conseguir a seed do random number generator) e então estará pronto para usar.
	

O sistema é controlado por um microcontrolador PIC16F687, possui uma interface com um display de 7 segmentos de quatro digitos, por onde o usuário pode vizualizar a configuração dos dados e o resultado da rolagem, e cinco botões por onde o usuário pode configurar os parametros dos dados ou realizar uma rolagem. Software desenvolvido em C através da MPLABX IDE v5.50 e testado em uma simulação através do Proteus v8.11


Botão 1: Realiza uma rolagem com a configuração atual dos dados

Botão 2: Aumenta o número de dados que serão rolados ao mesmo tempo.

Botão 3: Diminui o número de dados que serão rolados ao mesmo tempo.

Botão 4: Aumenta o número de lados do dado que será rolado.

Botão 5: Diminui o número de lados do dado que será rolado.




