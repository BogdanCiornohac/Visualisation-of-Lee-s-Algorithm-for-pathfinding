#ifndef __LEESALGORITHM_H__
#define __LEESALGORITHM_H__

#include<utility>
#include<queue>
#include"Colors.h"
using std::queue;
using std::pair;


class LeesAlgorithm {
	private:
		char wall, start, end;
		struct position
		{
			int x, y;
		}starts, finish, q[22*22];
		char table[22][22];
		int leeTable[22][22];
		int bottom, top;
		//queue<pair<int, int>> myQueue;

	public:
		//Constructor
		LeesAlgorithm();
		//Create the table for visualisation
		void displayTable(void);
		//Meniu for adding end, start & walls
		void meniu(void);
		//Function for adding start & end
		void addStartEnd(void);
		//Function for adding walls
		void addWall(void);
		//Function for removine walls
		void removeWall(void);
		//Change color of the point
		void changeColor(char c);
		//Verify is the choosen position is valid
		int isValidPlace(int x, int y);
		//Start Lee's algorithm
		void lee(void);
		//Display final road
		void displayRoad(void);
		//Load from file
		void loadMatrix(void);
};

#endif 
