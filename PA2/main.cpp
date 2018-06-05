#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    
    
	ifstream inFile(argv[1]); //Take in input file
	if (!inFile) {
		cerr << "Error, file required!\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof() ){
		cerr << "Error, empty file!\n";
 	 	return -1;
	}

	std::vector<string> words;
	std::string line;
	
	while (std::getline(inFile, line)) {
		//read line at a time (in case if newLine breaks!)
		std::istringstream ss(line);
		std::string token;
		while( ss >> token ){
			words.push_back(token);		
		}
		if (inFile.eof()){
			break;
		}
    }
	sort(words.begin(), words.end());
	
	for (size_t i=0; i < words.size(); i++){
		int dup = 1;
		for (size_t j=i+1; j < words.size(); j++){
			if (words[i] == words[j]){
				words[j].erase();
				dup += 1;
			}
		}
		if (words[i] != ""){
			cout << words[i] << " " << dup << endl;
		}
		
	}
	if (words.empty()){
		cerr << "Empty" << endl;
		return -1;
	}
    return 0;    
}
