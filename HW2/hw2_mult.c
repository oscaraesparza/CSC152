/*
* Oscar Esparza
* Professor Krovetz
* CSC 152
* 30 September 2018
*/
#include<stdio.h>

unsigned mult(unsigned a, unsigned b, unsigned modulus, unsigned degree)
{
    unsigned extra = 0;
    while (a != 0)
    {
        // checks x^0
        if(a & 1)
        {
            a--; 
            extra = extra ^ b;
        }
        // a / x
        a = a >> 1;
        // b * x
        b = b << 1;
        if (b & (degree << 2))
            b = b ^ modulus; 
    }
    return (a * b + extra);
}