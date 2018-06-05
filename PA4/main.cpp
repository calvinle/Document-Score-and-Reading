#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "word.h"
#include "split.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream inFile(argv[1]); //Take in input file
	ifstream excFile(argv[2]); //file of exceptions
	if (!inFile) {
		cerr << "Error, file required! LOL\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof() ){
		cerr << "Error, empty file!\n";
 	 	return -1;
	}
	
	vector<string> words;
	string line;
	
	while (std::getline(inFile, line)) {
		istringstream ss(line);
		string token;

		while( ss >> token ){	//token separated from white spaces
			vector<string> sent = tokenSplit(token); //create vector of broken up tokens
			for (size_t i=0; i < sent.size(); i++){ words.push_back(sent[i]); } //add them all to new vector
		}
		if (inFile.eof()){ break; }	
	}
	
	vector<string> newWords = capitalCheck(words);
	
	/*
	for (size_t i = 0; i < newWords.size(); i++){
		if (newWords[i][0] != '+' && isAcro(newWords[i]) == false && 
		hasDigit(newWords[i]) == false && newWords[i].size() > 2){
			stemAlg(newWords[i]);
		}
	}
	*/
	
	sort(newWords.begin(), newWords.end());
	if (newWords.empty()) {
		cout << "Nothing!" << endl;
		return -1;
	}
	
	
	for (size_t i=0; i < newWords.size(); i++){
		int dup = 1;	//First encounter of word = 1
		for (size_t j=i+1; j < newWords.size(); j++){
			if (newWords[i] == newWords[j]){
				newWords[j].erase();
				dup += 1;
			}
		}
		if (newWords[i] != ""){ cout << newWords[i] << " " << dup << endl; }
	}
	
	

	return 0;
}
