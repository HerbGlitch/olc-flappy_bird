#include "pipes.hpp"

Pipes::Pipes() : color(olc::GREEN){}

void Pipes::SpawnPipes(){
    pipe new_pipe;

    int gapY = (rand() % (SCREEN_HEIGHT - (MIN_PIPE_HEIGHT / 2) - PIPE_GAP));

    new_pipe.upHeight = gapY;
    new_pipe.downHeight = SCREEN_HEIGHT - (gapY + PIPE_GAP);

    new_pipe.upY = 0;
    new_pipe.downY = gapY + PIPE_GAP;

    new_pipe.x = SCREEN_WIDTH + PIPE_WIDTH;

    pipeV.push_back(new_pipe);
}

void Pipes::update(float fElapsedTime){

    if(spawning >= PIPE_SPAWN_TIME){
        SpawnPipes();
        spawning = 0;
    }
    spawning += fElapsedTime;

    for(int i = 0; i < pipeV.size(); i++){
        if(pipeV.at(i).x < 0 - PIPE_WIDTH){ pipeV.erase(pipeV.begin() + i); }
        else { pipeV.at(i).x -= PIPE_SPEED; }
    }

}

void Pipes::reset() {
  pipeV.clear();
}

std::vector<pipe> &Pipes::getPipes(){ return pipeV; }
olc::Pixel Pipes::getColor(){ return color; }
