// #pragma once

// #include <inttypes.h>

// #define OUTPUT 1
// #define INPUT 0
// #define INPUT_PULLUP 2
// #define HIGH 1
// #define LOW 0

// // Macros for specific pines
// #define pinMode_OUTPUT(port, bit)   DDR##port |= (1 << bit)
// #define pinMode_INPUT(port, bit)    DDR##port &= ~(1 << bit)
// #define pinMode_PULLUP(port, bit)   do { DDR##port &= ~(1 << bit); PORT##port |= (1 << bit); } while(0)

// #define digitalWrite_HIGH(port, bit)   PORT##port |= (1 << bit)
// #define digitalWrite_LOW(port, bit)    PORT##port &= ~(1 << bit)
// #define digitalWrite(port, bit, val)   do { if (val) PORT##port |= (1 << bit); else PORT##port &= ~(1 << bit); } while(0)

// #define digitalRead(port, bit)         ((PIN##port >> bit) & 1)

#pragma once

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

/* ============================================================================
 * ARDUINO-STYLE CONSTANTS
 * ============================================================================ */
#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

/* ============================================================================
 * PIN STRUCTURE
 * ============================================================================ */

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    uint8_t bit;
} Pin_t;

/* ============================================================================
 * PIN DEFINITIONS - All Arduino Uno Pins
 * ============================================================================ */

// ========== DIGITAL PINS (D0 - D13) ==========
static const Pin_t D0 = { &DDRD, &PORTD, &PIND, 0 };  // RX
static const Pin_t D1 = { &DDRD, &PORTD, &PIND, 1 };  // TX
static const Pin_t D2 = { &DDRD, &PORTD, &PIND, 2 };  // INT0
static const Pin_t D3 = { &DDRD, &PORTD, &PIND, 3 };  // INT1, PWM
static const Pin_t D4 = { &DDRD, &PORTD, &PIND, 4 };
static const Pin_t D5 = { &DDRD, &PORTD, &PIND, 5 };  // PWM
static const Pin_t D6 = { &DDRD, &PORTD, &PIND, 6 };  // PWM
static const Pin_t D7 = { &DDRD, &PORTD, &PIND, 7 };
static const Pin_t D8 = { &DDRB, &PORTB, &PINB, 0 };
static const Pin_t D9 = { &DDRB, &PORTB, &PINB, 1 };  // PWM
static const Pin_t D10 = { &DDRB, &PORTB, &PINB, 2 }; // SS, PWM
static const Pin_t D11 = { &DDRB, &PORTB, &PINB, 3 }; // MOSI, PWM
static const Pin_t D12 = { &DDRB, &PORTB, &PINB, 4 }; // MISO
static const Pin_t D13 = { &DDRB, &PORTB, &PINB, 5 }; // SCK, LED

// ========== ANALOG PINS (A0 - A5) ==========
static const Pin_t A0 = { &DDRC, &PORTC, &PINC, 0 };  // ADC0
static const Pin_t A1 = { &DDRC, &PORTC, &PINC, 1 };  // ADC1
static const Pin_t A2 = { &DDRC, &PORTC, &PINC, 2 };  // ADC2
static const Pin_t A3 = { &DDRC, &PORTC, &PINC, 3 };  // ADC3
static const Pin_t A4 = { &DDRC, &PORTC, &PINC, 4 };  // ADC4, SDA
static const Pin_t A5 = { &DDRC, &PORTC, &PINC, 5 };  // ADC5, SCL

// ========== SPECIAL FUNCTION ALIASES ==========
static const Pin_t LED_BUILTIN = { &DDRB, &PORTB, &PINB, 5 };  // D13
static const Pin_t SDA = { &DDRC, &PORTC, &PINC, 4 };          // A4
static const Pin_t SCL = { &DDRC, &PORTC, &PINC, 5 };          // A5
static const Pin_t SS = { &DDRB, &PORTB, &PINB, 2 };           // D10
static const Pin_t MOSI = { &DDRB, &PORTB, &PINB, 3 };         // D11
static const Pin_t MISO = { &DDRB, &PORTB, &PINB, 4 };         // D12
static const Pin_t SCK = { &DDRB, &PORTB, &PINB, 5 };          // D13
static const Pin_t RX = { &DDRD, &PORTD, &PIND, 0 };           // D0
static const Pin_t TX = { &DDRD, &PORTD, &PIND, 1 };           // D1
static const Pin_t EXT_INT0 = { &DDRD, &PORTD, &PIND, 2 };     // D2
static const Pin_t EXT_INT1 = { &DDRD, &PORTD, &PIND, 3 };     // D3

/* ============================================================================
 * PIN FUNCTIONS
 * ============================================================================ */

// Pin mode configuration
static inline void pinMode(Pin_t pin, uint8_t mode) {
    if (mode == OUTPUT) {
        *pin.ddr |= (1 << pin.bit);
    } 
    else if (mode == INPUT) {
        *pin.ddr &= ~(1 << pin.bit);
    } 
    else if (mode == INPUT_PULLUP) {
        *pin.ddr &= ~(1 << pin.bit);
        *pin.port |= (1 << pin.bit);
    }
}

// Digital write
static inline void digitalWrite(Pin_t pin, uint8_t value) {
    if (value == HIGH) {
        *pin.port |= (1 << pin.bit);
    } else {
        *pin.port &= ~(1 << pin.bit);
    }
}

// Digital read
static inline uint8_t digitalRead(Pin_t pin) {
    return (*pin.pin >> pin.bit) & 1;
}

// Digital toggle
static inline void digitalToggle(Pin_t pin) {
    *pin.port ^= (1 << pin.bit);
}

/* ============================================================================
 * USAGE EXAMPLES
 * ============================================================================ */

/*
 * EXAMPLE 1: YOUR ORIGINAL CODE - NOW WORKING!
 * 
 * int main(void) {
 *     pinMode(D8, OUTPUT);           // PB0 = D8 as output
 *     pinMode(D3, INPUT_PULLUP);     // PD3 = D3 as input with pull-up
 *     pinMode(D13, OUTPUT);          // LED_BUILTIN
 *     pinMode(A0, INPUT_PULLUP);     // Another button on A0
 *     
 *     while(1) {
 *         // Control LED with button on D3
 *         if (digitalRead(D3) == LOW) {
 *             digitalWrite(D8, HIGH);
 *         } else {
 *             digitalWrite(D8, LOW);
 *         }
 *         
 *         // Blink LED_BUILTIN when A0 is pressed
 *         if (digitalRead(A0) == LOW) {
 *             digitalWrite(LED_BUILTIN, HIGH);
 *             _delay_ms(100);
 *             digitalWrite(LED_BUILTIN, LOW);
 *             _delay_ms(100);
 *         }
 *     }
 *     return 0;
 * }
 */

/*
 * EXAMPLE 2: Simple LED Blink
 * 
 * int main(void) {
 *     pinMode(D13, OUTPUT);
 *     
 *     while(1) {
 *         digitalWrite(D13, HIGH);
 *         _delay_ms(1000);
 *         digitalWrite(D13, LOW);
 *         _delay_ms(1000);
 *     }
 *     return 0;
 * }
 */

/*
 * EXAMPLE 3: Reading multiple buttons
 * 
 * int main(void) {
 *     pinMode(D2, INPUT_PULLUP);
 *     pinMode(D3, INPUT_PULLUP);
 *     pinMode(D4, OUTPUT);
 *     
 *     while(1) {
 *         if (digitalRead(D2) == LOW && digitalRead(D3) == LOW) {
 *             digitalWrite(D4, HIGH);
 *         } else {
 *             digitalWrite(D4, LOW);
 *         }
 *     }
 *     return 0;
 * }
 */

/*
 * EXAMPLE 4: Using toggle function
 * 
 * int main(void) {
 *     pinMode(D13, OUTPUT);
 *     
 *     while(1) {
 *         digitalToggle(D13);
 *         _delay_ms(500);
 *     }
 *     return 0;
 * }
 */

/*
 * EXAMPLE 5: Using special function aliases
 * 
 * int main(void) {
 *     pinMode(LED_BUILTIN, OUTPUT);
 *     pinMode(EXT_INT0, INPUT_PULLUP);
 *     
 *     while(1) {
 *         if (digitalRead(EXT_INT0) == LOW) {
 *             digitalWrite(LED_BUILTIN, HIGH);
 *         } else {
 *             digitalWrite(LED_BUILTIN, LOW);
 *         }
 *     }
 *     return 0;
 * }
 */

/* ============================================================================
 * QUICK REFERENCE CARD
 * ============================================================================ */

/*
 * AVAILABLE PINS:
 * ===============
 * Digital:  D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13
 * Analog:   A0, A1, A2, A3, A4, A5
 * 
 * SPECIAL ALIASES:
 * ================
 * LED_BUILTIN = D13
 * SDA         = A4
 * SCL         = A5
 * SS          = D10
 * MOSI        = D11
 * MISO        = D12
 * SCK         = D13
 * RX          = D0
 * TX          = D1
 * EXT_INT0    = D2  (renamed to avoid conflict)
 * EXT_INT1    = D3  (renamed to avoid conflict)
 * 
 * FUNCTIONS:
 * ==========
 * pinMode(pin, mode)              - OUTPUT, INPUT, INPUT_PULLUP
 * digitalWrite(pin, value)        - HIGH or LOW
 * digitalRead(pin)                - returns HIGH or LOW
 * digitalToggle(pin)              - toggles pin state
 * 
 * PWM CAPABLE PINS:
 * =================
 * D3, D5, D6, D9, D10, D11
 */

/* ============================================================================
 * IMPORTANT NOTES
 * ============================================================================ */

/*
 * 1. All pins are defined as static const structures - minimal memory usage
 * 
 * 2. Functions are static inline - with -Os or -O2 optimization, they compile
 *    to direct register access with zero overhead
 * 
 * 3. The names EXT_INT0 and EXT_INT1 are used instead of INT0/INT1 to avoid
 *    conflicts with AVR header definitions
 * 
 * 4. All pins work exactly like Arduino but with native AVR performance
 * 
 * 5. For analog reading, you'll need to configure the ADC separately
 * 
 * 6. For PWM, you'll need to configure timers separately
 */