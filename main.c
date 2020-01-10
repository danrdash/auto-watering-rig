#define TRIGPOINT 128

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "lcdlib.h"

int main(void) {
		char buffer[10];
		DataDir_Control |=  1<<LightSwitch | 1<<RegisterSelect | 1<<ReadWrite; //set relevant bits as inputs
	
		// Configure PORT D bit 0 to an output
		DDRD = 0b00000001;

		// Configure PORT C bit 0 to an input
		DDRC = 0b00000000;

		// Configure ADC to be left justified, use AVCC as reference, and select ADC0 as ADC input
		ADMUX = 0b01100000;

		// Enable the ADC and set the prescaler to max value (128)
		ADCSRA = 0b10000111;


		uart_init();
		stdout = &uart_output;
		stdin  = &uart_input;
	
		char input;
		Send_Command(0x01); // clear screen
		_delay_ms(20);
		
		_delay_us(50);
		Send_Command(0x38); //Initialize 8 bit mode
		_delay_ms(10);
		
		_delay_us(50);
		Send_Command(0b00001111); // cursor and display on
		_delay_ms(50);
		while(1) {
		
			ADCSRA = ADCSRA | (1 << ADSC);
			
			// Wait until the ADSC bit has been cleared
			while(ADCSRA & (1 << ADSC));
			Send_Command(0x01); // clear screen
			_delay_ms(100);
			Send_String(itoa(ADCH, buffer, 10));
			_delay_ms(1000);
			if (ADCH < 100)
			{
				//TURN ON PERIPHERAL ROUTINE 
				continue;	
			}
			
			
			_delay_ms(100);
		}
		//puts("Hello world! Test Continues");
		//input = getchar();
		//printf("You wrote %c\n", input);
	
	
	return 0;
}