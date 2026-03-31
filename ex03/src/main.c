#include <avr/io.h>
#include <util/delay.h>
#include "tools.h"

// output: pin 8
// input: pin 3

int main(void) {
	uint8_t led_state = 0;
	uint8_t last_button_state = 0;
	uint8_t current_button;
	pinMode(D8, OUTPUT);
	pinMode(D3, INPUT_PULLUP);
	
	while(1) {
		current_button = digitalRead(D3);
		if (!current_button  && last_button_state) {
			led_state = !led_state;
			digitalWrite(D8, led_state);
		}
		last_button_state = current_button;
	}
	return 0;
}