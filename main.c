/*
 * TP_4_2024.c
*/ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "serialPort.h"
#include "RGB.h"
#include "ADC.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

//comunicación con la ISR
volatile char RX_Buffer=0;
volatile uint8_t LED_COLOR = 'N';

//variable para guardar el dato del ADC
uint16_t dato_adc;

int main(void){
	
    SerialPort_Init(BR9600); 			// Inicializo formato 8N1 y BAUDRATE = 9600bps
    SerialPort_TX_Enable();				// Activo el Transmisor del Puerto Serie
    SerialPort_RX_Enable();				// Activo el Receptor del Puerto Serie
    SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
    ADC_Init(3);						// Inicializo ADC y configuro canal 3 para la comunicación
	RGB_Init();							// Inicializo RGB
	sei();								// Activo interrup globales

	SerialPort_Send_String("Presione R, G o B para cambiar el color\r\n");
    while (1) {
		// Si se selecciona color R, G o B se lee el potenciometro y modifica intensidad
		if((LED_COLOR == 'R') || (LED_COLOR == 'G') ||(LED_COLOR == 'B')) {		
			dato_adc = ADC_Read();	//Lectura del potenciometro			
			uint8_t intensidad = (255.0/1023)*dato_adc;		//Convierte dato del potenciometro en una intensidad de 0 a 255
			LED_Intensidad(intensidad,LED_COLOR);			//Modifica intensidad del led enviado por parametro
		}
	}
}

ISR(USART_RX_vect){
	RX_Buffer = UDR0;
	if((RX_Buffer == 'R')){
		LED_COLOR='R';
		SerialPort_Send_String("Intensidad LED RED  \r\n");
	} else if((RX_Buffer == 'G')){
		LED_COLOR='G';
		SerialPort_Send_String("Intensidad LED GREEN  \r\n");
	} else if((RX_Buffer == 'B')){
		LED_COLOR='B';
		SerialPort_Send_String("Intensidad LED BLUE  \r\n");
	} else{
		LED_COLOR='N';
		SerialPort_Send_String("Lectura del potenciometro pausada - Ingrese un color (R, G o B) para continuar  \r\n");
	}
}
