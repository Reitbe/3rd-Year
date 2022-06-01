#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

// F(x) = (x + 1)(x - 1)(x - 4) = 0
vector<double> F(double x) {
	vector<double> function;
	function.push_back(x + 1);
	function.push_back(x - 1);
	function.push_back(x - 4);
	return function;
}

// G(x) = (x + 1)(x - 1)(x - 1)(x - 4) = 0
vector<double> G(double x) { 
	vector<double> function;
	function.push_back(x + 1);
	function.push_back(x - 1);
	function.push_back(x - 1);
	function.push_back(x - 4);
	return function;
}

// Result value of function
double resultOfFunction(vector<double> function) {
	double result = 1.0;
	int count = function.size();

	for (int i = 0; i < count; i++) {
		result *= function[i];
	}
	return result;
}

// From entered function, get the range pair vector
vector<pair<double, double>> setRange(int chooseFunction , vector<double> inputRange) { 
	vector<pair<double, double>> rangeSets;
	double min = 0.0;
	double max = 0.0;
	int count = 0;

	if (chooseFunction == 1) { 
		// When you choose "F", results are <(1,6), (-1,4), (-4,1)>
		while (count < 3) {
			min = F(inputRange[0])[count]; 
			max = F(inputRange[1])[count]; 
			rangeSets.push_back(make_pair(min,max)); 
			count++;
		}
	}
	else { 
		// When you choose "G", results are <(1,6), (-1,4), (-1,4), (-4,1)>
		while (count < 4) {
			min = G(inputRange[0])[count]; 
			max = G(inputRange[1])[count]; 
			rangeSets.push_back(make_pair(min, max));  
			count++;
		}
	}
	return rangeSets;
}


//  From range pair vector, get the range of "J"
vector<pair<double, double>> rangeComparison(vector<pair<double, double>> settedRanges) {
	vector<pair<double, double>> tempVector;
	int count = settedRanges.size();
	
	// return range of "J"
	if (count == 1) {
		return settedRanges;
	}
	
	for (int i = 0; i < count-1; i++) { 
		vector<double> tempForSort;

		tempForSort.push_back(settedRanges[i].first * settedRanges[i + 1].first);
		tempForSort.push_back(settedRanges[i].first * settedRanges[i + 1].second);
		tempForSort.push_back(settedRanges[i].second * settedRanges[i + 1].first);
		tempForSort.push_back(settedRanges[i].second * settedRanges[i + 1].second);

		sort(tempForSort.begin(), tempForSort.end()); 
		tempVector.push_back(make_pair(tempForSort.front(), tempForSort.back())); 
	}

	return rangeComparison(tempVector); 
}

// Interval Method
vector<double> intervalMethod(vector<double> inputRange, int chooseFunction, int chooseResult, vector<double> root) {
	vector<pair<double, double>> tempRange;
	vector<double> J_Range;
	vector<double> I_FrontRange;
	vector<double> I_BackRange;	
	double epsilon = 0.01;
	double middleOf_I = (inputRange[0] + inputRange[1]) / 2;
	int count = 0;

	// Print of I
	cout << "Range of I is <" << inputRange[0] << ", " << inputRange[1] << "> \n";

	// Epsilon range and Multiple root check
	if ( abs(inputRange[1] - inputRange[0]) < epsilon) {
		// Multiple root check : F(x)
		if (chooseFunction == 1 && resultOfFunction(F(inputRange[0])) * resultOfFunction(F(inputRange[1])) < 0) {
			root.push_back(middleOf_I);
			return root;
		}
		// Multiple root check : G(x)
		else if(chooseFunction == 2 && resultOfFunction(G(inputRange[0])) * resultOfFunction(G(inputRange[1])) < 0) {
			root.push_back(middleOf_I);
			return root;
		}
		else {
			return root;
		}
	}

	// Calculate J range
	tempRange = rangeComparison(setRange(chooseFunction, inputRange)); 
	J_Range.push_back(tempRange[0].first);
	J_Range.push_back(tempRange[0].second);

	// J ragne check
	if (J_Range[0] * J_Range[1] > 0) {
		return root;
	}

	// Devide range
	I_FrontRange.push_back(inputRange[0]);
	I_FrontRange.push_back(middleOf_I);
	I_BackRange.push_back(middleOf_I);
	I_BackRange.push_back(inputRange[1]);

	// IM(I1)
	root = intervalMethod(I_FrontRange, chooseFunction, chooseResult, root);

	// Check the result
	// When you choose "1_st root only"
	if (root.size() != 0 && chooseResult == 1) {
		return root;
	}
	// When you choose "all root"
	else {
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

	// Input Information
	cout << "====== Input Information ======\n";
	cout << "Choose the Function\n" << "1. F  or  2. G  : ";
	cin >> chooseFunction;
	cout << "Choose the Result\n" << "1. 1_st root only  or  2. All root  : ";
	cin >> chooseResult;
	cout << "Input the Range\n";
	cout << "Min: ";
	cin >> inputRange[0];
	cout << "Max: ";
	cin >> inputRange[1];

	// InputRange sort
	if (inputRange[0] > inputRange[1]) {
		temp = inputRange[0];
		inputRange[0] = inputRange[1];
		inputRange[1] = temp;
	}

	// Start Interval Method
	cout << "\n====== Calculating... ======\n";
	root = intervalMethod(inputRange, chooseFunction, chooseResult, root);
	
	// Print Roots
	cout << "\n====== Result ======\n";
	cout << "The root of this Function = ";
	if (root.size() == 0) {
		cout << "No Root \n";
	}
	else {
		for (int i = 0; i < root.size(); i++) {
			cout << "'" << root[i] << "' ,";
		}
	}
	cout << "\n\n";
	return 0;
}