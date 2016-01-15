//
//  ChessBoard.cpp
//  GomokuChessBoard
//
//  Created by Suu on 15/01/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "ChessBoard.hpp"

using namespace std;

ChessBoard::ChessBoard()
{
    cout << "Initialising chess board" << endl;
    for (int i = 0; i < 15; i ++)
    {
        for (int j = 0; j < 15; j ++)
        {
            this->board[i][j] = 0;
        }
    }
}

void ChessBoard::getBoard(int (*board)[15])
{
    board = this->board;
}

void ChessBoard::printBoard()
{
    cout << "  ";
    for (int i = 0; i < 15*2+1; i++)
    {
        if (i%2==1)
            cout << hex << i/2;
        else
            cout << " ";
    }
    cout << endl;
    cout << "  ";
    for (int i = 0; i < 15*2+1; i++) cout<<"_";
    cout<<endl;
    for (int i = 0; i < 15; i ++)
    {
        cout << hex << i <<"├-";
        for (int j = 0; j < 15; j ++)
        {
            cout << chessSet[this->board[i][j]] << "─";
        }
        cout << "┤" << endl;
    }
    cout << "  ";
    for (int i = 0; i < 15*2+1; i++) cout<<"¯";
    cout<<endl;
}

int ChessBoard::setOnChess(int chess, int x, int y)
{
    if (this->board[x][y] || x>=15 || y>=15)
    {
        return 1;
    }
    else
    {
        this->board[x][y] = chess;
        steps++;
        
        return 0;
    }
}

