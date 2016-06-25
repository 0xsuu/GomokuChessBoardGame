//
//  Learning.cpp
//  GomokuChessBoard
//
//  Created by Suu on 23/06/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include "Learning.hpp"

using namespace std;

double NBClassifier::getTheta(int feature, int featureValue, bool targetClass)
{
	const int l = 1;
	
	double theta = 0;
	vector<int> distinct;
	int countY = 0;
	auto currentFeature = this->features[feature];
	for (auto it = currentFeature.begin(); it != currentFeature.end(); ++it)
	{
		if (find(distinct.begin(), distinct.end(), *it) == distinct.end())
		{
			distinct.push_back(*it);
		}
		if (this->featureClass[distance(currentFeature.begin(), it)] == targetClass)
		{
			countY ++;
			if (*it == featureValue)
				theta ++;
		}
	}
	
	theta += l;
	theta = theta/(l*distinct.size() + countY);
	//theta = theta/countY;
	return theta;
}

double NBClassifier::getPi(bool targetClass)
{
	double pi = 0;
	
	for (const bool &c : this->featureClass)
	{
		if (c == targetClass)
		{
			pi ++;
		}
	}
	
	pi = pi/this->featureClass.size();
	
	return pi;
}

double NBClassifier::getEstimation(std::vector<int> X, bool Y)
{
	double retVal = 1;
	
	for (auto it = X.begin(); it != X.end(); ++it)
	{
		retVal *= this->getTheta((int)distance(X.begin(), it), *it, Y);
	}
	
	retVal *= this->getPi(Y);
	
	return retVal;
}

double NBClassifier::getProbability(std::vector<int> X, bool Y)
{
	double eY = this->getEstimation(X, Y);
	return eY/(eY+this->getEstimation(X, !Y));
}

