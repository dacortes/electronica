#pragma once

#include <inttypes.h>

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