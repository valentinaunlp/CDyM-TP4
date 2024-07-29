
#include "RGB.h"

uint8_t R=0, G=0, B=0;
uint8_t top_red = 255;


void RGB_Init(){
	
	//Configura los pines PB1, PB2 y PB5 como salida
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1<<PINB5);

	// Configurar Timer1 para PWM en modo no invertido en OC1A (PB1), OC1B (PB2)	
	// Modo no invertido para ambos canales
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	
	// Modo Fast PWM 8 bits. TOP=255
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	
	// Prescaler de 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	// Para que la señal sea igual o mayor a 50 Hz OCR1X debe ser menor o igual a 156 con un preescaler de 1024 (En interrupción, NO EN FAST PWM)
	OCR1B = 255;
	OCR1A = 255;
	timer0_init();
	
}

void LED_Intensidad(uint16_t intensidad, uint8_t color){
	if (color == 'R') {
		top_red = intensidad;
    } else if (color == 'G') {
			OCR1B = intensidad;
	} else if (color == 'B') {
			OCR1A = intensidad;
	}
}

void timer0_init() {
	// Modo CTC
	TCCR0A |= (1 << WGM01);
	
	// Valor de comparación
	OCR0A = 15;
	
	// Habilitar interrupción de Timer0
	TIMSK0 |= (1 << OCIE0A);
	
	// Preescalador de 64
	TCCR0B |= (1 << CS01) | (1 << CS00);
	
	PORTB |= (1<<PORTB5);
	
}

ISR(TIMER0_COMPA_vect) {
	volatile static uint8_t contador1 = 0;
	volatile static uint8_t contador2 = 0;
	volatile static uint8_t nivel_bajo = 0;

	if (contador1 < top_red) {
		contador1++;
	} else { if(!nivel_bajo) {
				nivel_bajo = 1;
				PORTB ^= (1 << PORTB5);
				} else { if (contador2 < (255-top_red)) {
							contador2++;
						} else {
							PORTB ^= (1 << PORTB5);
							contador1 = 0;
							contador2 = 0;
							nivel_bajo = 0;
						}
			}
	}
}