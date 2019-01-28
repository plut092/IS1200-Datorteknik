#include "stdio.h"

int main() {
  int i = 1;
  (volatile) * PORT = 0x8000abc0;
  PORT = 0x00000000;
  int port_stored = 0;
  printf("%x10x\n", PORT);
  do {
    PORT = 0xaaaaaaaa;
    if (PORT != port_stored) {
    port_stored = PORT;
    }
  } while(int i > 0);{
    if (PORT != port_stored) {
      port_stored = PORT;
    }
    i++;
  }
  return 0;
}
