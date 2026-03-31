#include <avr/io.h>
#include <util/delay.h>
#include "tools.h"

// output: pin 8
// input: pin 3

int main(void) {
	pinMode(D8, OUTPUT);
	pinMode(D3, INPUT_PULLUP);
	
	while(1) {
		if (digitalRead(D3) == 1)
			digitalWrite(D8, HIGH);
		else
			digitalWrite(D8, LOW);
	}
	return 0;
}