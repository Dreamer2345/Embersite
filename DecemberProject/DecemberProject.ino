#include <Arduboy2.h>
Arduboy2 ard;
Sprites sprites;
uint8_t Map[100];
#include "Enums.h"




void setup() {
  ard.begin();
  ard.clear();
  ard.initRandomSeed();
}



void loop() {
  if(!ard.nextFrame())
    return;

  ard.pollButtons();
  ard.clear();
  
  switch(gameState)
  {
    case GameState::Gen: GenMaze(); gameState = GameState::Game; break;
    case GameState::Game: UpdateGame(); break;
  }

  ard.display();
}
