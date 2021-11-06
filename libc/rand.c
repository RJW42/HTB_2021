static int a = 9;       // multiplier
static int b = 13;      // increment
static int m = 17;      // modulus


int generate_rand() {
    // Set seed
    static int x0 = 12;

    x0 = (a * x0 + b) % m;
    return x0;
}
