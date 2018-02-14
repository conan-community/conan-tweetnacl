#include <stdio.h>
#include <string.h>

#include "tweetnacl.h"

int main(int argc, char *argv[]) {
    char secret_key[] = "test_secret_key";
    char content[]  = "test content to sign";
    char sm[strlen(secret_key) + strlen(content)];
    unsigned long long ssize;
    printf("testing crypto_sign\n");
    crypto_sign((unsigned char *)sm, &ssize, (unsigned char *) content, strlen(content), (unsigned char *)secret_key);
    printf("crypto_sign called %llu len sm %lu\n", ssize, strlen(sm));
    printf("%s\n", (char *)sm);
    return 0;
}
