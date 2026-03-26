#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB0);

    DDRD &= ~(1 << DDD3);
    PORTD |= (1 << PORTD3);
    
    while(1)
    {
		PORTB &= ~(1 << PORTB0); 
        if (!(PIND & (1 << PIND3)))
        {
            PORTB |= (1 << PORTB0);
        }
        else
        {
            PORTB &= ~(1 << PORTB0);
        }
    }
    
    return 0;
}