/***************************************************************************//**
  @file     +simulador.h+
  @brief    +Simula un conjunto de 8 leds controlados por el puerto A, usando
             la librería funbits.           
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

#ifndef SIMULADOR_H
#define	SIMULADOR_H

/**
 * @brief simulate: simula 8 leds controlados por el puerto A. Toma entradas 
 * por consola. 
 * 1) Num 0-7: cambia el estado de ese led (ese bit).
 * 2) s: prende todos los leds.
 * 3) c: apaga todos los leds.
 * 4) t: inivierte el estado de todos los leds.
*/
void simulate(void);

#endif	/* SIMULADOR_H */

