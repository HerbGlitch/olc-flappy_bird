#pragma once

#include "../olcPixelGameEngine.hpp"
#include "../DEFINITIONS.hpp"
#include <vector>

struct pipe {
  int x = 0;
  int upY = 0;
  int downY = 0;
  int upHeight = 0;
  int downHeight = 0;
  int width = PIPE_WIDTH;
  bool collided = false;
};

class Pipes {
public:
  Pipes();
  void SpawnPipes();
  void update(float fElapsedTime);
  void reset();
  std::vector<pipe> &getPipes();
  olc::Pixel getColor();

private:
  std::vector<pipe> pipeV;
  olc::Pixel color;
  int pipe_gap = PIPE_GAP;
  float spawning = PIPE_SPAWN_TIME;
};
