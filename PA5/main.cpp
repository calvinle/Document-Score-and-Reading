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
	ifstream excFile(argv[1]); 				//1st Arg: Exception File
	ifstream inFile(argv[2]);  				//2nd Arg: Text file
	if (argc !=3){ 							//if not enough files
		cerr << "Need two files!" << endl;
		return -1;
	}
	if (!inFile || !excFile) {				//if not enough files
		cerr << "Error, file(s) required!\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof()){ //if text file empty
		cerr << "Error, empty file!\n";
 	 	return -1;
	}
	
	vector<string> words;
	string line;											//line to hold each line to parse
	while (getline(inFile, line)) { 						//while not empty line
		istringstream ss(line);
		string token;

		while( ss >> token ){								//token separated from white spaces
			vector<string> sent = tokenSplit(token); 		//create vector of broken up tokens
			for (size_t i=0; i < sent.size(); i++){ words.push_back(sent[i]); } //add them all to new vector
		}
		
		if (inFile.eof()){ break; }							//if end of file
	}
	vector<string> ex1;
	string line2;
	if (excFile.peek() != ifstream::traits_type::eof()){ 	//if not empty, parse exceptions prior to Porter
		while (getline(excFile, line2)) { 					//while not empty line
			size_t counter = 0; 							//must have 2 words/line. used to check
			istringstream ss2(line2); 						//capture line
			string token2;									//token2 intialized
			
			while( ss2 >> token2 ){ 						//token2 contains word(s separated by space)
				ex1.push_back(token2); 						//add to vector
				counter++; 									//increment counter
			}
			if (counter == 0){
				while(getline(excFile, line2)){
					if (isalnum(line2[0])){
						cerr << "Error" << endl;
						return -1;
					}
					if (excFile.eof()){
						break;
					}
				}
				break;
			}
			if (counter != 2){								//if counter not 2, then there aren't exactly 2 words a line
				cerr << "Can't have " << counter << " words on line" << endl;	//throw error
				return -1;
			}
			if (excFile.eof()){ break; }					//check for end of file (maybe?)	
		}
	}

	vector<string> newWords = capitalCheck(words);			//Capitalization Check
	
	//Check for ambiguous capitals
	for (size_t i = 0; i < newWords.size(); i++){
		if (newWords[i][0] == '+'){								 //if properly marked
		string c = newWords[i].substr(1, newWords[i].size()-1);  //create string var of token being checked without its +
			for (size_t j=0; j < newWords.size(); j++){ 		 //check rest of document for ambiguous marks
				if (c == newWords[j] && j != i){	//if found...
					newWords[i].erase(0,1);						//remove + from word
					break;
				}
				else if (j == newWords.size()-1 && newWords[i][0] == '+'){ //if reached end of doc and word[i] still unmarked
					newWords[i].erase(0,1);						//erase +
					newWords[i][0] += 32;						//convnert to lowercase
				}
			}
		}
	}
	
	//Exception File Parse prior to Porter
	for (size_t i=0; i < newWords.size(); i++){ //scan text file
		for (size_t j=0; j < ex1.size(); j++){
			if (newWords[i] == ex1[j] && j % 2 == 0){
				newWords[i] = ex1[j+1];
				break;
			}
		}
	}
	
	//Porter Algorithm
	for (size_t i = 0; i < newWords.size(); i++){
		if (newWords[i][0] != '+' && isAcro(newWords[i]) == false && 
		hasDigit(newWords[i]) == false && newWords[i].size() > 2){
			stemAlg(newWords[i]);
		}
	}
	
	//sort, check for empty
	sort(newWords.begin(), newWords.end());
	
	if (newWords.empty()) {
		cout << "Nothing!" << endl;
		return -1;
	}
	
	//output
	for (size_t i=0; i < newWords.size(); i++){
		int dup = 1;								//First encounter of word = 1
		for (size_t j=i+1; j < newWords.size(); j++){
			if (newWords[i] == newWords[j]){
				newWords[j].erase();				//if found, delete duplicate
				dup += 1;							//increment counter, verifying found match
			}
		}
		if (newWords[i] != ""){ cout << newWords[i] << " " << dup << endl; } //count output
	}
	
	return 0;
}
