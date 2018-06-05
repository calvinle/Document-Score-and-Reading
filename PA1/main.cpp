#include <iostream>
#include <fstream>
#include "count.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
	
	//Take in input file
	ifstream inFile(argv[1]); 
	if (!inFile) {
		std::cerr << "Error, file required!\n";
		return -1;
	}
	if ( inFile.peek() == std::ifstream::traits_type::eof() ){
		std::cerr << "Error, empty file!\n";
 	 	return -1;
	}
	int counter[20] = { 0 };

	std::string line;
	//read line at a time (in case if newLine breaks!)
	while (std::getline(inFile, line) && !inFile.eof()) {
		std::istringstream ss(line);
		std::string token;
        
		int num;
		while(ss >> token){
			if (token == "-0"){
				counter[0] += 1;
				continue;
			}
			if (elementCheck(token) == true){
				stringstream(token) >> num;
				counter[num] += 1;
			}
			else //Invalid element
				std::cerr << "Error, (" << token << ") is invalid. Exiting" << endl;
				return -1;
			}
		}
	}
	
	for (size_t x = 0; x < 20; x++){
        if (counter[x] != 0){
            printResults(counter);
            return 0;
        }
    }
    	std::cerr << "Error, no elements found" << endl;
    		return -1;
}
