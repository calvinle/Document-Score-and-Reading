#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "word.h"
#include "split.h"

int main(int argc, char* argv[]) {
	ifstream inFile(argv[1]); //Take in input file
	ifstream excFile(argv[2]); //file of exceptions
	if (!inFile) {
		std::cerr << "Error, file required! LOL\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof() ){
		std::cerr << "Error, empty file!\n";
 	 	return -1;
	}
	
	vector<string> words;
	string line;
	
	while (std::getline(inFile, line)) {
		istringstream ss(line);
		string token;

		while( ss >> token ){
			vector<string> sent = tokenSplit(token);
			for (size_t i=0; i < sent.size(); i++){ words.push_back(sent[i]); }
		}
		if (inFile.eof()){ break; }	
	}
	vector<string> newWords = capitalCheck(words);
	
	sort(newWords.begin(), newWords.end());
	if (newWords.empty()) {
		std::cout << "Nothing!" << endl;
		return -1;
	}
	
	for (size_t i=0; i < newWords.size(); i++){
		int dup = 1;
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
