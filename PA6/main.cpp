#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "word.h"
#include "split.h"
#include "tfidf.h"
#include <map>
#include <iomanip>


int main(int argc, char* argv[]) {
	if (argc < 4){
		std::cerr << "Need at least 3 files!" << endl;
		return -1;
	}	
	ifstream excFile(argv[1]);
	if (!excFile) {
		std::cerr << "Error, file(s) required!\n";
		return -1;
	}
	
	//Exception File
	vector<string> ex1;
	string line2;
	if (excFile.peek() != ifstream::traits_type::eof()){ 	//if not empty, parse exceptions prior to Porter
		while (getline(excFile, line2)) {
			size_t counter = 0;
			istringstream ss2(line2);
			string token2;
			
			while( ss2 >> token2 ){ 
				ex1.push_back(token2);
				counter++;
			}
			if (counter == 0){
				while(getline(excFile, line2)){
					if (isalnum(line2[0])){
						std::cerr << "Error" << endl;
						return -1;
					}
					if (excFile.eof()){
						break;
					}
				}
				break;
			}
			if (counter != 2){
				std::cerr << "EXCEPTION FILE: Can't have " << counter << " words on line" << endl;
				return -1;
			}
			if (excFile.eof()){ break; }	
		}
	}
	
	map<string, int> doc;
	vector<map<string, int>> c;
	//document analyzed
	for (int i=2; i < argc; i++){
		map<string, int> doc;
		ifstream inFile(argv[i]);
		if ( inFile.peek() == std::ifstream::traits_type::eof()){
			cerr << "Error, File " << i - 2 << " empty!\n";
			return -1;
		}
		
		vector<string> words;
		string line;
		while (getline(inFile, line)) {
			istringstream ss(line);
			string token;

			while( ss >> token ){
				vector<string> sent = tokenSplit(token);
				for (size_t i=0; i < sent.size(); i++){ words.push_back(sent[i]); }
			}
			if (inFile.eof()){ break; }
		}
		vector<string> newWords = capitalCheck(words); //Capitalization Check
		
		//Check for ambiguous capitals
		for (size_t i = 0; i < newWords.size(); i++){
			if (newWords[i][0] == '+'){
			string c = newWords[i].substr(1, newWords[i].size()-1);
				for (size_t j=0; j < newWords.size(); j++){ 
					if (c == newWords[j] && j != i){
						newWords[i].erase(0,1);
						break;
					}
					else if (j == newWords.size()-1 && newWords[i][0] == '+'){
						newWords[i].erase(0,1);
						newWords[i][0] += 32;
					}
				}
			}
		}
		
		//Exception File Parse prior to Porter
		for (size_t i=0; i < newWords.size(); i++){
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
				step1(newWords[i]);
			}
		}
		
		sort(newWords.begin(), newWords.end());
		
		if (newWords.empty()) {
			std::cout << "Nothing!" << endl;
			return -1;
		}
		
		vector<string> strings;
		vector<int> counts;
		for (size_t i=0; i < newWords.size(); i++){
			int dup = 1;
			for (size_t j=i+1; j < newWords.size(); j++){
				if (newWords[i] == newWords[j]){
					newWords[j].erase();
					dup += 1;
				}
			}
			if (newWords[i] != ""){
				doc[newWords[i]] = dup;
			}
		}
		c.push_back(doc);
	}
	Tfidf lib1(c);
	
	for (size_t i=0; i < lib1.N(); i++){
		for (size_t j=0; j < lib1.N(); j++){
			std::cout << fixed << setprecision(6) << lib1.Sim(lib1.doc(i), lib1.doc(j)) << " ";
		}
	}
	return 0;
}
