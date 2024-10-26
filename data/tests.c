/* Testing Code */

#include <limits.h>
#include <math.h>

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
    union {
        unsigned u;
        float f;
    } a;
    
    a.u = u;
    
    return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
    union {
        unsigned u;
        float f;
    } a;
    
    a.f = f;
    
    return a.u;
}

int test_bitXor(int x, int y) {
  return x ^ y;
}

int test_tmin(void) {
  return 0x80000000;
}

int test_isTmax(int x) {
    return x == 0x7FFFFFFF;
}

int test_allOddBits(int x) {
    for (int i = 1; i < 32; i += 2) {
        if ((x & (1 << i)) == 0)
            return 0;
    }
    
    return 1;
}

int test_negate(int x) {
    return -x;
}

int test_isAsciiDigit(int x) {
    return (0x30 <= x) && (x <= 0x39);
}

int test_conditional(int x, int y, int z) {
    return x ? y : z;
}

int test_isLessOrEqual(int x, int y) {
    return x <= y;
}

int test_logicalNeg(int x) {
    return !x;
}

int test_howManyBits(int x) {
    unsigned int a;
    unsigned int cnt;
    
    x = x < 0 ? -x - 1 : x;
    a = (unsigned int)x;
    for (cnt = 0; a; a >>= 1, ++cnt)
        ;

    return (int)(cnt + 1);
}

unsigned test_floatScale2(unsigned uf) {
    float f = u2f(uf);
    float tf = 2 * f;
    
    if (isnan(f))
        return uf;
    else
        return f2u(tf);
}

int test_floatFloat2Int(unsigned uf) {
    float f = u2f(uf);
    int x = (int)f;
    
    return x;
}

unsigned test_floatPower2(int x) {
    float p2 = 2.0;
    float result = 1.0;
    
    if ((unsigned)x == 0x80000000)
        return 0;
    if (x < 0) {
        x = -x;
        p2 = 0.5;
    }
    
    while (x > 0) {
        if (x & 0x01)
            result = result * p2;
        
        p2 = p2 * p2;
        x >>= 1;
    }
    
    return f2u(result);
}
