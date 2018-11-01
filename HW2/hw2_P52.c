/*
* Oscar Esparza
* Professor Krovetz
* CSC 152
* 28 September 2018
* from my understanding
* 1 2 3 4 5 6 7 8 9 10 11 12
* = 1 2  3  4
*   5 6  7  8
*   9 10 11 12 
*/

#include <stdio.h>
void P52(unsigned s[12]);
static unsigned rotl(unsigned x, unsigned n); 
/*
int main()
{
    unsigned array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    P52(array);
}*/

void P52(unsigned s[12])
{
    unsigned temp;
    unsigned x, y, z;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            x = rotl(s[0 + j], 24); // rotate left by 24
            y = rotl(s[4 + j], 9);  // rotate left by 9
            z = s[8 + j];
            s[8 + j] = x ^ (z << 1) ^ ((y & z) << 2);
            s[4 + j] = y ^ x ^ ((x | z) << 1);
            s[0 + j] = z ^ y ^ ((x & y) << 3);
        }
        if ((i % 4) == 0)
        {
            temp = s[0];
            s[0] = s[1];
            s[1] = temp;
            temp = s[2]; 
            s[2] = s[3];
            s[3] = temp;
            s[0] = s[0] ^ 0x9e377900 ^ (24 - i);
        }
        else if ((i % 4) == 2)
        {
            temp = s[0];
            s[0] = s[2];
            s[2] = temp;
            temp = s[1];
            s[1] = s[3];
            s[3] = temp;
        }
    }
    /*// for outpout
    for(int i = 0; i < 12; i++)
    {
        printf("%08x\n", s[i]);
    }*/
}

// found at https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
static unsigned rotl(unsigned x, unsigned n) 
{ 
   return (x << n)|(x >> (32 - n)); 
} 