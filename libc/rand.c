#include "rand.h"

static unsigned int a = 9;       // multiplier
static unsigned int b = 13;      // increment


unsigned int generate_rand(unsigned int modulo) {
    // Set seed
    static unsigned int x0 = 12;

    x0 = (a * x0 + b) % modulo;
    return x0;
}
