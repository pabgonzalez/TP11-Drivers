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
#include "hardware.h"
#include "simulador.h"
#include <pthread.h>
#include <unistd.h>

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
static void hideLeds(void);
void *thread_blynk();
static int state;
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void simulate(void){
    pthread_t blynk;
    pthread_create(&blynk, NULL, thread_blynk, NULL);
    
    char input = 0;
    printf("Simulador de Leds.\nNumero 0-7: cambia el estado de ese led.\n"
            "s: enciende todos los leds.\nc: apaga todos los leds.\nt: cambia el"
            "estado de todos los leds.\n");
    sleep(2);
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
        else if(input == 'b'){
            if(state == 1)
                state = 0;
            else
                state = 1;
        }
        else{                                   //Cualquiera otra entrada se toma como inválida.
            printf("Operacion invalida\n");
        }
        printLeds();                            //Imprime el estado de los leds.
        rpLeds();
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
    for(i = BYTE-1; i >= 0; i--){                     //Imprime el estado de cada led.
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

static void hideLeds(void){
    int i;                                      
    printf("-----------------\n");
    printf("|     PORTA     |\n");
    printf("-----------------\n");
    putchar('|');
    for(i = BYTE-1; i >= 0; i--){                     //Imprime el estado de cada led.
        putchar(OFF);
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

void * thread_blynk(){
    while (1){
        if (state == 1){
            hideLeds();
            rpLeds_Off();
            sleep(1);
            printLeds();
            rpLeds();
            sleep(1);
        }
        /*else{
            printLeds();
            sleep(1);
        }*/
    }
}

/*******************************************************************************
 ******************************************************************************/