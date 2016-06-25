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
#include "AI.hpp"

#include <fstream>

using namespace std;

int main(int argc, const char * argv[])
{
    ChessBoardGame myGame = ChessBoardGame();
	/*if (train)
	{
		for (int i = 0; i < 100; i++)
		{
			cout << "training... "<< i << endl;
			myGame.startGame(1);
			myGame.release();
		}
	}
	else
	{*/
		myGame.startGame(1);
		myGame.release();
	//}
	
    return 0;
}



// Test of bayesian classifier
/*
vector<int> a = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
vector<int> b = {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0};

vector<vector<int>> features;

features.push_back(a);
features.push_back(b);

vector<bool> cls;

for (int i = 0; i < 19; i++)
cls.push_back(true);
for (int i = 0; i < 31; i++)
cls.push_back(false);

NBClassifier BC = NBClassifier(features, cls);

cout << BC.getProbability({1,1}, true)*100<<"%" << endl;
*/