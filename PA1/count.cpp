#include "count.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

void printResults(int numbers[]){
    for (std::size_t c = 0; c < 20; c++){
        std::cout << c << " " << numbers[c] << "\n";
    }
}

bool elementCheck(string element){
    int num;
    for (std::size_t x = 0; x < element.size()-1; x++){
        if (isdigit(int(element[x])) == 0){
            return false;
        }
    }
    stringstream(element) >> num;
    if ( (num < 0) || (num > 19) ){
        return false;
    }
    else
        return true;
}
