#include <stdio.h>
#include <string.h>

#include "tweetnacl.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* it's really stupid that there isn't a syscall for this */

static int fd = -1;

void randombytes(unsigned char *x,unsigned long long xlen)
{
  int i;

  if (fd == -1) {
    for (;;) {
      fd = open("/dev/urandom",O_RDONLY);
      if (fd != -1) break;
      sleep(1);
    }
  }

  while (xlen > 0) {
    if (xlen < 1048576) i = xlen; else i = 1048576;

    i = read(fd,x,i);
    if (i < 1) {
      sleep(1);
      continue;
    }

    x += i;
    xlen -= i;
  }
}

int main(int argc, char *argv[]) {
    char secret_key[] = "test_secret_key";
    char content[]  = "test content to sign";
    char sm[strlen(secret_key) + strlen(content)];
    unsigned long long ssize;
    crypto_sign((unsigned char *)sm, &ssize, (unsigned char *) content, strlen(content), (unsigned char *)secret_key);
    printf("%s\n", (char *)sm);
    return 0;
}
