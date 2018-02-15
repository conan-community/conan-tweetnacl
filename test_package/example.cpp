#ifdef __cplusplus
extern "C" {
#endif
#include "tweetnacl.h"

/* Library needs external randombytes implemented */
#ifdef WIN32
#include "Windows.h"
#endif
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void randombytes(unsigned char * ptr,unsigned int length)
{
    char failed = 0;
#ifdef WIN32
    static HCRYPTPROV prov = 0;
    if (prov == 0) {
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, 0)) {
            failed = 1;
        }
    }
    if (!failed && !CryptGenRandom(prov, length, ptr)) {
        failed = 1;
    }
#else
    FILE* fh = fopen("/dev/urandom", "rb");
    if (fh != NULL) {
        if (fread(ptr, length, 1, fh) == 0) {
            failed = 1;
        }
        fclose(fh);
    } else {
        failed = 1;
    }
#endif
    /*
     * yes, this is horrible error handling but we don't have better
     * options from here and I don't want to start changing the design
     * of the library
     */
    if (failed) {
        fprintf(stderr, "Generating random data failed. Please report "
                        "this to https://github.com/ultramancool\n");
        exit(1);
    }
}

#ifdef __cplusplus
}
#endif


int main(int argc, char *argv[]) {
    char secret_key[] = "test_secret_key";
    char content[]  = "test content to sign";
    char sm[strlen(secret_key) + strlen(content)];
    unsigned long long ssize;
    crypto_sign((unsigned char *)sm, &ssize, (unsigned char *) content, strlen(content), (unsigned char *)secret_key);
    printf("%s\n", (char *)sm);
    return 0;
}