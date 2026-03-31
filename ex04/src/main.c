#include <avr/io.h>
#include <util/delay.h>
#include "tools.h"

// output: pin 8
// input: pin 3


void setPinMode(void)
{
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D8, INPUT_PULLUP);
	pinMode(D9, INPUT_PULLUP);
}

void printNumberBits(uint8_t num)
{
	if (num & (1 << 0))
		digitalWrite(D2, HIGH);
	else
		digitalWrite(D2, LOW);

	if (num & (1 << 1))
		digitalWrite(D3, HIGH);
	else
		digitalWrite(D3, LOW);

	if (num & (1 << 2))
		digitalWrite(D4, HIGH);
	else
		digitalWrite(D4, LOW);

	if (num & (1 << 3))
		digitalWrite(D5, HIGH);
	else
		digitalWrite(D5, LOW);
}

int main(void) {
	uint8_t num = 0;
	uint8_t curr_btn1 = 0;
	uint8_t last_btn1 = 1;

	uint8_t curr_btn2 = 0;
	uint8_t last_btn2 = 1;

	setPinMode();
	printNumberBits(num);
	
	while(1) {
		curr_btn1 = digitalRead(D8);
		curr_btn2 = digitalRead(D9);
		if (curr_btn1 == 1 && last_btn1 == 0 && num < 15) {
			num++;
			printNumberBits(num);
		}
		if (curr_btn2 && !last_btn2 && num >= 1) {
			num--;
			printNumberBits(num);
		}
		last_btn1 = curr_btn1;
		last_btn2 = curr_btn2;
	}
	return 0;
}