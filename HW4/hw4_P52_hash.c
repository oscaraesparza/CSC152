/*
* Oscar Esparza
* Professor Krovetz
* CSC 152
* 31 October 2018
*/

#include "hw3_P52.c"
#include <string.h>

void P52(unsigned s[12]);

// base on the sponge constructions on Serious Crytography P.184
void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes)
{
    unsigned char h[48] = {0}; // what will be passed into perm func
    unsigned bytes = mbytes;

    // absorbing phase
    while(bytes >= 16)  // the rate of 16 bytes
    {
      for(int i = 0; i < 16; i++)
        h[i] = h[i] ^ m[i];

      P52((unsigned int *)h);
      bytes -= 16;
    }

    // add padding
    if(bytes == 0)  // incase we went through the whole thing
    {
        unsigned char t[16] = {0};
        t[0] = 0b10000000;  // 10* padding start
        t[15] = 0b00000001; //10*1 padding end

        for(int i = 0; i < 16; i++)
            h[i] ^= t[i];

        P52((unsigned int *)h);
    }
    else
    {
      unsigned counter = bytes;
      for(int i = 0; i < counter; i++)
      {
            h[i] ^= m[i];
            counter--;
      }
      if(counter == 15)
            h[counter] = 0b10000001;
      else
      {
        h[counter] ^= 0b10000000;
        h[15] ^= 0b00000001;
      }

      P52((unsigned int *)h);
    }

    // squeezing phase
    unsigned squeezeBytes = rbytes;
    // write to output
    while(squeezeBytes >= 16)
    {
      for(int i = 0; i < 16; i++)
        res[i] = h[i];

      P52((unsigned int *)h);
      squeezeBytes -= 16;
    }
    if(squeezeBytes != 0) // leftover
    {
      for(int i = 0; i < squeezeBytes; i++)
        res[i] = h[i];
    }
}
