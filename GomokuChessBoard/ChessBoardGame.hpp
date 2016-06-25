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

class AI;

class ChessBoardGame
{
private:
    int started;
    
    int play(int player, int x, int y);
    
    void gameover(int lose);
	
	AI *ai1;
	AI *ai2;
    
public:
	void release()
	{
		free(ai1);
		free(ai2);
	}
	
    ChessBoardGame();
	
	ChessBoard myBoard = ChessBoard();
	
    int lastStep[2];
	
	int steps = 0;
    
    int P1();
    int P2();
	
	int boundary[4] = {7, 7, 7, 7};
	
    void startGame(int first);

};

#endif /* ChessBoardGame_hpp */
