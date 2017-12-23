#pragma once
struct UPoint{
  uint8_t x;
  uint8_t y;
  bool Used;
};


void InitMap(){
  for(uint8_t i=0; i<100; i++){
    Map[i] = MapElements::Null;
  }
}

uint8_t GetOffset(uint8_t x,uint8_t y){ return (x+(y*MAXX));}

void AddToStack(UPoint * s,UPoint cp){
  for(uint8_t i=0; i<100; i++){
    if (s[i].Used == false) {
      s[i].x = cp.x;
      s[i].y = cp.y;
      s[i].Used = true;
      break;
    }
  }
}

UPoint RemoveFromStack(UPoint * s){
  UPoint p;
  for(uint8_t i=100; i>0; i--){
    if (s[i].Used == true) {
      p.x = s[i].x;
      p.y = s[i].y;
      s[i].Used = false;
      break;
    }
  }
}

bool CheckDir(uint8_t d,uint8_t _x,uint8_t _y){
  uint8_t x = _x;
  uint8_t y = _y;

  switch(d){
    case 0:y++;break;
    case 1:y--;break;
    case 2:x++;break;
    case 3:x--;break;
  };

  if (x > MAXX) {return false;}
  if (y > MAXY) {return false;}

  if (Map[GetOffset(x,y)] == MapElements::Null) {return true;}
  else {return false;}  
}

void SetMapCurrent(UPoint Cur,uint8_t d){
  MapElements Elem = Map[GetOffset(Cur.x,Cur.y)];
  MapElements Elem1 = MapElements::Null;
  if (Elem == MapElements::Null) {
    switch(d){
      case 0:Elem1 = MapElements::RoomEndDown; break;
      case 1:Elem1 = MapElements::RoomEndUp; break;
      case 2:Elem1 = MapElements::RoomEndLeft; break;
      case 3:Elem1 = MapElements::RoomEndRight; break;
      };
  } else {
    switch(Elem){
      case MapElements::RoomEndUp: if (d != 0){switch(d){
                                                case 1:Elem1 = MapElements::HallVer; break;
                                                case 2:Elem1 = MapElements::RoomRightUp; break;
                                                case 3:Elem1 = MapElements::RoomLeftUp; break;
                                                };
                                    } break;
      case MapElements::RoomEndDown: if (d != 1){switch(d){
                                                case 0:Elem1 = MapElements::HallVer; break;
                                                case 2:Elem1 = MapElements::RoomRightDown; break;
                                                case 3:Elem1 = MapElements::RoomLeftDown; break;
                                                };
                                    } break;
      case MapElements::RoomEndRight: if (d != 2){switch(d){
                                                case 1:Elem1 = MapElements::RoomRightDown; break;
                                                case 0:Elem1 = MapElements::RoomRightUp; break;
                                                case 3:Elem1 = MapElements::HallHor; break;
                                                };
                                    } break;
      case MapElements::RoomEndLeft: if (d != 3){switch(d){
                                                case 1:Elem1 = MapElements::RoomLeftDown; break;
                                                case 0:Elem1 = MapElements::RoomLeftUp; break;
                                                case 2:Elem1 = MapElements::HallHor; break;
                                                };
                                    } break;
    }
  }
  Map[GetOffset(Cur.x,Cur.y)] = Elem1;
}


uint8_t CheckSuround(UPoint Cur){
  uint8_t x = Cur.x;
  uint8_t y = Cur.y;
  bool p[4];
  uint8_t Usable = 0;
  
  for (uint8_t i=0; i<4;i++){
    p[i] = CheckDir(i,x,y);
    if (p[i] == true) Usable++;
  }
  if (Usable == 0) {return 0;}
  else {
    uint8_t Rcount = random(0,Usable);
    for (uint8_t i=0; i<4;i++){
        if (p[i] == true) {
        if (Rcount != 0){Rcount--;}
        else{
          Usable = i;
          break;
        }
        }
    }
  }
  
  return Usable+1;
}






void GenMaze(){
    uint8_t Used = 99;
    UPoint Stack[100];
    UPoint CurPoint;
    InitMap();
    CurPoint.x = random(0,9);
    CurPoint.y = random(0,9);
    uint8_t d = random(0,3);
    MapElements Elem1;
    switch(d){
      case 0:Elem1 = MapElements::RoomEndUp; break;
      case 1:Elem1 = MapElements::RoomEndDown; break;
      case 2:Elem1 = MapElements::RoomEndRight; break;
      case 3:Elem1 = MapElements::RoomEndLeft; break;
      };
    Map[GetOffset(CurPoint.x,CurPoint.y)] = Elem1;
    AddToStack(Stack,CurPoint);

    

    while (Used > 0){
      if (CheckDir(d,CurPoint.x,CurPoint.y)){
          switch(d){
            case 0:CurPoint.y++;break;
            case 1:CurPoint.y--;break;
            case 2:CurPoint.x++;break;
            case 3:CurPoint.x--;break;
          };

          AddToStack(Stack,CurPoint);
          SetMapCurrent(CurPoint,d);
          Used--;
          if (random(0,10) == 0){
            d = random(0,3);
          }
          
      } else {
        if (CheckSuround(CurPoint) != 0){
          d = CheckSuround(CurPoint)-1;
        } else {
          while (CheckSuround(CurPoint) == 0){
            CurPoint = RemoveFromStack(Stack);
          }
        }
      }
    }
}

void UpdateGame(){
  for(uint8_t i=0; i<10; i++){
    for(uint8_t j=0; j<10; j++){
      ard.print('o');
    }
    ard.println();
  }
}

