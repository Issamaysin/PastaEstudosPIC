/*
 * File:   utils.h
 * Author: Renato Pepe
 * Description:     Arquivo para declaração das funções de utilidade
 * Created on 26 de Outubro de 2021, 13:50
 */


#ifndef UTILS_H
#define	UTILS_H

/* 
 * pin output methods 
 *  obs: only pin as input since PIC12F1822 only has one PORT 
 */
//set input pin as high (on portA)
void setPin(int iPin);
//clear pin
void clearPin(int iPin);
//toogle pin
void togglePin(int iPin);



#endif	/* UTILS_H */

