#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "funbits.h"

#define OUT "out"

#ifndef BYTE
#define BYTE 8
#endif


#define carpeta_dir(led) "/sys/class/gpio/gpio" led "/direction"
#define carpeta_pin(led) "/sys/class/gpio/gpio" led "/value"

const char * leds[] = {"17","4","18","23","24","25","22","27"};  
char folder[33]={"/sys/class/gpio/gpio"}; 

static void export_led (const char *ledx);
static void set_direction_out (char *carpeta);
 void carpeta (const char * puerto, char * folder , const char *final);

void hardware (void) {
    int i;
    for(i=0 ; i<BYTE ; ) {
        export_led( leds[i] );
        carpeta(leds[i] , folder , "/direction");
        set_direction_out(folder);
    }
    return;
}



static void export_led (const char *ledx) {
    FILE *handle_export;
    int nWritten;
    if ((handle_export = fopen("/sys/class/gpio/export","w")) == NULL)
    {
        printf("Cannot open EXPORT File. Try again later.\n");
        exit(1);
    }
    nWritten = fputs(ledx , handle_export);
    if (nWritten == -1)
    {
        printf("Cannot EXPORT PIN . Try again later.\n");
        exit(1);
    }
    else
        printf("EXPORT File opened succesfully\n");
    fclose(handle_export); // Be carefulldo this for EACH pin !!!
    return;
}

static void set_direction_out (char *carpeta) {
    FILE * handle_direction;
    int nWritten;
    if ((handle_direction= fopen(carpeta,"w")) == NULL) {
        printf("Cannot open DIRECTION File");
        exit(1);
    }
    // Set pin Direction
    if ((nWritten=fputs("out" , handle_direction))==-1) {
        printf("Cannot open DIRECTION pin. Try again later.\n");
        exit(1);
    }
    else {
        printf("DIRECTION File for PIN opened succesfully\n");
    }
    fclose(handle_direction); // Be carefulldo this for EACH pin !!!
    return;
}

void set_status (char state , char * pin)
{
    FILE * handle;
    if ((handle = fopen(pin,"w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
        exit(1);
    }
    else
    {
        printf("Device successfully opened\n");
    }
    if(fputc(state + '0' ,handle)==-1) // Set pin low
    {
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
        exit(1);
    }
    else{
        printf("Write to file %s successfully done.\n",pin);
    }
    fclose(handle);
    return;
}

 void carpeta (const char * puerto, char * folder , const char *final) {
    while(*folder++){}
    folder--;
    while(*puerto++){
        *folder++ = *puerto;
    }
    while(*final) {
        *folder++ = *final++;
    }
    *folder = 0;
}
 
void rpLeds (void){
    int i;
    for (i=0 ; i<BYTE ; i++) {
        carpeta(leds[i] , folder , "/value");
        set_status( (char)bitGet('A' , i) , folder );
    }
} 