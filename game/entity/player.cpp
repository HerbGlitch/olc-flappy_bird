#include "player.hpp"

Player::Player(): color(olc::WHITE){}

void Player::update(float fElapsedTime){
  if(jumping < JUMP_SECONDS){
    jumping += fElapsedTime;
    vx = 0;
    vy -= GRAVITY*4;
  }
  else {
    jumping = JUMP_SECONDS;
    vx = 0;
    vy += GRAVITY;
  }

  if(vx > PLAYER_VX_MAX){ vx = PLAYER_VX_MAX; }
  if(vy > PLAYER_VY_MAX){ vy = PLAYER_VY_MAX; }
  if(vx < -PLAYER_VX_MAX){ vx = -PLAYER_VX_MAX; }
  if(vy < -PLAYER_VY_MAX){ vy = -PLAYER_VY_MAX; }

  x += vx;
  y += vy;
}

void Player::reset(){
  x = SCREEN_WIDTH / 6;
  y = SCREEN_HEIGHT / 2;
  vx = 0;
  vy = 0;
}

void Player::mousePress(){
  jumping = 0;
  vy = 0;
}

int Player::getX(){ return x; }
int Player::getY(){ return y; }
olc::Pixel Player::getColor(){ return color; }
