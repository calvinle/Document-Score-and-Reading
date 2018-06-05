#include "count.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void printResults(int numbers[]){
    for (std::size_t c = 0; c < 20; c++){
        std::cout << c << " " << numbers[c] << "\n";
        //     "x"   " "    "<x counter>"
    }
}

bool elementCheck(string element){
    //Rules out decimal/float/double/negatives
    int num;
    for (std::size_t x = 0; x < element.size()-1; x++){
        if (isdigit(int(element[x])) == 0){
            //cout << "Not a digit!\n";
            return false;
        }
    }

    //confirmed int
    stringstream(element) >> num;
    if ( (num < 0) || (num > 19) ){
        return false;
    }

    else
        return true;
}
