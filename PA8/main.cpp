#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <math.h>
#include "word.h"
#include "split.h"
#include "tfidf.h"
#include "cl.h"


using namespace std;

int main(int argc, char* argv[]) {
	//ERROR OF ARGS/ARGC
	if (argc != 5){
		cerr << "Need 2 files && 2 numbers!" << endl;
		return -1;
	}
	
	ifstream inFile(argv[1]);
	if (!inFile) {
		cerr << "Error, foreground file required!\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof() ){
		cerr << "Error, empty foreground file!\n";
 	 	return -1;
	}	
	
	ifstream bgFile(argv[2]); 				//1st Arg: Exception File. First doc at argv[2]. Last is at argv[argc-1]
	if (!bgFile) {							//if exec. files doesn't exist...
		cerr << "Error, file(s) required!\n";
		return -1;
	}
	if ( bgFile.peek() == std::ifstream::traits_type::eof() ){
		cerr << "Error, empty background file!\n";
 	 	return -1;
	}
	
	double lowRange = atof(argv[3]);
	double hiRange = atof(argv[4]);
	if (lowRange > hiRange){
		cerr << "Error in reading level range!" << endl;
		return -1;
	}

	//READ BACKGROUND FILE FOR ALL BACKGROUND DOCS
	string bgLine;
	vector<string> bgDocs;
	if (bgFile.peek() != ifstream::traits_type::eof()){			//if bgFile not empty, proceed
		while (getline(bgFile, bgLine)){						//per line
			istringstream bgStream(bgLine);
			string bgToken;
			
			while (bgStream >> bgToken){						//parse line to token past whitespace
				//cout << bgToken << endl;
				bgDocs.push_back(bgToken);						//add to list of bgDocs
			}
		}
	}
	else{ cerr << "Background File empty" << endl; return -1; } //if bgFile empty, ERROR
	if (bgDocs.size() == 1) { cerr << "No query docs!" << endl; return -1; }
	
	
	//Exception File
	ifstream excFile(bgDocs[0]);
	vector<string> exc;
	string line2;
	if (excFile.peek() != ifstream::traits_type::eof()){ 	//if not empty, parse exceptions prior to Porter
		while (getline(excFile, line2)) { 					//while not empty line
			size_t counter = 0; 							//must have 2 words/line. used to check
			istringstream ss2(line2); 						//capture line
			string token2;									//token2 intialized
			
			while( ss2 >> token2 ){ 						//token2 contains word(s separated by space)
				exc.push_back(token2); 						//add to vector
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
				cerr << "EXCEPTION FILE: Can't have " << counter << " words on line" << endl;	//throw error
				return -1;
			}
			if (excFile.eof()){ break; }					//check for end of file (maybe?)	
		}
	}
	bgDocs.erase(bgDocs.begin());							//Remove exception filename
	bgDocs.insert(bgDocs.begin(), argv[1]);					//Add orig. file of argv[1] for linear comparison
	vector<double> scoreList;								//Track CL scores for each document

	map<string, int> doc;
	vector<map<string, int>> c;
	//All bgDocs: READ(PA2), SPLIT(PA3), CLScore(PA7), CAPITALcheck(PA5), EXCEPTION(PA5), PORTER(PA4), sort, TFIDF(PA6)
	for (size_t i=0; i < bgDocs.size(); i++){
		//READ(PA2)
		map<string, int> doc;										//new instance of doc
		ifstream inFile(bgDocs[i]);									//open Stream for file
		if ( inFile.peek() == std::ifstream::traits_type::eof()){ 	//if text file empty
			cout << i << endl;
			cerr << "Error, File " << bgDocs[i] << " empty!\n";			//ERROR
			return -1;
		}

		//SPLIT(PA3)
		vector<string> words;										
		string line;
		while (getline(inFile, line)){								//Parse Doc
			istringstream ss(line);
			string token;

			while( ss >> token ){									//Token separated from white spaces
				vector<string> sent = tokenSplit(token); 			//Vector of broken up tokens
				for (size_t i=0; i < sent.size(); i++){ words.push_back(sent[i]); } //Add splitTokens to overall doc
			}
			if (inFile.eof()){ break; }								//Stop at End of File
		}
		
		//CLScore(PA7)
		if (isnan(CL(words)) != 0){ cerr << "Error: Division by 0!" << endl; return -1; }
		else {
			scoreList.push_back(CL(words));				//Index of bgDoc matches ScoreList to track
			//cout << CL(words) << endl;				//bgDoc[i] = scoreList[i]
		}
		
		//CAPITALcheck(PA5)
		vector<string> newWords = capitalCheck(words);							//Find ambiguous Capitals
		for (size_t i = 0; i < newWords.size(); i++){
			if (newWords[i][0] == '+'){								 			//For marked ambiguous
			string c = newWords[i].substr(1, newWords[i].size()-1);  			//Copy of marked word without its '+'
				for (size_t j=0; j < newWords.size(); j++){ 		 			//Check rest of document for ambiguous marks
					if (c == newWords[j] && j != i){							//If found...
						newWords[i].erase(0,1);									//Remove '+' from word
						break;
					}
					else if (j == newWords.size()-1 && newWords[i][0] == '+'){ 	//If not Found
						newWords[i].erase(0,1);									//Erase +
						newWords[i][0] += 32;									//Convert to lowercase
					}
				}
			}
		}
		
		//EXCEPTION(PA5)
		for (size_t i=0; i < newWords.size(); i++){ //scan text file
			for (size_t j=0; j < exc.size(); j++){
				if (newWords[i] == exc[j] && j % 2 == 0){
					newWords[i] = exc[j+1];
					break;
				}
			}
		}
		
		//PORTER(PA4)
		for (size_t i = 0; i < newWords.size(); i++){
			if (newWords[i][0] != '+' && isAcro(newWords[i]) == false && 
			hasDigit(newWords[i]) == false && newWords[i].size() > 2){
				step1(newWords[i]);
			}
		}

		
		//sort
		sort(newWords.begin(), newWords.end());
		if (newWords.empty()) {
			cerr << "Nothing!" << endl;
			return -1;
		}
		
		//TFIDF(PA6)
		vector<string> strings;
		vector<int> counts;
		for (size_t i=0; i < newWords.size(); i++){
			int dup = 1;								//First encounter of word = 1
			//cout << newWords[i] << endl;
			for (size_t j=i+1; j < newWords.size(); j++){
				if (newWords[i] == newWords[j]){
					newWords[j].erase();				//if found, delete duplicate
					dup += 1;							//increment counter, verifying found match
				}
			}
			if (newWords[i] != ""){
				doc[newWords[i]] = dup;
			}
		}
		c.push_back(doc);
	}
	Tfidf lib1(c);
	double largestScore = 0.0;
	size_t docIndex = 0;
	for (size_t i=1; i < lib1.N(); i++){ //Compare all to first document
		if ( (lowRange <= scoreList[i]) && (scoreList[i] <= hiRange) && (lib1.Sim(lib1.doc(0), lib1.doc(i)) > largestScore) ){
			largestScore = lib1.Sim(lib1.doc(0), lib1.doc(i));
			docIndex = i;
		} 
	}
	if (docIndex != 0) {cout << bgDocs[docIndex] << endl;}
	if (largestScore == 0.0){cout << bgDocs[0] << endl;}
	//else{cerr << "None found" << endl; return -1;}
	return 0;
}
