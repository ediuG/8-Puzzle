#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;

typedef struct Puzzle
{
	int board[11] = {};
	//h1 is distance from root
	int h1 = 0;
	//h2 is estimate cost from state n to goal state
	int h2 = 0;
}puzzle;

puzzle *problem = new(Puzzle);
puzzle *info[50000];
puzzle* finishstate;

int state = 0;
int countCol = 0;
int column = 1;

bool goall = false;
int goalstate = 0;
int Llaststate = 0;

void randomPuzzle(puzzle *a);
void createTree(puzzle *puzz);
void printPuzz( puzzle *a);
int findPos0( puzzle *a);
void sLeft( puzzle *a);
void sRight( puzzle *a);
void sUp( puzzle *a);
void sDown( puzzle *a);
bool goal( puzzle *a);
void createState( puzzle *a, int *b);
bool compareState( puzzle *a, puzzle *b);
int countH2( puzzle *a);

void randomPuzzle( puzzle *a) {
	cout << "start Random" << endl;
	int goal[9] = { 1,2,3,4,5,6,7,8,0 };
	for (int i = 0;i < 9;i++) {
		a->board[i] = goal[i];
	}
	//srand(time(0));
	int moves = 45;
	int poss = findPos0(a);
	for (int i = 0;i < moves;i++) {
		poss = findPos0(a);
		int j = rand() % 4;
		if (j == 0 && (poss != 0 && poss != 1 && poss != 2)) {
			sUp(a);
			//cout << "Move Up" << endl;
		}
		else if (j == 1 && (poss != 6 && poss != 7 && poss != 8)) {
			sDown(a);
			//cout << "Move Down" << endl;
		}
		else if (j == 2 && (poss != 0 && poss != 3 && poss != 6)) {
			sLeft(a);
			//cout << "Move Left" << endl;
		}
		else if (j == 3 && (poss != 2 && poss != 5 && poss != 8)) {
			sRight(a);
			//cout << "Move Right" << endl;
		}
	}
	printPuzz(a);
}
bool compareState( puzzle *a) {
	int count = 0;

	for (int i = 0;i < countCol ;i++) {
		for (int i = 0;i < 9;i++) {
			if (a->board[i] == info[countCol]->board[i]) count++;
		}
		if (count == 9) {
			return true;
		}
		else {
			return false;
		}
	}
}
void printPuzz( puzzle *a) {
	cout << endl << "This puzzle now like this : " << endl;
	for (int i = 0;i < 9;i++) {
		if (a->board[i] != 0) {
			cout << "[" << a->board[i] << "]";
		}
		if (a->board[i] == 0) {
			cout << "[ ]";
		}
		if ((i == 2) || (i == 5)) {
			cout << "\n";
		}
	}
	cout << endl;
}
int findPos0( puzzle *a) {
	int pos0;
	for (int i = 0;i < 9;i++) {
		if (a->board[i] == 0) {
			pos0 = i;
			break;
		}
	}
	return pos0;
}
void sLeft( puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 - 1];
	a->board[pos0 - 1] = 0;
	a->board[9] = 3;
	a->h1 += 1;
	//a->h2=countH2(a);
}
void sRight( puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 + 1];
	a->board[pos0 + 1] = 0;
	a->board[9] = 4;
	a->h1 += 1;
}
void sUp( puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 - 3];
	a->board[pos0 - 3] = 0;
	a->board[9] = 1;
	a->h1 += 1;
}
void sDown( puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 + 3];
	a->board[pos0 + 3] = 0;
	a->board[9] = 2;
	a->h1 += 1;
}
bool goal( puzzle *a) {
	int goal[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	int count = 0;
	for (int i = 0;i < 9;i++) {
		if (a->board[i] == goal[i]) count++;
	}
	if (count == 9) {
		cout << "goal state is at state : " << state << endl;
		Llaststate = a->board[9];
		goalstate = state;
		finishstate = a;
		return true;
	}
	else {
		return false;
	}
}

int countH2( puzzle *a) {
	int goal[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	int count = 0;
	for (int i = 0;i < 9;i++) {
		if (a->board[i] == goal[i]) count++;
	}
/*	if (count == 9) {
		cout << "goal state is at state : " << state << endl;
		Llaststate = a[9];
		goalstate = state;
		return true;
	}
	else {
		return false;
	} */
	return count;
}

void createState( puzzle *a, int *b) {
	for (int i = 0;i <= 10;i++) {
		b[i] = a->board[i];
	}
}
/*
if (!compareState(newPuzzle)) {
L2[state] = newPuzzle;
L2[state]->board[10] = state;
}
*/
void createTree(puzzle *puzz) {
	int posi0 = findPos0(puzz);
	if ((posi0 == 0) || (posi0 == 2) || (posi0 == 6) || (posi0 == 8)) {
		//เลื่อนได้2ทาง
		//บนซ้าย
		if (posi0 == 0) {
			
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//บนขวา
		else if (posi0 == 2) {
			
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//ล่างซ้าย
		else if (posi0 == 6) {
			
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//ล่างขวา
		else if (posi0 == 8) {
			
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
	}
	else if ((posi0 == 1) || (posi0 == 3) || (posi0 == 5) || (posi0 == 7)) {
		//เลื่อนได้3ทาง
		//บนกลาง
		if (posi0 == 1) {
			
			//left
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//ซ้าย
		else if (posi0 == 3) {
			
			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//ขวา
		else if (posi0 == 5) {
			
			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//left
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
		//ล่าง
		else if (posi0 == 7) {
			
			//left
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				createState(puzz, newPuzzle->board);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = state;
				if (goall == false) goall = goal(info[column]);
				column++;
			}
		}
	}
	else if (posi0 == 4) {
		//เลื่อนได้4ทาง
	
		//left
		if (puzz->board[9] != 4) {
			Puzzle* newPuzzle = new(Puzzle);
			createState(puzz, newPuzzle->board);
			sLeft(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = state;
			if (goall == false) goall = goal(info[column]);
			column++;
		}
		//up
		if (puzz->board[9] != 2) {
			Puzzle* newPuzzle = new(Puzzle);
			createState(puzz, newPuzzle->board);
			sUp(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = state;
			if (goall == false) goall = goal(info[column]);
			column++;
		}
		//right
		if (puzz->board[9] != 3) {
			Puzzle* newPuzzle = new(Puzzle);
			createState(puzz, newPuzzle->board);
			sRight(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = state;
			if (goall == false) goall = goal(info[column]);
			column++;
		}
		//down
		if (puzz->board[9] != 1) {
			Puzzle* newPuzzle = new(Puzzle);
			createState(puzz, newPuzzle->board);
			sDown(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = state;
			if (goall == false) goall = goal(info[column]);
			column++;
		}
	}
	state++;
}

void bfSearch( puzzle *a) {
	if (!goal(a)) {
		cout << endl << "..begin breadth-first search.." << endl;
		//int countCol = 0;
		info[0] = a;
		while (1) {
			if (goall == true) break;
			else {
				createTree(info[countCol]);
				//printPuzz(info[countCol]);
				//cout << countCol << endl;
				countCol++;
			}
		}

		//printttttttttttttttttttttttttttttttttt
		Puzzle *movement[100];

		//มูฟเม้น
		int i = goalstate;
		if (info[i]->board != NULL) {
			int befmove = info[i]->board[9];
			int befstate = info[i]->board[10];
			cout << "state ==== " << befstate << endl;
			printPuzz(a);

			int befmv = info[i]->board[9];
			int befst = info[i]->board[10];
			int countMM = 0;

			//save movement
			for (int a = i;a > 0;a--) {
				Puzzle *print = new Puzzle;
				createState(info[befst], print->board);
				movement[countMM] = print;
				befst = info[befst]->board[10];
				if (befst == 0)break;
				countMM++;
				befmv = info[befst]->board[9];
			}
			//print movement
			int countTemp = countMM;
			for (int b = 0;b <= countTemp;b++) {
				int beforemv = movement[countMM]->board[9];
				if (beforemv == 1) cout << "Move: " << "Up ";
				else if (beforemv == 2) cout << "Move: " << "Down ";
				else if (beforemv == 3) cout << "Move: " << "Left ";
				else if (beforemv == 4) cout << "Move: " << "Right ";

				cout << ", State: " << movement[countMM]->board[10] << endl;
				//cout << "h1: " << movement[countMM]->h1;
				printPuzz(movement[countMM]);
				countMM--;
			}
			
			if ((info[i]->board[9]) == 1) cout << "Move: Up";
			else if ((info[i]->board[9]) == 2) cout << "Move: Down";
			else if ((info[i]->board[9]) == 3) cout << "Move: Left";
			else if ((info[i]->board[9]) == 4) cout << "Move: Right";
			cout << ", State: " << info[i]->board[10] << endl;
			//cout << "h1: " << movement[countMM]->h1;
			printPuzz(info[i]);

			// print goal
			if ((finishstate->board[9]) == 1) cout << "Move: Up";
			else if ((finishstate->board[9]) == 2) cout << "Move: Down";
			else if ((finishstate->board[9]) == 3) cout << "Move: Left";
			else if ((finishstate->board[9]) == 4) cout << "Move: Right";
			cout << ", State: " << finishstate->board[10] << endl;
			//cout << "h1: " << movement[countMM]->h1;
			printPuzz(finishstate);
		}
	}
}

void main() {
	clock_t startT, finishT, totalT;
	startT = clock();

	cout << "**random puzzle**" << endl;
	randomPuzzle(problem);

	cout << "search" << endl;
	bfSearch(problem);
	
	cout << endl<<"countCol: " << countCol << endl << "state: " << finishstate->board[10] << endl;

	finishT = clock();
	totalT = finishT - startT;
	cout << "time: " << totalT << " msecs" << endl;
}
