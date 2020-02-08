#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.hpp"
#include "DEFINITIONS.hpp"
#include "entity/player.hpp"
#include "entity/pipes.hpp"
#include "calculations/collision.hpp"
#include <fstream>

class game : public olc::PixelGameEngine {
public:
  game(){
    sAppName = "flapps";
  }

  bool OnUserCreate() override {
    std::ifstream readFile;
    readFile.open(SCORE_PATH);

    if(readFile.is_open()){
      while(!readFile.eof()){
        readFile >> highScore;
      }
    }
    readFile.close();
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    if(inGame){
      if (GetMouse(0).bPressed){
        player.mousePress();
      }

      current_time += fElapsedTime;
      if(current_time > UPDATE){
        game_update(fElapsedTime);
        current_time = 0;
      }

      //drawing
      Clear(olc::BLACK);
      DrawString(SCREEN_WIDTH / 2, 10, std::to_string(score), olc::WHITE, 4);
      DrawCircle(player.getX(), player.getY(), PLAYER_RADIUS, player.getColor());
      for (pipe &p : pipes.getPipes()){
        DrawRect(p.x, p.upY, PIPE_WIDTH, p.upHeight, pipes.getColor());
        DrawRect(p.x, p.downY, PIPE_WIDTH, p.downHeight, pipes.getColor());
      }
    }
    else {
      //play button clicked, reset everything
      if (GetMouse(0).bPressed){
        if(collis.mouseRectClicked(GetMouseX(), GetMouseY(), ((SCREEN_WIDTH / 2) - (PLAY_BUTTON_WIDTH / 2)), ((SCREEN_HEIGHT / 2) - (PLAY_BUTTON_HEIGHT / 2)), PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT)){
          inGame = true;
          player.reset();
          pipes.reset();
          score = 0;
          save = false;
        }
      }

      current_time += fElapsedTime;
      if(current_time > UPDATE){
        menu_update();
        current_time = 0;
      }

      //drawing
      Clear(olc::BLACK);
      DrawString(10, 10, std::to_string(highScore), olc::WHITE, 4);
      DrawString(SCREEN_WIDTH - (40 * std::to_string(score).size()), 10, std::to_string(score), olc::WHITE, 4);
      DrawString(150, 300, "FLAPPY BIRD", olc::WHITE, 6);
      DrawRect(((SCREEN_WIDTH / 2) - (PLAY_BUTTON_WIDTH / 2)), ((SCREEN_HEIGHT / 2) - (PLAY_BUTTON_HEIGHT / 2)), PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT);
      DrawTriangle(((SCREEN_WIDTH / 2) - (PLAY_BUTTON_WIDTH / 4)), ((SCREEN_HEIGHT / 2) - (PLAY_BUTTON_HEIGHT / 4)), ((SCREEN_WIDTH / 2) - (PLAY_BUTTON_WIDTH / 4)), ((SCREEN_HEIGHT / 2) + (PLAY_BUTTON_HEIGHT / 4)), ((SCREEN_WIDTH / 2) + (PLAY_BUTTON_WIDTH / 4)), (SCREEN_HEIGHT / 2));
    }
    return true;
  }

  void game_update(float fElapsedTime){
    //pipe function calls
    pipes.update(fElapsedTime);
    //collision with pipe
    for (pipe &p : pipes.getPipes()){
      if(collis.circleRectCollision(player.getX(), player.getY(), PLAYER_RADIUS, p.x, p.upY, PIPE_WIDTH, p.upHeight)){ inGame = false; }
      if(collis.circleRectCollision(player.getX(), player.getY(), PLAYER_RADIUS, p.x, p.downY, PIPE_WIDTH, p.downHeight)){ inGame = false; }
      if(!p.collided && collis.circleRectCollision(player.getX(), player.getY(), PLAYER_RADIUS, p.x, p.upY + p.upHeight, PIPE_WIDTH, PIPE_GAP)){
        p.collided = true;
        score++;
      }
    }
    //collision with ground and roof
    if(collis.circleRectCollision(player.getX(), player.getY(), PLAYER_RADIUS, 0, SCREEN_HEIGHT, SCREEN_WIDTH, PLAYER_RADIUS)){ inGame = false; }
    if(collis.circleRectCollision(player.getX(), player.getY(), PLAYER_RADIUS, 0, 0 - PLAYER_RADIUS, SCREEN_WIDTH, PLAYER_RADIUS)){ inGame = false; }
    //player function calls
    player.update(fElapsedTime);
    //drawing
  }

  void menu_update(){
    if(!save){
      std::ofstream writeFile(SCORE_PATH);
      if(writeFile.is_open()){
        if(score > highScore){
          highScore = score;
        }
        writeFile << highScore;
      }
      writeFile.close();
      save = true;
    }
  }


private:
  Player player;
  Pipes pipes;

  collision collis;
  bool save = false;
  bool inGame = false;
  int score = 0;
  int highScore = 0;
  float current_time = 0.0f;
};
