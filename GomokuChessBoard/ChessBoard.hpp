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
    int board[15][15];
    int steps;
    
    int countH=0;
    int countV=0;
    int countD1=0;
    int countD2=0;
    int countD3=0;
    int countD4=0;
    int scanLines(int num);
    int scanDiagonals(int num);
	
	int w_p1Start = 0; //and p5
	int w_p2Start = 0; //and p6
	int w_p3Start = 0;
	int w_p4Start = 0;
    
public:
	int w_p1 = 0; //oo
	int w_p2 = 0; //ooo
	int w_p3 = 0; //oooo
	int w_p4 = 0; //ooooo
	int w_p5 = 0; //oox
	int w_p6 = 0; //ooox
	int w_p7 = 0; //o+o
	int w_p8 = 0; //o+oo
	int w_p9 = 0; //o+ooo
	int w_p10 = 0; //o+ox
	int w_p11 = 0; //o+oox
	int w_p12 = 0; //o+ooox
	
    ChessBoard();
    void getBoard(int board[15][15]);
    void printBoard();
    int setOnChess(int chess, int x, int y);
	bool checkOnBoard(int x, int y);
    int checkWin();
};

#endif /* ChessBoard_h */
