#pragma once

#include "../olcPixelGameEngine.hpp"
#include "../DEFINITIONS.hpp"

class Player {
public:
  Player();
  void reset();
  void update(float fElapsedTime);
  void mousePress();
  int getX();
  int getY();
  olc::Pixel getColor();
private:
  olc::Pixel color;
  int x = SCREEN_WIDTH / 6;
  int y = SCREEN_HEIGHT / 2;
  float vx;
  float vy;
  float jumping = JUMP_SECONDS;
};
