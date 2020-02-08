#include "game.hpp"
#include <time.h>

int main(){
  srand(std::time(nullptr));
  game demo;
  if(demo.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE_X, SCALE_Y)){
    demo.Start();
  }
  return 0;
}
