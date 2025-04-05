#include <stdio.h>

void run(){
  char buffer[1024];
  char ch;
  {
    fgets(buffer, 1023, stdin);
    ch = buffer[0];
  }
  puts("hello world");
  putchar(ch);
}

int main() {
  run();
  return 0;
}


