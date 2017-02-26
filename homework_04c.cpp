#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
struct Peg {
	int value;
};
vector <vector <Peg> > stateList;
class Board {
public:
	vector <Peg> originalState;
	vector <Peg> thisState;
	Board(int start);
	void Jump(int peg, map<int, vector<pair <int, int> > > &movesList);
	bool isSolved();
	bool validMoveExists(int peg, map<int, vector<pair <int, int> > > &movesList);
	void printBoard();
};

Board::Board(int start) {
	//constructs board
	//sets initial empty peg hole
	for(int i = 0; i < 15; i++) {
		thisState.push_back(Peg());
		thisState[i].value = 1;
		if(i == start - 1) {
			thisState[i].value = 0;
		}
	}
	originalState = thisState;
}

void Board::printBoard() {
	printf("		%d\n", thisState[0].value);
	printf("	       %d %d\n", thisState[1].value, thisState[2].value);
	printf("	      %d %d %d\n", thisState[3].value, thisState[4].value, thisState[5].value);
	printf("             %d %d %d %d\n", thisState[6].value, thisState[7].value, thisState[8].value, thisState[9].value);
	printf("            %d %d %d %d %d\n", thisState[10].value, thisState[11].value, thisState[12].value, thisState[13].value, thisState[14].value);
}

bool Board::validMoveExists(int peg, map<int, vector<pair <int, int> > > &movesList) {
	for(int s = 0; s < movesList[peg].size(); s++) {
	if(thisState[peg - 1].value == 1 && thisState[(movesList[peg][s].first) - 1].value == 1 && thisState[(movesList[peg][s].second) - 1].value == 0) {
		return true;
		}
	}
	return false;
}

bool Board::isSolved() {
	int numLeft;
	for(int i = 0; i < 15; i++) {
		if(thisState[i].value == 1) {
			++numLeft;
		}
	}
	if(numLeft == 1) {
		cout << "SOLVED" << endl;
		return true;
	}
	else {
		return false;
	}
}

void Board::Jump(int peg, map <int, vector<pair <int, int> > > &movesList) {

	if(isSolved()) {
		return;
	}
	

	bool moveMade = false;
	for(int s = 0; s < movesList[peg].size(); s++) {
		//jump move
		if(thisState[peg - 1].value == 1 && thisState[(movesList[peg][s].first) - 1].value == 1 && thisState[(movesList[peg][s].second) - 1].value == 0) {
			thisState[peg - 1].value = 0;
			thisState[(movesList[peg][s].first) - 1].value = 0;
			thisState[(movesList[peg][s].second) - 1].value = 1;
			stateList.push_back(thisState);
			moveMade = true;
			printBoard();
			Jump(movesList[peg][s].second, movesList);
			if(isSolved()) {
				return;
			}
			else {
				moveMade = false;
			}	
		}	
	}

	if(moveMade == false) {
		for(int p = 1; p < 16; p++) {
			bool validPeg = validMoveExists(p, movesList);
			if(validPeg == true) {
				Jump(p, movesList);
			}

			if(isSolved()) {
				return;
			}
			
		}
	}

	if(moveMade == false && stateList.size() > 0) {
		stateList.pop_back();
		if(stateList.size() > 0) {
			thisState = stateList.back();
		}
		else {
			thisState = originalState;
		}
		return;
	}

}

int main(int argc, char* argv[]) {
	const int possiblePairs[] = {2, 4, 3, 6, 0, 4, 7, 5, 9, 0, 6, 10, 5, 8, 0, 2, 1, 7, 11, 5, 6, 8, 13, 0, 9, 14, 8, 12, 0, 10, 15, 3, 1, 9, 13, 5, 4, 0, 4, 2, 8, 9, 0, 9, 10, 5, 3, 0, 5, 2, 8, 7, 0, 6, 3, 9, 8, 0, 12, 13, 7, 4, 0, 13, 14, 8, 5, 0, 9, 6, 14, 15, 12, 11, 8, 4, 0, 9, 5, 13, 12, 0, 14, 13, 10, 6};
	map <int, vector<pair <int, int> > > possibleMoves;
		for(int pegCount = 1, arrayIndex = 0; pegCount < 16;) {
			if(possiblePairs[arrayIndex] == 0) {
				++pegCount;
				++arrayIndex;
			}
			else {
				possibleMoves[pegCount].push_back(make_pair(possiblePairs[arrayIndex], possiblePairs[arrayIndex + 1]));
				arrayIndex = arrayIndex + 2;
			}
		}

	int emptyPegLoc, checkPegLoc = atoi(argv[1]);
	bool printBoard;
	string checkPrintBoard = argv[2];

	if(checkPegLoc > 0 && checkPegLoc <= 15) {
		emptyPegLoc = checkPegLoc;
		if(checkPrintBoard == "true" || checkPrintBoard == "1") {
			printBoard = true;
		}
		else if(checkPrintBoard == "false" || checkPrintBoard == "0") {
			printBoard = false;
		}
		else {
			cout << "Invalid Values" << endl;
			exit(0);
		}
	}
	else {
		cout << "Invalid Values";
		exit(0);
	}
	
	Board b(emptyPegLoc);
	//cout << possibleMoves[1].size();
	b.Jump(1, possibleMoves);
	
	for(int i = 0; i < stateList.size(); i++) {
		for(int x = 0; x < 15; x++) {
			cout << stateList[i][x].value;
		}
		cout << endl;
	}
	
	//b.printBoard();
	
}