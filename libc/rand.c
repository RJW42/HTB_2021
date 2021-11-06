#include "rand.h"
#include "../cpu/timer.h"

static unsigned int seed = 1;

void srand (int newseed) {
    seed = (unsigned)newseed & 0x7fffffffU;
}
unsigned int generate_rand (unsigned int modulo) {
    seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
    return ((unsigned int)seed) % modulo;
}
