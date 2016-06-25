//
//  AI.cpp
//  GomokuChessBoard
//
//  Created by Suu on 21/06/2016.
//  Copyright © 2016 suu. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <map>

#include "AI.hpp"

using namespace std;

void AI::endGame(int totalSteps, bool win)
{
	for (vector<int> const& r : recordDifference)
	{
		for (int const& c : r)
		{
			csvWriter << c;
			csvWriter << ',';
		}
		csvWriter << '\n';
	}
	
/*
	this->scanBoard(1);
	this->scanBoard(2);
	
	vector<int> cWP(wP);
	vector<int> cBP(bP);
	
	wP = {0,0,0,0,0,0,0,0,0,0};
	bP = {0,0,0,0,0,0,0,0,0,0};
	
	copy(&(cbg->myBoard.board[0][0]), &(cbg->myBoard.board[0][0]) + 225, &(this->mindBoard[0][0]));
	
	mindBoard[cbg->lastStep[0]][cbg->lastStep[1]] = 0;
	
	this->scanBoard(1);
	this->scanBoard(2);
	
	for (int i = 0; i < 20; i ++)
	{
		vector<int> diff;
		
		for (int i = 0; i < 10; i ++)
		{
			diff.push_back(cBP[i]-bP[i]);
		}
		for (int const& c : diff)
		{
			csvWriter << c;
			csvWriter << ',';
		}
		csvWriter << win << '\n';
		
		diff = {};
		
		for (int i = 0; i < 10; i ++)
		{
			diff.push_back(cWP[i]-wP[i]);
		}
		for (int const& c : diff)
		{
			csvWriter << c;
			csvWriter << ',';
		}
		csvWriter << !win << '\n';
		
		wP = {0,0,0,0,0,0,0,0,0,0};
		bP = {0,0,0,0,0,0,0,0,0,0};
	}
	*/
	
	csvWriter.close();
}

void AI::learnHuman(int x, int y)
{
	copy(&(cbg->myBoard.board[0][0]), &(cbg->myBoard.board[0][0]) + 225, &(this->mindBoard[0][0]));
	
	this->scanBoard(1);
	this->scanBoard(2);
	
	vector<int> cWP(wP);
	vector<int> cBP(bP);
	
	wP = {0,0,0,0,0,0,0,0,0,0};
	bP = {0,0,0,0,0,0,0,0,0,0};
	
	for (int i = cbg->boundary[0]; i <= cbg->boundary[1]; i++)
	{
		for (int j = cbg->boundary[2]; j <= cbg->boundary[3]; j++)
		{
			if (!mindBoard[i][j] || (i == x && j == y))
			{
				mindBoard[i][j] = black+1;
				this->scanBoard(1);
				
				vector<int> diff;
				
				for (int i = 0; i < 10; i ++)
				{
					diff.push_back(wP[i]-cWP[i]);
					features[i].push_back(wP[i]-cWP[i]);
				}
				
				if (i == x && j == y)
				{
					diff.push_back(1);
					featureClass.push_back(true);
				}
				else
				{
					diff.push_back(0);
					featureClass.push_back(false);
				}
				
				recordDifference.push_back(diff);
				
				wP = {0,0,0,0,0,0,0,0,0,0};
				
				countBP = 0;
				countWP = 0;
				mindBoard[i][j] = 0;
			}
		}
	}
}

tuple<int, int> AI::generateLocation()
{
	if (cbg->myBoard.checkOnBoard(7, 7))
	{//Scan when started
		this->scanBoard(1);
		this->scanBoard(2);
		
		vector<int> tmp;// = {cbg->steps};
		if (black)
		{
			tmp.insert(tmp.end(), bP.begin(), bP.end());
			tmp.insert(tmp.end(), wP.begin(), wP.end());
		}
		else
		{
			tmp.insert(tmp.end(), wP.begin(), wP.end());
			tmp.insert(tmp.end(), bP.begin(), bP.end());
		}
		
		wP = {0,0,0,0,0,0,0,0,0,0};
		bP = {0,0,0,0,0,0,0,0,0,0};
		
		record.push_back(tmp);
	}
	
	int x = -1;
	int y = -1;
	do
	{
		uniform_int_distribution<int> distributionX(cbg->boundary[0],cbg->boundary[1]);
		x = distributionX(randDevice);
		uniform_int_distribution<int> distributionY(cbg->boundary[2],cbg->boundary[3]);
		y = distributionY(randDevice);
	} while (cbg->myBoard.checkOnBoard(x, y));
	
	return make_tuple(x, y);
}

tuple<int, int> AI::searchBestLocation()
{
	map<tuple<int, int>, double> heuMap;
	
	/*if (train)
	{
		return generateLocation();
		if (cbg->myBoard.checkOnBoard(7, 7))
		{//Scan when started
			this->scanBoard(1);
			this->scanBoard(2);
			
			vector<int> tmp;// = {cbg->steps};
			if (black)
			{
				tmp.insert(tmp.end(), bP.begin(), bP.end());
				tmp.insert(tmp.end(), wP.begin(), wP.end());
			}
			else
			{
				tmp.insert(tmp.end(), wP.begin(), wP.end());
				tmp.insert(tmp.end(), bP.begin(), bP.end());
			}
			
			wP = {0,0,0,0,0,0,0,0,0,0};
			bP = {0,0,0,0,0,0,0,0,0,0};
			
			record.push_back(tmp);
		}
	}*/
		
	copy(&(cbg->myBoard.board[0][0]), &(cbg->myBoard.board[0][0]) + 225, &(this->mindBoard[0][0]));
	
	this->scanBoard(1);
	this->scanBoard(2);
	
	vector<int> cWP(wP);
	vector<int> cBP(bP);
	
	cout << "current O: ";
	for (const int &c : bP)
	{
		cout << c << ", ";
	}
	cout << endl << "current X: ";
	for (const int &c : wP)
	{
		cout << c << ", ";
	}
	cout << endl;
	
	wP = {0,0,0,0,0,0,0,0,0,0};
	bP = {0,0,0,0,0,0,0,0,0,0};
	
	for (int i = cbg->boundary[0]; i <= cbg->boundary[1]; i++)
	{
		for (int j = cbg->boundary[2]; j <= cbg->boundary[3]; j++)
		{
			if (!mindBoard[i][j])
			{
				mindBoard[i][j] = black?1:2;
				this->scanBoard(1);
				this->scanBoard(2);
				
				/*vector<int> input;// = {cbg->steps};
				if (black)
				{
					input.insert(input.end(), bP.begin(), bP.end());
					input.insert(input.end(), wP.begin(), wP.end());
				}
				else
				{
					input.insert(input.end(), wP.begin(), wP.end());
					input.insert(input.end(), bP.begin(), bP.end());
				}*/
				
				vector<int> oppDiff;
				
				vector<int> input;// = {cbg->steps};
				for (int i = 0; i < 10; i ++)
				{
					oppDiff.push_back(wP[i]-cWP[i]);
				}
				
				double loseHeu = this->winClassifier.getProbability(oppDiff, false);
				
				vector<int> selfDiff;
				
				for (int i = 0; i < 10; i ++)
				{
					selfDiff.push_back(bP[i]-cBP[i]);
				}
				
				double winHeu = this->winClassifier.getProbability(selfDiff, true);
				
				cout << "("<<i<<", "<<j<<") win rate: " << winHeu*100 << ", opponent lose rate: " << loseHeu*100 << "%"<< endl;
				
				heuMap.insert(pair<tuple<int, int>, double>(make_tuple(i,j), winHeu+loseHeu));
				
				wP = {0,0,0,0,0,0,0,0,0,0};
				bP = {0,0,0,0,0,0,0,0,0,0};
				countBP = 0;
				countWP = 0;
				mindBoard[i][j] = 0;
			}
		}
	}
	
	vector<tuple<int, int>> bestPoints;
	double max = -1000;
	for (auto it=heuMap.begin(); it!=heuMap.end(); ++it)
	{
		if (it->second > max)
		{
			max = it->second;
			bestPoints = {it->first};
		}
		else if (it->second == max)
		{
			bestPoints.push_back(it->first);
		}
	}
	
	uniform_int_distribution<int> distributionX(0,(int)bestPoints.size()-1);
	return bestPoints[distributionX(randDevice)];
}

//
// Private methods
//

int AI::checkBoard(int white, const int i, const int j)
{
	int pieceMap[] = {0,white,3-white};
	if (0)
		return pieceMap[cbg->myBoard.checkOnBoard(i, j)]; //train
	else
		return pieceMap[this->mindBoard[i][j]];  //Play
}

void AI::scanBoard(int white)
{
	vector<int> *pP = nullptr;
	int *countPP = nullptr;
	if (white == 1)
	{
		pP = &wP;
		countPP = &countWP;
	}
	else if (white == 2)
	{
		pP = &bP;
		countPP = &countBP;
	}
	else
	{
		return;
	}
	
	for (int i = 0; i < 15; i++)
	{
		FSA fsa = FSA(q0);
		
		//horizontal
		//Boundary, add oponent piece
		int j = 0;
		fsa.checkAndGoNext(3-white);
		
		while (j < 15)
		{

			int retVal = fsa.checkAndGoNext(this->checkBoard(white, i, j));
			//cout << j << " "<<fsa.currentNode->name << " "<< this->checkBoard(white, i, j) << " "<< retVal <<" | ";
			
			if (retVal == -1) {//Rejected
				j--; }
			else if (retVal == 0) {//Still processing
				j++; }
			else if (retVal >= 1) {//Accepted
				int width = 0;
				bool found = false;
				//Check lower
				for (int wd = j-1; wd < 15; wd++) {
					if (this->checkBoard(white, i, wd) == 3-white) {
						width = wd;
						found = true;
						break; }
				}
				if (!found) width = 15;
				found = false;
				//Check higher & get width
				for (int wd = j-2; wd >= 0; wd--)
				{
					if (this->checkBoard(white, i, wd) == 3-white)
					{
						width -= wd;
						found = true;
						break;
					}
				}
				if (!found) width += 1;
				found = false;
				
				//If got enought space(width)
				if (width >= 6) pP->at(retVal-1) ++;
				
				if (retVal >= 7 && retVal <= 10)
				{
					j-=2;
					while (this->checkBoard(white, i, j)) j--;
				}
				else { j--; }
			}
		}
		//Boundary, add oponent piece
		int retValHE = fsa.checkAndGoNext(3-white);
		if (retValHE>=1) pP->at(retValHE-1) ++;
		
		//To vertical
		fsa.restart();
		/*
		cout << endl << "H, "<< i << ": ";
		for (auto const& c : *pP)
		{
			*countPP += c;
			cout << c << ' ';
		}
		cout << endl;*/
		
		
		//vertical
		j = 0;
		
		//Boundary, add oponent piece
		fsa.checkAndGoNext(3-white);
		
		while (j < 15)
		{
			int retVal = fsa.checkAndGoNext(this->checkBoard(white, j, i));
			//cout << j << " "<<fsa.currentNode->name << " "<< this->checkBoard(white, i, j) << " "<< retVal <<" | ";
			
			if (retVal == -1) {//Rejected
				j--; }
			else if (retVal == 0) {//Still processing
				j++; }
			else if (retVal >= 1) {//Accepted
				int width = 0;
				bool found = false;
				//Check lower
				for (int wd = j-1; wd < 15; wd++)
				{
					if (this->checkBoard(white, wd, i) == 3-white)
					{
						width = wd;
						found = true;
						break;
					}
				}
				if (!found) width = 15;
				found = false;
				//Check higher & get width
				for (int wd = j-2; wd >= 0; wd--)
				{
					if (this->checkBoard(white, wd, i) == 3-white)
					{
						width -= wd;
						found = true;
						break;
					}
				}
				if (!found) width += 1;
				found = false;
				
				//If got enought space(width)
				if (width >= 6) pP->at(retVal-1) ++;
				
				if (retVal >= 7 && retVal <= 10)
				{
					j-=2;
					while (this->checkBoard(white, j, i)) j--;
				}
				else{ j--; }
			}
		}
		//Boundary, add oponent piece
		int retValVE = fsa.checkAndGoNext(3-white);
		if (retValVE>=1) pP->at(retValVE-1) ++;
		
		//To next
		fsa.restart();
		/*
		cout << endl <<"V, "<< i << ": ";
		for (auto const& c : *pP)
		{
			*countPP += c;
			cout << c << ' ';
		}
		cout << endl;*/
	}
	
	//Diagonal
	int startPointsX[] = {10,9,8,7,6,5,4,3,2,1,0,  0,0,0,0,0,0,0,0,0,0 };
	int startPointsY[] = { 0,0,0,0,0,0,0,0,0,0,0,  1,2,3,4,5,6,7,8,9,10};
	
	int startPointsXBack[] = {0,0,0,0,0,0,0 ,0 ,0 ,0 ,0,  1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10};
	int startPointsYBack[] = {4,5,6,7,8,9,10,11,12,13,14, 14,14,14,14,14,14,14,14,14,14};
	
	for (int i = 0; i <= 21; i++)
	{
		int sX = startPointsX[i];
		int sY = startPointsY[i];
		
		int sXB = startPointsXBack[i];
		int sYB = startPointsYBack[i];
		
		FSA fsa = FSA(q0);
		
		
		// left to right
		
		//Boundary, add oponent piece
		fsa.checkAndGoNext(3-white);
		
		while (sX<15 && sY<15)
		{
			int retVal = fsa.checkAndGoNext(this->checkBoard(white, sX, sY));
			//cout << j << " "<<fsa.currentNode->name << " "<< this->checkBoard(white, i, j) << " "<< retVal <<" | ";
			
			if (retVal == -1)
			{//Rejected
				sX--;
				sY--;
			}
			else if (retVal == 0)
			{//Still processing
				sX++;
				sY++;
			}
			else if (retVal >= 1)
			{//Accepted
				
				//Check capacity
				
				int width = 0;
				bool found = false;
				//Check higher
				int tmpSX = sX - 1;
				int tmpSY = sY - 1;
				while (tmpSX < 15 && tmpSY < 15)
				{
					if (this->checkBoard(white, tmpSX, tmpSY) == 3-white)
					{
						found = true;
						width = tmpSX;
					}
					tmpSX ++;
					tmpSY ++;
				}
				if (!found)
				{
					width = 15;
				}
				found = false;
				//Check lower & get width
				tmpSX = sX - 2;
				tmpSY = sY - 2;
				while (tmpSX >=0 && tmpSY >= 0)
				{
					if (this->checkBoard(white, tmpSX, tmpSY) == 3-white)
					{
						found = true;
						width -= tmpSX;
					}
					tmpSX--;
					tmpSY--;
				}
				if (!found)
				{
					width += 1;
				}
				found = false;
				
				//If got enought space(width)
				if (width >= 6)
				{
					pP->at(retVal-1) ++;
				}
				
				
				if (retVal >= 7 && retVal <= 10)
				{
					sX-=2;
					sY-=2;
					while (this->checkBoard(white, sX, sY))
					{
						sX--;
						sY--;
					}
				}
				else
				{
					sX--;
					sY--;
				}
			}
			
		}
		//Boundary, add oponent piece
		int retValDE = fsa.checkAndGoNext(3-white);
		if (retValDE>=1) pP->at(retValDE-1) ++;
		
		//To next
		fsa.restart();
		/*
		cout << endl <<"D\\, "<< i << ": ";
		for (auto const& c : *pP)
		{
			*countPP += c;
			cout << c << ' ';
		}
		cout << endl;*/
		
		
		// right to left
		
		//Boundary, add oponent piece
		fsa.checkAndGoNext(3-white);
		
		while (sXB<15 && sYB>=0)
		{
			int retVal = fsa.checkAndGoNext(this->checkBoard(white, sXB, sYB));
			//cout << j << " "<<fsa.currentNode->name << " "<< this->checkBoard(white, i, j) << " "<< retVal <<" | ";
			
			if (retVal == -1)
			{//Rejected
				sXB--;
				sYB++;
			}
			else if (retVal == 0)
			{//Still processing
				sXB++;
				sYB--;
			}
			else if (retVal >= 1)
			{//Accepted
				
				//Check capacity
				
				int width = 0;
				bool found = false;
				//Check higher
				int tmpSXB = sXB + 1;
				int tmpSYB = sYB - 1;
				while (tmpSXB >= 0 && tmpSYB < 15 && tmpSXB < 15 && tmpSYB >= 0)
				{
					if (this->checkBoard(white, tmpSXB, tmpSYB) == 3-white)
					{
						found = true;
						width = tmpSYB;
					}
					tmpSXB --;
					tmpSYB ++;
				}
				if (!found)
				{
					width = 15;
				}
				found = false;
				//Check lower & get width
				tmpSXB = sXB + 2;
				tmpSYB = sYB - 2;
				while (tmpSXB < 15 && tmpSYB >= 0)
				{
					if (this->checkBoard(white, tmpSXB, tmpSYB) == 3-white)
					{
						found = true;
						width -= tmpSYB;
					}
					tmpSXB++;
					tmpSYB--;
				}
				if (!found)
				{
					width += 1;
				}
				found = false;
				
				//If got enought space(width)
				if (width >= 6)
				{
					pP->at(retVal-1) ++;
				}
				
				
				if (retVal >= 7 && retVal <= 10)
				{
					sXB-=2;
					sYB+=2;
					while (this->checkBoard(white, sXB, sYB))
					{
						sXB--;
						sYB++;
					}
				}
				else
				{
					sXB--;
					sYB++;
				}
			}
			
		}
		//Boundary, add oponent piece
		int retValDBE = fsa.checkAndGoNext(3-white);
		if (retValDBE>=1) pP->at(retValDBE-1) ++;
		
		//To next
		fsa.restart();
		/*
		cout << endl <<"D/, "<< i << ": ";
		for (auto const& c : *pP)
		{
			*countPP += c;
			cout << c << ' ';
		}
		cout << endl;*/
		
	}
}