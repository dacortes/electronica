

// output: pin 8

// int main(void) {
//     pinMode_OUTPUT_D8();
//     while(1)
// 		digitalWrite_HIGH_D8();
//     return 0;
// }

#include "tools.h"

// output: pin 8
int main(void) {
    pinMode(D8, OUTPUT);
    while(1) {
        digitalWrite(D8, HIGH);
    }
    return 0;
}