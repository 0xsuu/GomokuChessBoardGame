//
//  main.cpp
//  GomokuChessBoard
//
//  Created by Suu on 15/01/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include <iostream>
#include "ChessBoard.hpp"
#include "ChessBoardGame.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    ChessBoardGame myGame = ChessBoardGame();
    myGame.startGame(1);
    
    return 0;
}
