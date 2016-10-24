//============================================================================
// Name        : BSTreeWithTwoRoot.cpp
// Author      : CHG
// Version     :
// Copyright   : Life is  so short, so we  Code !!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "File.h"
#include "BSTree.h"
#include "Record.h"
using namespace std;
int main() {
	cout << "Programming makes us happy!!!" << endl;
	BSTree  recordeTree;
	BSTree  *pRecordeTree = &recordeTree;
	readFileAndBuildRecored(*pRecordeTree);
	return 0;
}
