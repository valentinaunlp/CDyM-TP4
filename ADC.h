#ifndef ADC_H_
	#define ADC_H_

	#define F_CPU 16000000UL
	#include <avr/io.h>
	#include <stdio.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>

	// -------- Prototipos de funciones Publicas ---------------

	// Inicializacion
	void ADC_Init(uint8_t);
	//Lectura
	uint16_t ADC_Read();
#endif /* ADC_H_ */