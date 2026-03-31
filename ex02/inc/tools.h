#pragma once

#include <inttypes.h>

// # define PB0 0
// # define PB1 1
// # define PB2 2
// # define PB3 3
// # define PB4 4
// # define PB5 5
// # define PB6 6
// # define PB7 7

// # define PORTB *(volatile uint8_t *) 0x25
// # define DDRB *(volatile uint8_t *) 0x24
// # define PINB *(volatile uint8_t *) 0x23

// # define PD0 0
// # define PD1 1
// # define PD2 2
// # define PD3 3
// # define PD4 4
// # define PD5 5
// # define PD6 6
// # define PD7 7

// # define PORTD *(volatile uint8_t *) 0x2B
// # define DDRD *(volatile uint8_t *) 0x2A
// # define PIND *(volatile uint8_t *) 0x29


// Definiciones simples sin enum
#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

// Macros for specific pines
#define pinMode_OUTPUT(port, bit)   DDR##port |= (1 << bit)
#define pinMode_INPUT(port, bit)    DDR##port &= ~(1 << bit)
#define pinMode_PULLUP(port, bit)   do { DDR##port &= ~(1 << bit); PORT##port |= (1 << bit); } while(0)

#define digitalWrite_HIGH(port, bit)   PORT##port |= (1 << bit)
#define digitalWrite_LOW(port, bit)    PORT##port &= ~(1 << bit)
#define digitalWrite(port, bit, val)   do { if (val) PORT##port |= (1 << bit); else PORT##port &= ~(1 << bit); } while(0)

#define digitalRead(port, bit)         ((PIN##port >> bit) & 1)