#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

vector<double> F(double x) { // F(x) = (x + 1)*(x - 1)*(x - 4)
	vector<double> function;
	function.push_back(x + 1);
	function.push_back(x - 1);
	function.push_back(x - 4);
	return function;
}

vector<double> G(double x) { // G(x) = (x + 1)*(x - 1)*(x - 1)*(x - 4)
	vector<double> function;
	function.push_back(x + 1);
	function.push_back(x - 1);
	function.push_back(x - 1);
	function.push_back(x - 4);;
	return function;
}

double resultOfFunction(vector<double> function) {
	double result = 1;
	int count = function.size();
	for (int i = 0; i < count; i++) {
		result *= function[i];
	}
	return result;
}

vector<pair<double, double>> setRange(int chooseFunction , vector<double> inputRange) { // [0,5]를 받았다고 하면
	vector<pair<double, double>> rangeSets;
	double min = 0.0;
	double max = 0.0;
	int count = 0;

	cout << "Setted ranges are : ";
	if (chooseFunction == 1) { // Choose F(x) = (x + 1)*(x - 1)*(x - 4)
		while (count < 3) {
			min = F(inputRange[0])[count]; // 1, -1, -4
			max = F(inputRange[1])[count]; // 6, 4, 1
			rangeSets.push_back(make_pair(min,max)); // (1,6), (-1,4), (-4,1)
			cout << "<" << rangeSets[count].first << ", " << rangeSets[count].second << "> ";
			count++;
		}
		cout << "\n";
	}
	else { // Choose G(x) = (x + 1)*(x - 1)*(x - 1)*(x - 4)
		while (count < 4) {
			min = G(inputRange[0])[count]; // 1, -1, -1, -4
			max = G(inputRange[1])[count]; // 6, 4, 4, 1
			rangeSets.push_back(make_pair(min, max)); // (1,6), (-1,4), (-1,4), (-4,1)
			cout << "<" << rangeSets[count].first << ", " << rangeSets[count].second << "> ";
			count++;
		}
		cout << "\n";
	}
	return rangeSets;
}

vector<pair<double, double>> rangeComparison(vector<pair<double, double>> settedRanges) {
	vector<pair<double, double>> tempVector;
	int count = settedRanges.size();
	
	if (count == 1) {
		cout << "Range of J is <" << settedRanges[0].first << ", " << settedRanges[0].second << "> \n";
		return settedRanges; // 재귀의 끝에 1개의 값만 남긴다면, 그것이 J 범위이다. 
	}
	
	cout << "In this turn, the result : ";
	
	for (int i = 0; i < count-1; i++) { // 아래의 과정을 count-1번 반복한다. 
		vector<double> tempForSort; // 정렬을 위한 임시 벡터, 4개의 곱을 담은 다음 
		tempForSort.push_back(settedRanges[i].first * settedRanges[i + 1].first);
		tempForSort.push_back(settedRanges[i].first * settedRanges[i + 1].second);
		tempForSort.push_back(settedRanges[i].second * settedRanges[i + 1].first);
		tempForSort.push_back(settedRanges[i].second * settedRanges[i + 1].second);
		sort(tempForSort.begin(), tempForSort.end()); // 시작부터 끝까지 정렬한다. 작은게 앞이겠지? 
		tempVector.push_back(make_pair(tempForSort.front(), tempForSort.back())); // 그 중 최소, 최대만 뽑아서 tempVector에 삽입한다. 
		cout << "<" << tempVector[i].first << ", " << tempVector[i].second << "> ";
	} // 그러면 결과적으로 총 개수는 1개가 줄어들고, i와 i+1을 곱 연산한 결과들이 있는 벡터를 반환한다.
	cout << "\n";
 
	return rangeComparison(tempVector); // 그걸 재귀적으로 반복하다보면 1개가 남을거다.
}

vector<double> intervalMethod(vector<double> inputRange, int chooseFunction, int chooseResult, vector<double> root) {
	vector<pair<double, double>> tempRange;
	vector<double> J_Range;
	vector<double> I_FrontRange;
	vector<double> I_BackRange;
	int count = 0;
	
	double epsilon = 0.1;
	double middleOf_I = (inputRange[0] + inputRange[1]) / 2;
	cout << "====== IM Start ======\n";
	cout << "The inputRange <" << inputRange[0] << ", " << inputRange[1] << "> \n";

	// epsilon range check
	if ( abs(inputRange[1] - inputRange[0]) < epsilon) {
		if (chooseFunction == 1 && resultOfFunction(F(inputRange[0])) * resultOfFunction(F(inputRange[1])) < 0) {
			cout << "#########> Find root! = " << middleOf_I << "\n";
			root.push_back(middleOf_I);
			return root;
		}
		else if(chooseFunction == 2 && resultOfFunction(G(inputRange[0])) * resultOfFunction(G(inputRange[1])) < 0) {
			cout << "#########> Find root! = " << middleOf_I << "\n";
			root.push_back(middleOf_I);
			return root;
		}
		else {
			cout << "#########> Find multiple root! \n";
			return root;
		}
	}
	cout << "1. epsilon range check - OK\n";

	// Calculate J range
	tempRange = rangeComparison(setRange(chooseFunction, inputRange)); // J범위
	J_Range.push_back(tempRange[0].first);
	J_Range.push_back(tempRange[0].second);
	cout << "2. Calculate J range - OK\n";

	// J ragne check
	if (J_Range[0] * J_Range[1] > 0) {
		return root;
	}
	cout << "3. J range check - OK\n";

	// devide range
	I_FrontRange.push_back(inputRange[0]);
	I_FrontRange.push_back(middleOf_I);
	I_BackRange.push_back(middleOf_I);
	I_BackRange.push_back(inputRange[1]);
	cout << "4. Devide Range - OK\n";
	cout << "Front_Range <" << I_FrontRange[0] << ", " << I_FrontRange[1] << "> \n";
	cout << "Back_Range <" << I_BackRange[0] << ", " << I_BackRange[1] << "> \n";

	// IM(I1)
	root = intervalMethod(I_FrontRange, chooseFunction, chooseResult, root);
	cout << "5. IM(I1) -OK \n";

	// IM(I1) root list
	for (int i = 0; i < root.size(); i++) {
		cout << "@@'" << root[i] << "' ,";
	}
	cout << "\n";


	// check the result
	if (root.size() != 0 && chooseResult == 1) {
		cout << "Root is " << root.front() << "\n";
		return root;
	}
	else {
		cout << "6. Let's go to IM(I2)\n";
		return intervalMethod(I_BackRange, chooseFunction, chooseResult, root);
	}
}

int main(int argc, char** argv) {
	vector<pair<double, double>> settedRanges;
	vector<pair<double, double>> tempRange;
	vector<double> inputRange(2);
	vector<double> root;
	int chooseFunction = 0;
	int chooseResult = 0;
	double temp = 0;

	// 이것들 나중에 다 밖으로 빼버리자
	cout << "====== Input Information ======\n";
	cout << "Choose the Function\n" << "1. F  or  2. G  : ";
	cin >> chooseFunction;
	cout << "Choose the Result\n" << "1. First root  or  2. All root  : ";
	cin >> chooseResult;
	cout << "Input the Range\n";
	cout << "Min: ";
	cin >> inputRange[0];
	cout << "Max: ";
	cin >> inputRange[1];

	if (inputRange[0] > inputRange[1]) {
		temp = inputRange[0];
		inputRange[0] = inputRange[1];
		inputRange[1] = temp;
	}


	root = intervalMethod(inputRange, chooseFunction, chooseResult, root);
	cout << "The root of this Function = ";

	if (root.size() == 0) {
		cout << "No Root \n";
	}
	else {
		for (int i = 0; i < root.size(); i++) {
			cout << "'" << root[i] << "' ,";
		}
	}
	return 0;
}