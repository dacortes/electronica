#include <util/delay.h>
#include "tools.h"

int main()
{
    DDRB |= (1 << PB0);
  
    while(1)
    {
        PORTB |= (1 << PB0);
    }
}