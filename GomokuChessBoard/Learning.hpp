//
//  Learning.hpp
//  GomokuChessBoard
//
//  Created by Suu on 23/06/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#ifndef Learning_hpp
#define Learning_hpp

#include <iostream>
#include <vector>

class NBClassifier
{
public:
	NBClassifier(){};
	
	NBClassifier(std::vector<std::vector<int>> Xs, std::vector<bool> Y)
	{
		this->features = Xs;
		this->featureClass = Y;
	}
	
	double getEstimation(std::vector<int>X, bool Y);
	double getProbability(std::vector<int>X, bool Y);
	
	
private:
	std::vector<std::vector<int>> features;
	std::vector<bool> featureClass;
	
	double getTheta(int feature, int featureValue, bool targetClass);
	double getPi(bool targetClass);
	
};

#endif /* Learning_hpp */
