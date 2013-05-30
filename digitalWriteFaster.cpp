#include "WProgram.h"
#include "digitalWriteFaster.h"

void shiftOutFaster(uint8 dataPin, uint8 clockPin, uint8 bitOrder, uint8 val) {
    int i;

    for (i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            digitalWriteFaster(dataPin, !!(val & (1 << i)));
        } else {
            digitalWriteFaster(dataPin, !!(val & (1 << (7 - i))));
        }

        digitalWriteFaster(clockPin, HIGH);
        digitalWriteFaster(clockPin, LOW);
    }
}
