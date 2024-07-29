 
#include "ADC.h"

void ADC_Init(uint8_t canal){
	
	// Ajusta resultado a la derecha
	ADMUX &=~ (1<<ADLAR);

	// Voltage de ref = AVCC //
	ADMUX |=  (1<<REFS0);
	ADMUX &=~ (1<<REFS1);

	// Divisor de frecuencia = 128 -> 16000/128 = 125 KHz
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
	
	// Selección del canal del ADC
	ADMUX &=~  0x0F;
	ADMUX |=  canal;
	
	// Encendemos el ADC
	ADCSRA |= (1<<ADEN);
	_delay_us(10);	// Espera que encienda
}

uint16_t ADC_Read(){

	// Empezar conversion
	ADCSRA |= (1<<ADSC);

	// Esperar hasta que finalice conversión
	while( !(ADCSRA & (1<<ADIF)) );
	ADCSRA |= (1<<ADIF);	// Reiniciamos el flag

	return ADC;
}