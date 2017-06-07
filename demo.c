extern void __stdcall proc_main(void);

#include <stdio.h>

int main(void)
{
  printf("demo.c: main\n");
  proc_main();
  return 0; 
}
