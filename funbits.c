/***************************************************************************//**
  @file     +funbits.c+
  @brief    +Contiene funciones para el manejo de los puertos A, B y D+
            +A y B son puertos de 8 bits mientras que D es de 16 bits (A y B juntos).
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funbits.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MASK1   0x1             //Máscara genérica útil para múltiples funciones.
#define BYTE    8               //Bits por byte.

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef union {
    struct {
        uint8_t B;              //Puerto B
        uint8_t A;              //Puerto A
    };
    uint16_t D;                 //Puerto D
} PORT;                         //La unión PORT tiene dos puertos de 8 bits (A y B) y un puerto D que es el A junto con el B.

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int validate(char port, int bit);
static int validateMask(char port, uint16_t mask);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static PORT puerto;             //puerto define una unión de tipo PORT.
static uint8_t mask8;           //una máscara de 8 bits.
static uint16_t mask16;         //una máscara de 16 bits.
    
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* bitSet: recibe un puerto y un número de bit. Enciende ese bit de ese puerto.*/
void bitSet (char port, int bit){
    if (validate(port,bit)) {            //Sigue si la entrada es válida,                              
        return;
    }
    switch (port) {        
        case 'A':                       //Caso Puerto A                
            mask8 = (MASK1 << bit);     //Máscara de 8 bits que solo tiene 1 en la posición recibida.
            puerto.A |= mask8;          //Ahora el puerto A tiene el bit recibido en 1.
            break;           
        case 'B':                       //Caso Puerto B (análogo A)
            mask8 = (MASK1 << bit);
            puerto.B |= mask8;
            break;           
        case 'D':                       //Caso puerto D
            mask16 = (MASK1 << bit);
            puerto.D |= mask16;
            break;       
        default: break;
    }
    return;
}

/* bitClr: recibe un puerto y un número de bit. Apaga ese bit de ese puerto.*/
void bitClr (char port, int bit){
    if (validate(port,bit)) {           //Sigue si la entrada es válida.
        return;
    }
    switch (port) {       
        case 'A':                       //Caso Puerto A.
            mask8 = ~(MASK1 << bit);    //Máscara de 8 bits con 0 solo en el bit recibido.
            puerto.A &= mask8;          //Borra el bit en cuestión del puerto A.
            break;            
        case 'B':                       //Caso Puerto B (análogo A)
            mask8 = ~(MASK1 << bit);
            puerto.B &= mask8;
            break;            
        case 'D':                       //Caso Puerto D.
            mask16 = ~(MASK1 << bit);   //Máscara de 16 bits con 0 solo en el bit recibido.
            puerto.D &= mask16;         //Borra el bit.
            break;
        default: 
            printf("default\n");
            break;
    }
    return;
}

/* bitGet: recibe un puerto y un bit. Devuelve el estado de ese bit de ese puerto.
 * Devuelve -1 si la entrada es inválida. */
int bitGet(char port, int bit){
    int ans;
    if(validate(port, bit)){
        return -1;
    }
    switch(port){
        case 'A':                               //Caso Puerto A.
            mask8 = (MASK1 << bit);             //Máscara de 8 bits con un 1 en el bit recibido.
            ans = ((puerto.A & mask8)>> bit);   //Estado de ese bit en el puerto A.
            break;
        case 'B':                               //Caso Puerto B.
            mask8 = MASK1 << bit;
            ans = ((puerto.B & mask8)>> bit);
            break;
        case 'D':                               //Caso Puerto D.
            mask16 = MASK1 << bit;
            ans = ((puerto.D & mask8)>> bit);
            break;
        default: break;
    }
    return ans;
}

/* bitToggle: recibe un puerto y un número de bit. Invierte el estado de ese
   bit de ese puerto. No devuelve nada.*/
void bitToggle (char port, int bit){
    if (validate(port,bit)) {                   //Sigue si la entrada es válida.
        return;
    }
    switch (port) {        
        case 'A':                               //Caso Puerto A.
            mask8 = MASK1 << bit;               //Máscara de 8 bits con un 1 en el bit recibido.
            puerto.A ^= mask8;                  //Invierte el estado de ese bit en el puerto A.
            break;           
        case 'B':                               //Caso Puerto B.
            mask8 = MASK1 << bit;
            puerto.B ^= mask8;
            break;            
        case 'D':                               //Caso Puerto D.
            mask16 = (MASK1 << bit);
            puerto.D ^= mask16;
            break;        
        default: break;
    }
    return;
}

/* maskOn: recibe un puerto y una máscara de 16 bits. Activa en el puerto los bits
 que están encendidos en la máscara. */
void maskOn (char port, uint16_t mask) { 
    if (validateMask(port,mask)) {              //Sigue si la entrada es válida.
        return;
    } 
    switch (port) {
        case 'A':                               //Caso Puerto A.
            puerto.A |= (uint8_t)mask;          //Activa en el puerto A los bits encendidos en la máscara (8 bits)
            break;
        case 'B': 
            puerto.B |= (uint8_t)mask;          //Caso Puerto B (Análogo A)
            break;
        case 'D':                               //Caso Puerto D.
            puerto.D |= mask;                   //Activa en el puerto D los bits encendidos en la máscara (16 bits)
            break;
        default: break;               
    }
    return;
}

/* maskOff: recibe un puerto y una máscara de 16 bits. Desactiva en el puerto los bits
 que están encendidos en la máscara. */
void maskOff (char port, uint16_t mask) { 
    if (validateMask(port,mask)) {              //Sigue si la entrada es válida.
        return;
    }
    switch (port) {
        case 'A':                               //Caso Puerto A.
            puerto.A &= ~(uint8_t)mask;         //Apaga en el puerto A los bits encendidos en la máscara (8 bits).
            break;
        case 'B':                               //Caso Puerto B (Análogo).
            puerto.B &= ~(uint8_t)mask;
            break;
        case 'D':                               //Caso Puerto D.
            puerto.D &= ~mask;                  //Apaga en el puerto D los bits encendidos en la máscara (16 bits).
            break;
        default: break;               
    }
    return;
}

/* maskToggle: recibe un puerto y una máscara de 16 bits. Invierte el estado
 de los bits del puerto que están activados en la máscara. */
void maskToggle (char port, uint16_t mask) { 
    if (validateMask(port,mask)) {              //Sigue si la entrada es válida.
        return;
    }
    switch (port) {                             
        case 'A':                               //Caso Puerto A.
            puerto.A ^= (uint8_t)mask;          //Invierte estado en puerto A de bits activados en mask (máscara de 8 bits).
            break;
        case 'B':                               //Caso Puerto B.
            puerto.B ^= (uint8_t)mask;
            break;
        case 'D':                               //Caso Puerto D.
            puerto.D ^= mask;                   //Invierte estado en puerto D de bits activados en mask (máscara de 16 bits).
            break;
        default: break;               
    }
    return;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* validate:    recibe un puerto y un bit. verifica la validez del número de bit 
                para ese puerto. Devuelve un 0 si es valido y un 1 si no lo es. 
 */
static int validate (char port, int bit){
    if (bit < 0){
        printf("El numero de bits no puede ser negativo\n");
        return 1;
    }  
    switch (port) {        
        case 'A': case 'B':
            if (bit >= BYTE){
                printf("Ingrese un numero entre 0 y 7 -Puertos A y B-\n");
                return 1;
            } 
            break;                 
        case 'D':
            if (bit >= 2*BYTE){
                printf("Ingrese un numero entre 0 y 15 -Puerto D-\n");
                return 1;
            }
            break;        
        default: 
            printf("Ingrese un puerto valido: 'A', 'B' o 'D'.\n");
            return 1;
            break;
    }
    return 0;           //Si llega acá la entrada es válida.
}

/* validateMask:    recibe un puerto y una máscara de 16 bits. Valida que el 
 *                  tamaño la máscara sea compatible con ese puerto. 
 *                  Devuelve un 0 si lo es y un 1 sino.
 */
static int validateMask(char port, uint16_t mask){   
    switch (port) {       
        case 'A': case 'B':
            if (mask >= 256){           //Solamente las máscaras de valor númerico inferior a 256 son válidas para A o B.
                printf("Ingrese una mascara valida de 8 bits -Puertos A y B-\n");
                return 1;
            } 
            break;                     
        case 'D':
            break;                      //Cualquier máscara de 16 bits es válida para D.        
        default: 
            printf("Ingrese un puerto valido: 'A', 'B' o 'D'.\n");
            return 1;
            break;
    }
    return 0;                           //Si llega hasta acá la entrada es válida.
}

/*******************************************************************************
 ******************************************************************************/