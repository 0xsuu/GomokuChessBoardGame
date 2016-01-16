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
    cout << endl;
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

int ChessBoard::checkWin()
{
    int i = this->scanLines(5);
    int j = this->scanDiagonals(5);
    if (i)
        return i;
    else if (j)
        return j;
    else
        return 0;
}

//Private Methods

int ChessBoard::scanLines(int num)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            //Check vertical five
            if (this->board[i][j]==this->board[i][j+1] && this->board[i][j])
            {
                this->countH++;
                if (countH==num-1)
                {
                    this->countH=0;
                    return this->board[i][j];
                }
            }
            else
            {
                this->countH=0;
            }
            
            //Check horizontal five
            if (this->board[j][i]==this->board[j+1][i] && this->board[j][i])
            {
                this->countV++;
                if (this->countV==num-1)
                {
                    this->countV=0;
                    return this->board[j][i];
                }
            }
            else
            {
                this->countV=0;
            }
        }
        this->countH = 0;
        this->countV = 0;
    }
    return 0;
}

int ChessBoard::scanDiagonals(int num)
{
    for (int j = 0; j < 16-num; j ++)
    {
        for (int i = j; i < 14; i ++)
        {
            if (this->board[i][i-j]==this->board[i+1][i-j+1] && this->board[i][i-j])
            {
                this->countD1++;
                if (this->countD1==num-1)
                {
                    this->countD1=0;
                    return this->board[i][i-j];
                }
            }
            else
            {
                this->countD1 = 0;
            }
            
            if (this->board[i-j][i]==this->board[i-j+1][i+1] && this->board[i-j][i])
            {
                this->countD2++;
                if (this->countD2==num-1)
                {
                    this->countD2=0;
                    return this->board[i-j][i];
                }
            }
            else
            {
                this->countD2 = 0;
            }
            
            if (this->board[i-j][14-i]==this->board[i-j+1][14-i-1] && this->board[i-j][14-i])
            {
                this->countD3++;
                if (this->countD3==num-1)
                {
                    this->countD3=0;
                    return this->board[i-j][14-i];
                }
            }
            else
            {
                this->countD3 = 0;
            }
            
            if (this->board[i-j+1][13-i+2*j]==this->board[i-j+1+1][13-i+2*j-1] && this->board[i-j+1][13-i+2*j])
            {
                this->countD4++;
                if (this->countD4==num-1)
                {
                    this->countD4=0;
                    return this->board[i-j+1][13-i+2*j];
                }
            }
            else
            {
                this->countD4 = 0;
            }
        }
        this->countD1 = 0;
        this->countD2 = 0;
        this->countD3 = 0;
        this->countD4 = 0;
    }
    return 0;
}
