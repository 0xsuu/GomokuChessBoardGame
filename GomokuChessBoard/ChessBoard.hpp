//
//  ChessBoard.h
//  GomokuChessBoard
//
//  Created by Suu on 15/01/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef ChessBoard_h
#define ChessBoard_h

class ChessBoard
{
    const int boardSize = 15;
    const std::string chessSet[3] = {"+", "O", "X"};
    
private:
	
    int steps;
    
    int countH=0;
    int countV=0;
    int countD1=0;
    int countD2=0;
    int countD3=0;
    int countD4=0;
    int scanLines(int num);
    int scanDiagonals(int num);
    
public:
	int board[15][15];
	
    ChessBoard();
	void clearBoard();
    void getBoard(int board[15][15]);
    void printBoard();
    int setOnChess(int chess, int x, int y);
	int checkOnBoard(int x, int y);
    int checkWin();
};

#endif /* ChessBoard_h */
