/**
 * @file hw3_ctr.c
 * @author Ted Krovetz
 * @date 3 October 2018
 * @brief Encrypts or decrypts stdin to stdout
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONCE_LEN 12
#define BLK_LEN 48
#define KEY_LEN 48

void P52(unsigned s[12]);

int main(int argc, const char* argv[]) {
    size_t bytes_read;
    unsigned char key[KEY_LEN] = {0};  /* Auto init to all zeros */
    unsigned char nonce[NONCE_LEN];
    unsigned char blk[BLK_LEN];

    /* Setup key and nonce. Report command line errors */
    if ((argc == 3) && (strlen(argv[1]) == 1) && (strlen(argv[2]) <= KEY_LEN) &&
                    ((argv[1][0] == 'e') || (argv[1][0] == 'd'))) {
        if (argv[1][0] == 'e') {
            FILE *rand = fopen("/dev/urandom", "rb");
            fread(nonce, 1, NONCE_LEN, rand);
            fclose(rand);
            fwrite(nonce, 1, NONCE_LEN, stdout);
        } else {
            fread(nonce, 1, NONCE_LEN, stdin);
        }
        memcpy(key, argv[2], strlen(argv[2]));
    } else {
        fprintf(stderr, "usage: %s d|e <pwd up to 48 chars>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned char paddedNonce[BLK_LEN];
    do {
        bytes_read = fread(blk, 1, BLK_LEN, stdin);
        if (bytes_read > 0) {
            // process bytes_read bytes
            for (int i = 0; i < NOUNCE_LEN; i++)  // create a copy on the nonce
              paddedNonce =[i] = nonce[i];

            for(int i = NONCE_LEN; i < BLK_LEN; i++)  // add counter after the nonce
                paddedNonce[i] = counter[i];

            for (int i = 0; i < bytes_read; i++)  // time to XOR our padded nonce
              
            // end process btyes_read bytes
            fwrite(blk, 1, bytes_read, stdout);
        }
    } while (bytes_read == BLK_LEN);
    return EXIT_SUCCESS;
}
