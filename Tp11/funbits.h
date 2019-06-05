/***************************************************************************//**
  @file     +funbits.h+
  @brief    +Contiene funciones para el manejo de los puertos A, B y D+
            +A y B son puertos de 8 bits mientras que D es de 16 bits (A y B juntos).
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

#ifndef FUNBITS_H
#define FUNBITS_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/* Observaciones:
    1_ Todas las funciones siguientes reciben como primer parámetro el puerto,
 * denotado por 'A', 'B' o 'D'. 
    2_ bitSet, bitClt, bitGet y bitToggle reciben como segundo parámetro un 
 * número de bit, el cual debe ser válido para el puerto elegido.
    3_ maskOn, maskOff y maskToggle reciben una máscara de 16 bits. En los casos
 * de los puertos A y B dicha máscara debe caber en 8 bits para ser considerada
 * válida. 
    4_ Salvo bitGet, las funciones no devuleven nada. 
 */

/* bitSet: dado un puerto y un bit, setea el bit en 1. */
void bitSet (char port, int bit);    

/* bitCLr: dado un puerto y un bit, coloca el bit en 0. */
void bitClr (char  port, int bit);        

/* bitGet: dado un puerto y un bit, devuelve el valor del bit. */
int bitGet(char port, int bit);

/* bitToggle: dado un puerto y un bit cambia el estado del bit a su opuesto.*/
void bitToggle (char port, int bit);

/* maskOn: dado un puerto y una máscara, activa en el puerto los bits encendidos
   en la máscara */
void maskOn (char port, uint16_t mask);

/* maskOff: dado un puerto y una máscara, apaga en el puerto los bits encendidos
   en la máscara */
void maskOff (char port, uint16_t mask);

/* maskToggle: dado un bit y una máscara, cambia en el puerto el estado de los
   bits encendidos en la máscara. */
void maskToggle (char port, uint16_t mask);

/*******************************************************************************
 ******************************************************************************/

#endif /* FUNBITS_H */

