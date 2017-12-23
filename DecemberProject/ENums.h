#pragma once

#define MAXX 9
#define MAXY 9

enum class GameState { 
      MainMenu, 
      Settings, 
      Game ,
      LoadMap ,
      Gen,
};

enum class MapElements : uint8_t {
  Null,
  RoomCenter,
  RoomLeftDown,
  RoomLeftUp,
  RoomRightDown,
  RoomRightUp,
  RoomEndUp,
  RoomEndDown,
  RoomEndLeft,
  RoomEndRight,
  HallVer,
  HallHor,
  HallHorUp,
  HallHorDown,
  HallVerRight,
  HallVerLeft,
};


GameState gameState = GameState::Gen;




