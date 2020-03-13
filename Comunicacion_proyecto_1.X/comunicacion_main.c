/*
 * File:   comunicacion_main.c
 * Author: MIGUEL GARC�A
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include "serial.h"
#include "SPI.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

uint8_t mandar_rasp = 0;
uint8_t recibir_rasp = 0;
uint8_t bandera_1 = 0;

//      LECTURAS
uint8_t distancia_atr = 0;
uint8_t distancia_ade = 0;
uint8_t temp_amb = 0;
uint8_t temp_obj = 0;
uint8_t posicion = 0;
uint8_t tiempo = 0;
uint8_t humedad = 0;



void main(void) {
    PORTC = 0x00;
    TRISC = 0x00;
    oscillator(6);
    init_serial();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);  //MASTER  
    
    while(1){
      
        
        if (PIR1bits.RCIF == 1){
            bandera_1 = RCREG;
        }  
        if (bandera_1 == 110){
            while (PIR1bits.RCIF == 0);
            distancia_atr = RCREG;
            while (PIR1bits.RCIF == 0);
            distancia_ade = RCREG;             
            while (PIR1bits.RCIF == 0);
            temp_amb = RCREG;
            while (PIR1bits.RCIF == 0);
            temp_obj = RCREG;             
            while (PIR1bits.RCIF == 0);
            posicion = RCREG;
            while (PIR1bits.RCIF == 0);
            tiempo = RCREG;             
            while (PIR1bits.RCIF == 0);
            humedad = RCREG;
            bandera_1 = 0;
            mandar_rasp = 1;
        }
        
        __delay_ms(10);
        
        if (mandar_rasp = 1){
            spiWrite(110);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(distancia_atr);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(distancia_ade);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(temp_amb);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(temp_obj);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(posicion);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(tiempo);
            recibir_rasp = spiRead();
            __delay_ms(10);
            
            spiWrite(humedad);
            recibir_rasp = spiRead();
            __delay_ms(10);
        }
        
        
    }
    return;
}
