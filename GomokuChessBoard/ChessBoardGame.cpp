//
//  ChessBoardGame.cpp
//  GomokuChessBoard
//
//  Created by Suu on 15/01/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include "ChessBoardGame.hpp"
#include "AI.hpp"
#include <tuple>

using namespace std;

ChessBoardGame::ChessBoardGame()
{
    this->started = 0;
	
	ai1 = new AI(true, this);
	ai2 = new AI(false, this);
}

int ChessBoardGame::P1()
{
    //Add AI here
    //this->myBoard->getChessBoard(int board[15][15]);
    //this->LastStep
	
	tuple<int,int> t = ai1->generateLocation();
	cout << "AI 1 played " << get<0>(t) << " " << get<1>(t) << endl;
    return this->play(1, get<0>(t), get<1>(t));
}

int ChessBoardGame::P2()
{
    //Add AI here
    //this->myBoard->getChessBoard(int board[15][15]);
    //this->LastStep
	
    tuple<int,int> t = ai2->generateLocation();
	cout << "AI 2 played " << get<0>(t) << " " << get<1>(t) << endl;
    return this->play(2, get<0>(t), get<1>(t));
	
	/*
	int x, y;
	cout << "P2: ";
	scanf("%d, %d", &x, &y);
	return this->play(2, x, y);
	*/
}

int ChessBoardGame::play(int player, int x, int y)
{
    if (this->myBoard.setOnChess(player, x, y))
    {
        gameover(player);
        return 1;
    }
    else
    {
        if (int win = this->myBoard.checkWin())
        {
            gameover(3 ^ win);
            return 1;
        }
        else
        {
            myBoard.printBoard();
            this->lastStep[0] = x;
            this->lastStep[1] = y;
        }
    }
 
	if (x-1<boundary[0] && x-1>=0) boundary[0]=x-1;
	else if (x+1>boundary[1] && x+1<=14) boundary[1]=x+1;
	if (y-1<boundary[2] && y-1>=0) boundary[2]=y-1;
	else if (y+1>boundary[3] & y+1<=14) boundary[3]=y+1;
	
    return 0;
}

void ChessBoardGame::startGame(int first)
{
    this->started = 1;
    //this->myBoard.printBoard();
    if (first == 2)
    {
        if (P2())
        {
            gameover(2);
            return;
        }
    }
    
    while (this->started)
    {
        if (P1() || P2()) return;
    }
}

void ChessBoardGame::gameover(int lose)
{
    this->started = 0;
    this->myBoard.printBoard();
    int win = 3 ^ lose;
    cout << "Player " << win << " Wins" << endl;
}
