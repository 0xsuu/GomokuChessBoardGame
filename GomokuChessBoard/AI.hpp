//
//  AI.hpp
//  GomokuChessBoard
//
//  Created by Suu on 21/06/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <iostream>
#include <tuple>
#include <random>

#include "ChessBoardGame.hpp"

class AI
{
public:
	AI() {}
	
	AI(bool black, ChessBoardGame *cbg)
	{
		this->black = black;
		this->cbg = cbg;
	}
	
	std::tuple<int, int> generateLocation();
	
private:
	ChessBoardGame *cbg;
	bool black;
	std::random_device randDevice;	
};

#endif /* AI_hpp */