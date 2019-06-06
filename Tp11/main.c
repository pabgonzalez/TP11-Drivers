/***************************************************************************//**
  @file     +main.c+
  @brief    +Invoca simulador de leds.+
  @author   +Grupo 2.+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funbits.h"
#include "simulador.h"
#include "hardware.h"

#define BYTE    8

int main (void) {
    hardware();
    simulate();
    return 0;
}
