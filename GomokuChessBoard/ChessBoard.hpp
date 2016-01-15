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
    
public:
    ChessBoard();
    void getBoard(int board[15][15]);
    void printBoard();
    int setOnChess(int chess, int x, int y);
};

#endif /* ChessBoard_h */
