static x0 = 12;  // seed
static a;        // multiplier
static b;        // increment
static m;        // modulus


int generate_rand() {
    static x0 = (a * x0 + b) % m;
    return x0;
}
