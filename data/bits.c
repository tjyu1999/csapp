/* 
 * CS:APP Data Lab
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

/* 
 * bitXor - x ^ y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 0x01 << 31;
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    return !((~x ^ (x + 1)) | !(x + 1)); // mind the case when x = -1
}

/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int mask = 0xAA;
    mask = mask + (mask << 8) + (mask << 16) + (mask << 24); // 0xAAAAAAAA
    
    return !((x & mask) ^ mask);
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}

/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int Tmin = 0x01 << 31;
    
    return !((x + ~0x30 + 1) & Tmin) & !((0x39 + ~x + 1) & Tmin);
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2, 4, 5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    x = !x + ~0;
    
    return (x & y) | (~x & z);
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4, 5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int x_sign = x >> 31;
    int y_sign = y >> 31;
    
    return (x_sign & !y_sign) | (!(x_sign ^ y_sign) & !((y + ~x + 1) >> 31));
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    return ~((x | (~x + 1)) >> 31) & 0x01;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12)  = 5           // 01100      (8 + 4)
 *            howManyBits(298) = 10          // 0100101010 (256 + 32 + 8 + 2)
 *            howManyBits(-5)  = 4           // 1011       (-8 + 3)
 *            howManyBits(0)   = 1           // 0
 *            howManyBits(-1)  = 1           // 1          (-1)
 *            howManyBits(0x80000000) = 32  
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {    
    x = x ^ (x >> 31);
    int b16 = !!(x >> 16) << 4;
    
    x = x >> b16;
    int b8 = !!(x >> 8) << 3;
    
    x = x >> b8;
    int b4 = !!(x >> 4) << 2;
    
    x = x >> b4;
    int b2 = !!(x >> 2) << 1;
    
    x = x >> b2;
    int b1 = !!(x >> 1);
    
    x = x >> b1;
    int b0 = x;

    return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}

/* 
 * floatScale2 - Return bit-level equivalent of expression 2 * f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned s = (uf >> 31) & 0x01;
    unsigned e = (uf >> 23) & 0xff;
    unsigned f = uf & 0x7fffff;
    
    if (!e)
        return (s << 31) | (f << 1);
    if (!(e ^ 0xff))
        return uf;
        
    return (s << 31) | ((e + 1) << 23) | f;
}

/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int)f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int s = (uf >> 31) & 0x011;
    int e = (uf >> 23) & 0xff;
    int f = uf & 0x7fffff;
    
    if (!(e | f))
        return 0;
        
    e = e - 127;
    if (e < 0)
        return 0;
    if (e > 30 + (s & !f)) // if s = 1 & f = 0 then -2^31 is the minimun of legal representation
        return 0x80000000u;
        
    f = ((1 << 23) | f) >> (23 - e);
    
    return s ? -f : f;
}

/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    x = x + 127;
    if (x < 0)
        return 0;
        
    return (x < 255) ? (x << 23) : 0x7f800000u;
}
