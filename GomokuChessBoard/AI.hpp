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
#include <fstream>
#include <tuple>
#include <random>

#include "ChessBoardGame.hpp"
#include "Learning.hpp"

#define NUM_OF_FEATURES 10

const bool train = false;

class FSA_node
{
public:
	
	FSA_node(){}
	
	
	void setTransition(FSA_node *S0, FSA_node *S1, FSA_node *S2, int name, bool final)
	{
		this->S[0] = S0;
		this->S[1] = S1;
		this->S[2] = S2;
		this->name = name;
		this->final = final;
	}
	
	FSA_node *S[3];
	int name;
	bool final;
};

class FSA
{
public:
	FSA(){}
	
	FSA(FSA_node *startNode)
	{
		this->startNode = startNode;
		this->currentNode = startNode;
	}

	int checkAndGoNext(int input)
	{
		if (currentNode != nullptr)
		{
			if (currentNode->final == true)
			{
				int finalNode = currentNode->name;
				this->restart();
				return finalNode;
			}
			else
			{
				currentNode = currentNode->S[input];
				return 0;
			}
		}
		else
		{
			this->restart();
			return -1;
		}
	}
	
	void restart()
	{
		currentNode = startNode;
	}
	
	FSA_node *startNode;
	
//private:
	FSA_node *currentNode;
};

class AI
{
public:
	AI() {}
	
	~AI()
	{
		csvWriter.close();
	}
	
	AI(bool black, ChessBoardGame *cbg)
	{
		csvWriter.open("data.csv", std::fstream::in | std::fstream::out | std::fstream::app);
		csvReader.open("data.csv", std::fstream::in);

		//Load previous data
		std::string tmpL;
		std::string tmp;
		int lineCount = 0;
		std::vector<int> tmpV;
		for (int i = 0; i < NUM_OF_FEATURES; i++)
			this->features.push_back(tmpV);
		
		while (getline(csvReader, tmp, ','))
		{
			
			int val = atoi(tmp.c_str());
				
				if (lineCount == NUM_OF_FEATURES-1)
				{
					this->features[NUM_OF_FEATURES-1].push_back(val);
					
					getline(csvReader, tmp);
					this->featureClass.push_back((bool)atoi(tmp.c_str()));
					
					lineCount = 0;
				}
				else
				{
					this->features[lineCount].push_back(val);
				
					lineCount ++;
				}
			
		}
		
		if (this->featureClass.size() == 0)
		{
			for (int i = 0; i < NUM_OF_FEATURES; i++)
				this->features[i].push_back(0);
			this->featureClass.push_back(0);
		}
		
		csvReader.close();
		
		winClassifier = NBClassifier(this->features, this->featureClass);
		
		this->black = black;
		this->cbg = cbg;
		
		q0->setTransition(q27, q23, q21, 0, false);
		q23->setTransition(q32, q29, q21, 23, false);
		q21->setTransition(q27, q23, q21, 21, false);
		q27->setTransition(q27, q1, q21, 27, false);
		q32->setTransition(q27, q33, q21, 32, false);
		q29->setTransition(q36, q30, q21, 29, false);
		q1->setTransition(q6, q2, q21, 1, false);
		q33->setTransition(p9, q34, q21, 33, false);
		q36->setTransition(p5, q37, q21, 36, false);
		q30->setTransition(q39, q31, q21, 30, false);
		q2->setTransition(q7, q3, p5, 2, false);
		q6->setTransition(q27, q10, q21, 6, false);
		p9->setTransition(nullptr, nullptr, nullptr, 9, true);
		q34->setTransition(p10, q35, q21, 34, false);
		p1->setTransition(nullptr, nullptr, nullptr, 1, true);
		q37->setTransition(p10, q38, q21, 37, false);
		q39->setTransition(p6, q40, q21, 39, false);
		q31->setTransition(p3, p4, q21, 31, false);
		q3->setTransition(q8, q4, p6, 3, false);
		p5->setTransition(nullptr, nullptr, nullptr, 5, true);
		q7->setTransition(p1, q19, p1, 7, false);
		q10->setTransition(p7, q11, p9, 10, false);
		p10->setTransition(nullptr, nullptr, nullptr, 10, true);
		q35->setTransition(q4, p3, p6, 35, false);
		q38->setTransition(p3, p3, p3, 38, false);
		p6->setTransition(nullptr, nullptr, nullptr, 6, true);
		q40->setTransition(p3, p3, p3, 40, false);
		p3->setTransition(nullptr, nullptr, nullptr, 3, true);
		p4->setTransition(nullptr, nullptr, nullptr, 4, true);
		q4->setTransition(p3, p4, p3, 4, false);
		q8->setTransition(p2, q9, p2, 8, false);
		q19->setTransition(p8, p3, p10, 19, false);
		p7->setTransition(nullptr, nullptr, nullptr, 7, true);
		q11->setTransition(p8, q15, p10, 11, false);
		p2->setTransition(nullptr, nullptr, nullptr, 2, true);
		q9->setTransition(p3, q2, p3, 9, false);
		p8->setTransition(nullptr, nullptr, nullptr, 8, true);
		q20->setTransition(p3, q3, p3, 20, false);
		q15->setTransition(p3, q4, p3, 15, false);
	}
	
	std::tuple<int, int> generateLocation();
	std::tuple<int, int> searchBestLocation();
	void endGame(int totalSteps, bool win);
	
	void learnHuman(int x, int y);
	
private:
	
	std::vector<std::vector<int>> record;
	std::vector<std::vector<int>> recordDifference;
	
	std::vector<std::vector<int>> features;
	std::vector<bool> featureClass;
	
	NBClassifier winClassifier;
	
	std::vector<int> wP = {0,0,0,0,0,0,0,0,0,0};
	int countWP = 0;
	std::vector<int> bP = {0,0,0,0,0,0,0,0,0,0};
	int countBP = 0;
	
	std::fstream csvWriter;
	std::fstream csvReader;
	
	//p1: oo
	//p2: ooo
	//p3: oooo
	//p4: ooooo
	//p5: oox
	//p6: ooox
	//p7: o+o
	//p8: o+oo
	//p9: o+ox
	//p10: o+oox
	
	int checkBoard(int white, const int i, const int j);
	void scanBoard(int white);
	
	int mindBoard[15][15];
	
	ChessBoardGame *cbg;
	bool black;
	std::random_device randDevice;
	
	FSA_node *q0 = new FSA_node();
	FSA_node *q23 = new FSA_node();
	FSA_node *q21 = new FSA_node();
	FSA_node *q27 = new FSA_node();
	FSA_node *q32 = new FSA_node();
	FSA_node *q29 = new FSA_node();
	FSA_node *q1 = new FSA_node();
	FSA_node *q33 = new FSA_node();
	FSA_node *q36 = new FSA_node();
	FSA_node *q30 = new FSA_node();
	FSA_node *q2 = new FSA_node();
	FSA_node *q6 = new FSA_node();
	FSA_node *p9 = new FSA_node();
	FSA_node *q34 = new FSA_node();
	FSA_node *p1 = new FSA_node();
	FSA_node *q37 = new FSA_node();
	FSA_node *q39 = new FSA_node();
	FSA_node *q31 = new FSA_node();
	FSA_node *q3 = new FSA_node();
	FSA_node *p5 = new FSA_node();
	FSA_node *q7 = new FSA_node();
	FSA_node *q10 = new FSA_node();
	FSA_node *p10 = new FSA_node();
	FSA_node *q35 = new FSA_node();
	FSA_node *q38 = new FSA_node();
	FSA_node *p6 = new FSA_node();
	FSA_node *q40 = new FSA_node();
	FSA_node *p3 = new FSA_node();
	FSA_node *p4 = new FSA_node();
	FSA_node *q4 = new FSA_node();
	FSA_node *q8 = new FSA_node();
	FSA_node *q19 = new FSA_node();
	FSA_node *p7 = new FSA_node();
	FSA_node *q11 = new FSA_node();
	FSA_node *p2 = new FSA_node();
	FSA_node *q9 = new FSA_node();
	FSA_node *p8 = new FSA_node();
	FSA_node *q20 = new FSA_node();
	FSA_node *q15 = new FSA_node();
	
	
};

#endif /* AI_hpp */