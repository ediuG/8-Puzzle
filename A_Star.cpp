#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


typedef struct Puzzle
{   /* index 0-8 is number in board
	index 9 is direction
	index 10 is before state
	index 11 is index of info array*/
	int board[12] = {};
	int cost = 0;
	int distance = 0;
}puzzle;

typedef struct node {
	puzzle* puzzle;
	node *next = NULL;
}Node;

typedef struct list {
	node *first_node;
}List;

//linked-list function
List* new_list(void);
void node_insert_begin(List*, puzzle*);
void node_insert_after(Node*, puzzle*);
void node_insert_ordered(List*, puzzle*);
void node_remove_begin(List*);

//puzzle function
void randomPuzzle(puzzle*);
void coppyPuzzle(puzzle*, puzzle*);
int findPos0(puzzle*);
void sLeft(puzzle*);
void sRight(puzzle*);
void sUp(puzzle*);
void sDown(puzzle*);
void createState(puzzle*, int*);
void createTree(puzzle*);
bool goal(puzzle*);
int h2(puzzle*);
void aStar(puzzle*);
void printPuzz(puzzle*);

puzzle* problem = new(Puzzle);
//create new auto sort linked-list
List *list = new_list();

puzzle* stack[50000];
puzzle* info[50000];
puzzle* finishstate;
int state = 0;
int countCol = 0;
int column = 1;
bool goall = false;
int Llaststate = 0;

List* new_list(void) {
	List *list = (List *)malloc(sizeof(node));
	list->first_node = new(Node);
	return list;
}

void node_insert_begin(List *list, puzzle* puzz) {
	Node *new_node = new(Node);
	new_node->puzzle = puzz;
	new_node->next = list->first_node;
	list->first_node = new_node;
}

void node_insert_after(Node *node, puzzle* puzz) {
	Node *new_node = new(Node);
	new_node->puzzle = puzz;
	new_node->next = node->next;
	node->next = new_node;
}

void node_insert_ordered(List *list, puzzle* puzz) {

	if (list->first_node->puzzle->cost > puzz->cost) {
		node_insert_begin(list, puzz);
	}
	else if (list->first_node->puzzle->cost < puzz->cost && list->first_node->next == NULL) {
		node_insert_after(list->first_node, puzz);
	}
	else {
		Node *node = list->first_node->next;
		Node *prev_node = list->first_node;

		while (node != NULL) {
			if (node->puzzle->cost > puzz->cost) {
				node_insert_after(prev_node, puzz);
				break;
			}
			prev_node = node;
			node = node->next;

		}
		if (node == NULL) {
			node_insert_after(prev_node, puzz);
		}
	}
}
/*remove first node of list*/
void node_remove_begin(List *list) {
	Node *d_node = list->first_node;
	list->first_node = list->first_node->next;
	delete d_node;

}

void randomPuzzle(puzzle *a) {
	cout << "start Random" << endl;
	int goal[9] = { 1,2,3,4,5,6,7,8,0 };
	for (int i = 0; i < 9; i++) {
		a->board[i] = goal[i];
	}

	//srand(time(0));
	int moves = 45;
	int poss;
	for (int i = 0; i < moves; i++) {
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

void coppyPuzzle(puzzle* source, puzzle* dest) {
	for (int i = 0; i <= 11; i++) {
		dest->board[i] = source->board[i];
	}
	dest->cost = source->cost;
	dest->distance = source->distance;
}

int findPos0(puzzle *a) {
	int pos0;
	for (int i = 0; i < 9; i++) {
		if (a->board[i] == 0) {
			pos0 = i;
			break;
		}
	}
	return pos0;
}

void sLeft(puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 - 1];
	a->board[pos0 - 1] = 0;
	a->board[9] = 3;
	//a->h2=countH2(a);
}

void sRight(puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 + 1];
	a->board[pos0 + 1] = 0;
	a->board[9] = 4;
}

void sUp(puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 - 3];
	a->board[pos0 - 3] = 0;
	a->board[9] = 1;
}

void sDown(puzzle *a) {
	int pos0 = findPos0(a);
	a->board[pos0] = a->board[pos0 + 3];
	a->board[pos0 + 3] = 0;
	a->board[9] = 2;
}

void createState(puzzle *a, int *b) {
	for (int i = 0; i <= 10; i++) {
		b[i] = a->board[i];
	}
}

//insert node with bad move (move forward then backward) detected
void createTree(puzzle *puzz) {
	int posi0 = findPos0(puzz);
	if ((posi0 == 0) || (posi0 == 2) || (posi0 == 6) || (posi0 == 8)) {
		//เลื่อนได้2ทาง
		//บนซ้าย
		if (posi0 == 0) {

			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//บนขวา
		else if (posi0 == 2) {

			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//ล่างซ้าย
		else if (posi0 == 6) {

			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//ล่างขวา
		else if (posi0 == 8) {

			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
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
				coppyPuzzle(puzz, newPuzzle);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//ซ้าย
		else if (posi0 == 3) {

			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//ขวา
		else if (posi0 == 5) {

			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//left
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//down
			if (puzz->board[9] != 1) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sDown(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
		//ล่าง
		else if (posi0 == 7) {

			//left
			if (puzz->board[9] != 4) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sLeft(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//up
			if (puzz->board[9] != 2) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sUp(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
			//right
			if (puzz->board[9] != 3) {
				Puzzle* newPuzzle = new(Puzzle);
				coppyPuzzle(puzz, newPuzzle);
				sRight(newPuzzle);

				info[column] = newPuzzle;
				info[column]->board[10] = puzz->board[11];
				info[column]->board[11] = column;
				if (!goall) goall = goal(info[column]);
				column++;

				newPuzzle->distance = puzz->distance + 1;
				//cout << "distance: " << newPuzzle->distance << endl;
				newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
				Puzzle* listPuzzle = new(Puzzle);
				coppyPuzzle(newPuzzle, listPuzzle);
				node_insert_ordered(list, listPuzzle);
			}
		}
	}
	else if (posi0 == 4) {
		//เลื่อนได้4ทาง

		//left
		if (puzz->board[9] != 4) {
			Puzzle* newPuzzle = new(Puzzle);
			coppyPuzzle(puzz, newPuzzle);
			sLeft(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = puzz->board[11];
			info[column]->board[11] = column;
			if (!goall) goall = goal(info[column]);
			column++;

			newPuzzle->distance = puzz->distance + 1;
			//cout << "distance: " << newPuzzle->distance << endl;
			newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
			Puzzle* listPuzzle = new(Puzzle);
			coppyPuzzle(newPuzzle, listPuzzle);
			node_insert_ordered(list, listPuzzle);
		}
		//up
		if (puzz->board[9] != 2) {
			Puzzle* newPuzzle = new(Puzzle);
			coppyPuzzle(puzz, newPuzzle);
			sUp(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = puzz->board[11];
			info[column]->board[11] = column;
			if (!goall) goall = goal(info[column]);
			column++;

			newPuzzle->distance = puzz->distance + 1;
			//cout << "distance: " << newPuzzle->distance << endl;
			newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
			Puzzle* listPuzzle = new(Puzzle);
			coppyPuzzle(newPuzzle, listPuzzle);
			node_insert_ordered(list, listPuzzle);
		}
		//right
		if (puzz->board[9] != 3) {
			Puzzle* newPuzzle = new(Puzzle);
			coppyPuzzle(puzz, newPuzzle);
			sRight(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = puzz->board[11];
			info[column]->board[11] = column;
			if (!goall) goall = goal(info[column]);
			column++;

			newPuzzle->distance = puzz->distance + 1;
			//cout << "distance: " << newPuzzle->distance << endl;
			newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
			Puzzle* listPuzzle = new(Puzzle);
			coppyPuzzle(newPuzzle, listPuzzle);
			node_insert_ordered(list, listPuzzle);
		}
		//down
		if (puzz->board[9] != 1) {
			Puzzle* newPuzzle = new(Puzzle);
			coppyPuzzle(puzz, newPuzzle);
			sDown(newPuzzle);

			info[column] = newPuzzle;
			info[column]->board[10] = puzz->board[11];
			info[column]->board[11] = column;
			if (!goall) goall = goal(info[column]);
			column++;

			newPuzzle->distance = puzz->distance + 1;
			////cout << "distance: " << newPuzzle->distance << endl;
			newPuzzle->cost = h2(newPuzzle) + newPuzzle->distance;
			Puzzle* listPuzzle = new(Puzzle);
			coppyPuzzle(newPuzzle, listPuzzle);
			node_insert_ordered(list, listPuzzle);
		}
	}
	state++;
}

bool goal(puzzle *a) {
	int goal[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (a->board[i] == goal[i]) count++;
	}
	if (count == 9) {
		Llaststate = a->board[9];
		finishstate = a;
		return true;
	}
	else {
		return false;
	}
}

int h2(puzzle* p) {
	int cost = 0;
	int finalState[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	for (int i = 0; i < 9; ++i)
	{
		if (p->board[i] != finalState[i])
		{
			cost++;
		}
	}
	//cout << "cost form h2: " << cost << endl;
	return cost;
}

void aStar(puzzle* prob) {
	info[0] = prob;
	Puzzle* listPuzzle = new(Puzzle);
	coppyPuzzle(info[0], listPuzzle);
	node_insert_after(list->first_node, listPuzzle);
	node_remove_begin(list);
	createTree(info[0]);
	node_remove_begin(list);
	while (!goall) {
		Puzzle* TempPuzzle = new(Puzzle);
		coppyPuzzle(list->first_node->puzzle, TempPuzzle);
		node_remove_begin(list);
		createTree(TempPuzzle);
	}

	Puzzle *movement[100];
	//มูฟเม้น
	int i = finishstate->board[11];
	if (info[i]->board != NULL) {
		int befmove = info[i]->board[9];
		int befstate = info[i]->board[10];

		cout << "=================Movement=====================" << endl;
		printPuzz(prob);

		int befmv = info[i]->board[9];
		int befst = info[i]->board[10];
		int currentst = info[i]->board[11];
		int countMM = 0;

		//save movement
		for (int a = i; a > 0; a--) {
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
		for (int b = 0; b <= countTemp; b++) {
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

		// print goal
		if ((finishstate->board[9]) == 1) cout << "Move: Up";
		else if ((finishstate->board[9]) == 2) cout << "Move: Down";
		else if ((finishstate->board[9]) == 3) cout << "Move: Left";
		else if ((finishstate->board[9]) == 4) cout << "Move: Right";
		cout << ", State: " << finishstate->board[10] << endl;
		printPuzz(finishstate);
		cout << "goal state is at state : " << finishstate->board[11] << endl;
	}
}

void printPuzz(puzzle *a) {
	cout << endl << "This puzzle now like this : " << endl;
	for (int i = 0; i < 9; i++) {
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

int main(int argc, char const *argv[])
{
	clock_t start, finish, total;
	start = clock();

	//Generate random puzzle
	randomPuzzle(problem);

	//init some data of start board
	problem->cost = h2(problem);
	problem->distance = 1;

	aStar(problem);

	finish = clock();
	total = finish - start;
	cout << "time: " << total << " msecs" << endl;
	return 0;
}
