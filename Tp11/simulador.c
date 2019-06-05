/***************************************************************************//**
  @file     +simulador.c+
  @brief    +Simula un conjunto de 8 leds controlados por el puerto A, usando
             la librería funbits.           
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "funbits.h"
#include "simulador.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BYTE 8          //Bits por byte.
#define ON '*'          //Led encendido.
#define OFF ' '         //Led apagado.

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void turn_on(void);
static void turn_off(void);
static void negate(void);
static void printLeds(void);
static void cleanBuffer(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void simulate(void){
    char input = 0;
    printf("Simulador de Leds.\nNumero 0-7: cambia el estado de ese led.\n"
            "s: enciende todos los leds.\nc: apaga todos los leds.\nt: cambia el"
            "estado de todos los leds.\n");
    while((input = getchar())!= 'q'){           //mientras el usuario no ingrese 'q'
        cleanBuffer();                          //se reinicia el buffer.
        if((input <= '7') && (input >= '0')){   //Si se ingrsa un número entre 0 y 7, ese led cambia de estado.
            bitToggle('A',(input - '0' ));
        }
        else if(input == 'c'){                  //Con 'c' se apagan todos los leds.
            turn_off();
        }
        else if(input == 's'){                  //Con 's' se prenden todos los leds.
            turn_on();
        }
        else if(input == 't'){                  //Con 't' cambian de estado todos los leds.
            negate();
        }
        else{                                   //Cualquiera otra entrada se toma como inválida.
            printf("Operacion invalida\n");
        }
        printLeds();                            //Imprime el estado de los leds.
    }
    printf("Fin de la simulacion\n");           
    cleanBuffer();
    return;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/* turn_on: prende todos los leds. */
static void turn_on(void){
    printf("Turn on!\n");
    maskOn('A', 0xFF);
    return;
}

/* turn_off: apaga todos los leds. */
static void turn_off(void){
    printf("Turn off!\n");
    maskOff('A', 0xFF);
    return;
}

/* negate: cambia el estado de todos los leds */
static void negate(void){
    printf("Negate!\n");
    maskToggle('A', 0xFF);
    return;
}

/* printLeds: imprime el estado de los leds. */
static void printLeds(void){
    int i;                                      
    printf("-----------------\n");
    printf("|     PORTA     |\n");
    printf("-----------------\n");
    putchar('|');
    for(i = 0; i < BYTE; i++){                     //Imprime el estado de cada led.
        if(bitGet('A', i)){                        
            putchar(ON);                           //Si es 1, imprime un '*' 
        }
        else{
            putchar(OFF);                          //Si es 0, imprime un ' '
        }
        putchar('|');
    }
    putchar('\n');
    printf("-----------------\n");
    return;
}

/* cleanBuffer: vacía el buffer de getchar()*/
static void cleanBuffer(void){
    while(getchar() != '\n'){}
    return;
}

/*******************************************************************************
 ******************************************************************************/