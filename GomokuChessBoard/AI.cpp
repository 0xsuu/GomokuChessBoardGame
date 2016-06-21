//
//  AI.cpp
//  GomokuChessBoard
//
//  Created by Suu on 21/06/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include <iostream>

#include "AI.hpp"

using namespace std;

tuple<int, int> AI::generateLocation()
{
	int x = -1;
	int y = -1;
	do
	{
		uniform_int_distribution<int> distributionX(cbg->boundary[0],cbg->boundary[1]);
		x = distributionX(randDevice);
		uniform_int_distribution<int> distributionY(cbg->boundary[2],cbg->boundary[3]);
		y = distributionY(randDevice);
	} while (!cbg->myBoard.checkOnBoard(x, y));
	
	return make_tuple(x, y);
}