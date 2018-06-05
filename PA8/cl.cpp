#include <string>
#include <vector>
#include <iostream>
#include "cl.h"
using namespace std;

double CL(vector<string> doc){
	return (0.0588 * Letter(doc)) - (0.296 * Sentence(doc)) - 15.8;
}

double Sentence(vector<string> doc){
	double sCount = 0;
	double wCount = 0;
	
	for (size_t i=0; i < doc.size(); i++){
		if (sentEnd(doc[i]) == true){
			sCount++;
		}
		else if (isWord(doc[i])){
			wCount++;
		}
	}
	//cout << "Sentences: " << sCount << endl;
	//cout << "Words: " << wCount << endl;
	return (sCount / wCount) * 100;
}

double Letter(vector<string> doc){
	double wCount = 0;
	double lCount = 0;
	
	for (size_t i=0; i < doc.size(); i++){
		if (isWord(doc[i])){					//if valid word
			lCount += doc[i].length();		//add string length to lCount
			wCount++;						//increment wCount
		}
	}
	//cout << "Letters : " << lCount << endl;
	return (lCount / wCount) * 100;
}

bool isWord(string w){						//if string is valid word
	for (size_t i=0; i < w.length(); i++){	//iterate
		if (w[i] == '\''){					//ignore apostrophe's
			continue;
		}
		if (w[i] == '.' && isdigit(w[i+1])){
			continue;
		}
		if (i > 0 && (w[i] == '.' || w[i] == ',') && isdigit(w[i-1]) && isdigit(w[i+1]) ){ //2.3
			continue;
		}
		if (isdigit(w[i]) || isalpha(w[i])){
			continue;
		}
		else
			return false;
	}
	return true;
}

bool sentEnd(string p){
	for (size_t i=0; i < p.length()	; i++){
		if (p[i] == '!' || p[i] == '?' || p[i] == '.'){
			return true;
		}
	}
	return false;
}