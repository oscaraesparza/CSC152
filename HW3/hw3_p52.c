/*
* Oscar Esparza
* Professor Krovetz
* CSC 152
* 13 October 2018
*/
#include <stdio.h>
#include <string.h>
#include <immintrin.h>

//void P52(unsigned s[12]);
/*
int main() {
    unsigned char buf[48] = {0};
    unsigned char expected[48] = {
        0xC4,0xD8,0x67,0x64,0x3B,0xF8,0xDC,0x07,0xD4,0xB0,0x0B,0x3B,0x4C,0x36,
        0x21,0x1B,0xDC,0x31,0x34,0x08,0x8E,0xBE,0xFB,0x0E,0x84,0xE8,0x54,0x00,
        0x55,0xD9,0x8B,0x64,0x2E,0xB4,0x5D,0x4A,0xCB,0x41,0x06,0xCA,0xC2,0xD2,
        0x73,0x86,0x09,0xD8,0x30,0x2E};
    P52((unsigned *)buf);
    if (memcmp(buf,expected,48)==0)
        printf("Pass\n");
    else
        printf("No Pass\n");
    return 0;
}*/

void P52(unsigned s[12])
{
    for (int i = 0; i < 24; i++)
    {
        __m128i r0 = _mm_loadu_si128((__m128i *) s);  //load register 0
        __m128i temp0 = _mm_slli_epi32(r0, 24);       // shift left by 24
        __m128i temp1 = _mm_srli_epi32(r0, 8);        // shift right by 8
        r0 = _mm_xor_si128(temp0,temp1);              // or the results togeter
        _mm_storeu_si128((__m128i *)s,r0);            // load back in to s 

        __m128i r1 = _mm_loadu_si128((__m128i *) &s[4]);  //load register 1
        temp0 = _mm_slli_epi32(r1, 9);                    // shift left by 9
        temp1 = _mm_srli_epi32(r1, 23);                   // shift right by 23
        r1 = _mm_xor_si128(temp0,temp1);                  // or the results togeter
        _mm_storeu_si128((__m128i *) &s[4] ,r1);          // load back in to s 

        __m128i r2 = _mm_loadu_si128((__m128i *) &s[8]);  //load register 0
        _mm_storeu_si128((__m128i *) &s[8] ,r2);          // load back in to s 

        temp0 =  _mm_slli_epi32(_mm_and_si128(r1, r2), 2); // ((y & z) << 2)
        temp1 = _mm_xor_si128(r0,_mm_slli_epi32(r2, 1));   // x ^ (z << 1)
        __m128i result =  _mm_xor_si128(temp0, temp1);     //  x ^ (z << 1) ^ ((y & z) << 2)
        _mm_storeu_si128((__m128i *) &s[8] ,result);

        temp0 =  _mm_slli_epi32(_mm_or_si128(r0, r2), 1); //((x | z) << 1)
        temp1 = _mm_xor_si128(r1,r0);                     // y ^ x
        result = _mm_xor_si128(temp0, temp1);             // y ^ x ^ ((x | z) << 1)
        _mm_storeu_si128((__m128i *) &s[4] ,result);

        temp0 = _mm_slli_epi32(_mm_and_si128(r0, r1), 3); // ((x & y) << 3)
        temp1 = _mm_xor_si128(r2,r1);                     // z ^ y
        result = _mm_xor_si128(temp0, temp1);             // z ^ y ^ ((x & y) << 3)
        _mm_storeu_si128((__m128i *) &s[0] ,result);

        if ((i % 4) == 0)
        {
            r0 = _mm_loadu_si128((__m128i*)s);
            __m128i shuffle = _mm_shuffle_epi32(r0, 0b10110001);  //2 3 0 1 
            _mm_storeu_si128((__m128i*)s, shuffle);
            s[0] = s[0] ^ 0x9e377900 ^ (24 - i);
        }
        else if ((i % 4) == 2)
        {
            r0 = _mm_loadu_si128((__m128i*) s);
            __m128i shuffle = _mm_shuffle_epi32(r0, 0b01001110);  //1 0 3 2
            _mm_storeu_si128((__m128i*)s, shuffle);
        }
    }
}
