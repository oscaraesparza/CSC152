/*
* Oscar Esparza
* Professor Krovetz
* CSC 152
* 31 October 2018
*/

#include <stdio.h>
#include <string.h>
#include "hw4_P52_hash.c"
#define SZ 6

void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes);

int main()
{
  int main(){
    unsigned char tortoise[SZ] = {0};
    unsigned char hare[SZ] = {0};
    unsigned char temp1[SZ], temp2[SZ];

    do{
        //tortoise = H(tortoise)
        P52_hash(tortoise, SZ, tortoise, SZ);

        //hare = H(H(hare))
        P52_hash(hare, SZ, hare, SZ);
        P52_hash(hare, SZ, hare, SZ);

    } while(memcmp(tortoise,hare,SZ)!=0); //while hare != tortoise

    //tortoise = start value
    unsigned char r[SZ] = {0};
    memcpy(tortoise, r, (size_t) SZ);

    //while hare != tortoise
    while(memcmp(tortoise,hare,SZ)!=0){
        //temp1 = tortoise
        memcpy(temp1, tortoise, (size_t) SZ);

        //temp2 = hare
        memcpy(temp2, hare, (size_t) SZ);

        //tortoise = H(temp1)
        P52_hash(temp1, SZ, tortoise, SZ);

        //hare = H(temp2)
        P52_hash(temp2, SZ, hare, SZ);
    }

    // return temp1
    for(int i=0; i < SZ; i++){
        printf("0x%x ",temp1[i]);
    }

    printf("\n");

    //return temp2
    for(int i=0; i < SZ; i++){
        printf("0x%x ",temp2[i]);
    }

    return 0;
}
}
