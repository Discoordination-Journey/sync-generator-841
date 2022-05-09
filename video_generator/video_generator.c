// Discoordination's Laboratories
// Video Sync Generator for Electronika-841
// 09.05.2022 (c)
// discoordination.ru/videotechnics/sync_gen_841.html


#define F_CPU 17734480UL // quartz frequency
#define H_TIME 29.95     // horizontal sync

#define HIGH_H PORTB |= _BV(PB0); // horizontal
#define LOW_H PORTB &= ~_BV(PB0);

#define HIGH_V PORTB |= _BV(PB1); // vertical
#define LOW_V PORTB &= ~_BV(PB1);

#include <avr/io.h>
#include <util/delay.h>

uint16_t c_line; // current TV line
uint8_t c_pole; // pole

int main(void)
{
	DDRB |= _BV(PB0); // HORIZONTAL OUT
	DDRB |= _BV(PB1); // VERTICAL OUT
	
    while(1)
    {		
		// horizontal sync
		
		if(c_line%2)
		{
			if(c_pole)
			{
				LOW_H
				_delay_us(H_TIME);
			}
			else
			{
				HIGH_H
				_delay_us(H_TIME);
			}
		}
		else
		{
			if(c_pole)
			{
				HIGH_H
				_delay_us(H_TIME);
			}
			else
			{
				LOW_H
				_delay_us(H_TIME);
			}
			
		}
		
		switch(c_line)
		{
			case 0:
			{
				LOW_V
				break;
			}
			case 7:
			{
				HIGH_V
				break;
			}
		}	
		c_line++;
		
		if(c_line == 625) 
		{
			c_line = 0;
			c_pole ^= 1;
		}				
    }
}