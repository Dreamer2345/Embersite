#include <Arduboy2.h>
Arduboy2 ard;
Sprites sprites;
#include "Bitmaps.h"
#include "ENums.h"
#include "Maps.h"
#include "Player.h"
PlayerClass Player;
MapElements Map[100];
#include "Game.h"



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
