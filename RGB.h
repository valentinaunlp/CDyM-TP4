
#ifndef RGB_H_
	#define RGB_H_

	#define F_CPU 16000000UL
	#include <avr/io.h>
	#include <stdio.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicializacion
	void RGB_Init();
	// Modifica registro con intensidad del led recibido por parametro
	void LED_Intensidad(uint16_t, uint8_t);
	// Inicialización del Timer0 para PWM por software
	void timer0_init();

#endif /* RGB_H_ */