#define CTEST_MAIN
#define CTEST_COLOR_OK
#include "./buf_test.c"

int main(int argc, const char *argv[]) {
  int result = ctest_main(argc, argv);
  return result;
}
