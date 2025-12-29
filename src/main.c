#include "head.h"
#include "log.h"

int main() {
  init_log();
  init_state();
  input();
  update();
  while (gamestates.runningstate) {
    update();
  }
  return 0;
}