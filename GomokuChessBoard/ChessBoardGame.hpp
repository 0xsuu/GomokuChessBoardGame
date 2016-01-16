//
//  ChessBoardGame.hpp
//  GomokuChessBoard
//
//  Created by Suu on 15/01/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef ChessBoardGame_hpp
#define ChessBoardGame_hpp

#include <iostream>
#include "ChessBoard.hpp"

class ChessBoardGame
{
private:
    ChessBoard myBoard = ChessBoard();
    int started;
    
    int play(int player, int x, int y);
    
    void gameover(int lose);
    
public:
    ChessBoardGame();
    
    int lastStep[2];
    
    int P1();
    int P2();
    
    void startGame(int first);

};

#endif /* ChessBoardGame_hpp */
