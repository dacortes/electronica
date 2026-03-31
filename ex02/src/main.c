#include <avr/io.h>
#include <util/delay.h>
#include "tools.h"

// ouput: pin 8
// input: pin 3

int main(void) {
	pinMode_OUTPUT(B, 0);
	pinMode_PULLUP(D, 3);
	
	while(1) {
		if (digitalRead(D, 3) == true)
			digitalWrite_HIGH(B, 0);
		else
			digitalWrite_LOW(B, 0);
	}
	return 0;
}