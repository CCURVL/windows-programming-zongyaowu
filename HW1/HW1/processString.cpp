#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <gtest\gtest.h>

using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	stringstream s(inputStr);
	string sub_str;
	int L = 0;																							//計算分隔號數量
	while (getline(s, sub_str, ' ')) {
		cout << sub_str << endl;
		L++;
	}
	cout << L << endl;
	istringstream buffer(inputStr);
	char chars[] = "()- ";
	for (unsigned int y = 0; y < strlen(chars); ++y) {
		inputStr.erase(remove(inputStr.begin(), inputStr.end(), chars[y]), inputStr.end());				//消除空白&負號
	}
	unsigned int z = 0;
	for (z = 0; z < inputStr.length(); z++) { if (!isdigit(inputStr[z]))return -1; };
	int x;
	int value;
	int iArr[100];
	for (x = 0; x< L; x++) {
		buffer >> value;																				//string to int
		cout << value << " ";
		iArr[x] = value;
	}
	cout << endl;
	int i;// j;
	int temp = 0;

	/*for (i = 0; i < L; i++) {																			//bubble sort
		for (j = i; j < L; j++) {
			if (iArr[j] < iArr[i]) {
				temp = iArr[j];
				iArr[j] = iArr[i];
				iArr[i] = temp;
			}
		}
	}*/
	sort(iArr, iArr+L);
	for (i = 0; i < L; i++) {
		cout << iArr[i] << " ";
	}
	cout << endl;
	string convert_str;																					//int to string
	inputStr.clear();
	for (i = 0; i < L; i++) {
		stringstream ss;
		int number = iArr[i];
		ss << number;
		ss >> convert_str;
		inputStr.append(convert_str);																		//堆值						
		inputStr.append(" ");
	}
	inputStr.erase(inputStr.find_last_not_of(" ") + 1);													//消除最後一個空白				
	return 0;
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	double D;
	double  y, z;
	D = b*b - 4 * a*c;
	cout << D << endl;
	if (D > 0) {
		y = (-b + sqrt(D)) / (2 * a);
		z = (-b - sqrt(D)) / (2 * a);
		x.push_back(y);
		x.push_back(z);
		return 1;
	}
	else if (D == 0) {
		y = (-b) / (2 * a);
		x.push_back(y);
		cout << x[0] << endl;
		return 0;
	}
	else {
		return -1;
	}
}

int main(int argc, char*argv[]) {

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}