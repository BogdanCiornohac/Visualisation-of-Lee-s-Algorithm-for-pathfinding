#include"LeesAlgorithm.h"
#include<iostream>
#include<fstream>
using namespace std;


LeesAlgorithm::LeesAlgorithm()
{
	start = 's';
	end = 'f';
	wall = '#';
	bottom = top = 0;

	finish.x = finish.y = starts.x = starts.y = 0;
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 20; j++)
		{
			table[i][j] = '0';
			leeTable[i][j] = 0;
		}
	//We borad the matrix
	for (int j = 0; j <= 21; j++)
	{
		table[0][j] = table[21][j] = '#';
		leeTable[0][j] = leeTable[21][j] = -1;
	}
	for (int i = 0; i <= 21; i++)
	{
		table[i][0] = table[i][21] = '#';
		leeTable[i][0] = leeTable[i][21] = -1;
	}
}

void LeesAlgorithm::displayTable(void)
{
	cout << "  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20\n";
	cout << " _______________________________________________________________________________\n";
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 1; j <= 20; j++)
			if (table[i][j] == '0')
				cout << "|_" << table[i][j] << "_";
			else
				changeColor(table[i][j]);
		cout << "|   "<<i<<"\n";
	}
	cout << "\n";
}

void LeesAlgorithm::meniu(void)
{
	system("cls");
	displayTable();
	cout << "   Choose your optin: \n  1.Add Start & end\n  2.Add Walls\n  3.Remove Walls\n  4.Start Lee's Algorithm\n";
	cout<<"  5.Load table from file(Modify matrix from matrix.txt)\n"; 
	int option;
	cin >> option;
	
	switch (option)
	{
		case 1:
			addStartEnd();
			break;
		case 2:
			addWall();
			break;
		case 3:
			removeWall();
			break;
		case 4:
		{
			lee();
			displayTable();
			
			//checking if 
			if (leeTable[finish.x][finish.y] == 0)
			{
				cout << "Impossible to find road";
			}
			else
			{
				displayRoad();
			}

			Sleep(100);
			break;
		}
		case 5:
			loadMatrix();
			break;
		default:
		{
			cout << "There is no such command!";
			Sleep(1500);
			meniu();
			break;
		}
	}

}

void LeesAlgorithm::addStartEnd(void)
{
	int x, y;

	cout << "Insert coordinates for start (between 1 and 20): ";
	cin >> x >> y;
	while (isValidPlace(x, y) == 0)
	{
		cout << "Place is already in use. Please insert other coordinates: ";
		cin >> x >> y;
	}
	table[starts.x][starts.y] = '0';
	starts.x = x;
	starts.y = y;
	table[starts.x][starts.y] = start;
	leeTable[starts.x][starts.y] = 1;

	cout << "Insert coordinates for end (between 1 and 20): ";
	cin >> x >> y;
	while (isValidPlace(x, y) == 0)
	{
		cout << "Place is already in use. Please insert other coordinates: ";
		cin >> x >> y;
	}
	table[finish.x][finish.y] = '0';
	finish.x = x;
	finish.y = y;
	table[finish.x][finish.y] = end;
	meniu();
}

void LeesAlgorithm::addWall(void)
{
	cout << "Inster wall position. Insert -1 -1 when you want to stop.\n";
	int x, y;
	cin >> x >> y;
	while (x != -1)
	{
		if (!isValidPlace(x, y)) 
		{
			cout << "Place is already in use.Please insert other coordinates: ";
			cin >> x >> y;
		}
		table[x][y] = wall;
		leeTable[x][y] = -1;
		cin >> x >> y;
	}
	meniu();

}

void LeesAlgorithm::removeWall(void)
{
	int x, y;
	cout << "Insert walls posotions. Insert -1 -1 when ypu want to stop.\n ";
	cin >> x >> y;
	
	while (x != -1)
	{
		if (table[x][y] == '#')
		{
			table[x][y] = '0';
			leeTable[x][y] = 0;
		}
		else
			cout << "There is no wall\n";
		cin >> x >> y;
	}
	meniu();
}

int LeesAlgorithm::isValidPlace(int x, int y)
{
	if (x < 1 || x > 20 || y < 1 || y > 20)
		return 0;
	if (table[x][y] == '0')
		return 1;
	return 0;
}

void LeesAlgorithm::lee(void)
{
	int addRow[] = { -1, 0, 1, 0 };
	int addCol[] = { 0, 1, 0, -1 };

	q[0] = starts;
	
	bottom = top = 0;

	position pos;

	while (bottom <= top && !leeTable[finish.x][finish.y])
	{
		pos = q[bottom++];
		for (int i = 0; i < 4; i++)
		{
			position neighbor;

			neighbor.x = pos.x + addRow[i];
			neighbor.y = pos.y + addCol[i];

			if (!leeTable[neighbor.x][neighbor.y])
			{
				//if (table[neighbor.x][neighbor.y] != 1 && leeTable[neighbor.x][neighbor.y] != 's')
				table[neighbor.x][neighbor.y] = '*';
				leeTable[neighbor.x][neighbor.y] = leeTable[pos.x][pos.y] + 1;
				q[++top] = neighbor;
			}
			displayTable();
			Sleep(60);
			system("cls");
		}
	}
	table[finish.x][finish.y] = end;
}

void LeesAlgorithm::displayRoad(void)
{
	int addRow[] = { -1, 0, 1, 0 };
	int addCol[] = { 0, 1, 0, -1 };

	position stack[22 * 22];
	
	int vf = 0;

	position pos = stack[++vf] = finish;

	while (leeTable[pos.x][pos.y] > 1)
	{
		for (int i = 0; i < 4; i++)
		{
			position neighbor;

			neighbor.x = pos.x + addRow[i];
			neighbor.y = pos.y + addCol[i];
			if (leeTable[neighbor.x][neighbor.y] == leeTable[pos.x][pos.y] - 1)
			{
				stack[++vf] = pos = neighbor;
				break;
			}
		}
	}

	vf--;

	while (vf > 1)
	{
		table[stack[vf].x][stack[vf].y] = '=';
		
		system("cls");
		displayTable();
		Sleep(150);
		
		vf--;
	}
}

void LeesAlgorithm::changeColor(char c)
{
	WORD Attributes = 0;
	cout << "|_";
	if (c == 's')
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (c == 'f')
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (c == '#')
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (c == '*')
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else if (c == '=')
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << c;
	ResetConsoleColour(Attributes);
	cout << "_";
}

void LeesAlgorithm::loadMatrix(void)
{
	ifstream fin("Matrix.in");

	char matrixCharacter;
	int i = 1, j = 1;

	while(fin >> matrixCharacter)
	{
		if (matrixCharacter == ' ')
			continue;
		
		if (j > 20)
		{
			j = 1;
			i++;
		}

		table[i][j] = matrixCharacter;

		if (matrixCharacter == 's')
		{
			starts.x = i;
			starts.y = j;
			leeTable[starts.x][starts.y] = 1;
		}
		else if (matrixCharacter == 'f')
		{
			finish.x = i;
			finish.y = j;
		}
		else if (matrixCharacter == '#')
		{
			table[i][j] = wall;
			leeTable[i][j] = -1;
		}
		j++;

		
	}
	meniu();
}