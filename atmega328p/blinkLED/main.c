#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	DDRB = 0xFF;
	PORTB = 0x00;

	DDRC = 0xFF;
	PORTC = 0X00;

	int freq = 0;

	while(1){
		PORTD |= _BV(PORTD4);
		_delay_ms(freq);

		PORTD &= ~_BV(PORTD4);
		_delay_ms(freq);

		if (freq < 200){
			freq++;
		}else{
			freq=0;
		}
	}
}
