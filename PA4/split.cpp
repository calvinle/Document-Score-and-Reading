#include "split.h"
#include <iostream>
#include <vector>
using namespace std;

vector<string> tokenSplit(string token){
	vector<string> elements; //returning new vector of broken vectors
	size_t i = 0; //index to be manually incremented
	size_t n = 0; //second var n to capture previous i before it gets incremented
	while (i != token.size()){ //until index reaches end of token	
		if ( isalpha(token[n]) || isdigit(token[n]) || (token[n] == '\'') ){ //alphaNum or '
			i += alphaNumScan(token, n, i);	
			elements.push_back(token.substr(n,i-n)); //add substring of beginning index to incremented index
			n = i; //n captures index previous i before i increments
		}
		
		if ( validPunc(token, i) == true){ //begin looking for string of punc
			i += puncScan(token, n, i);
			elements.push_back(token.substr(n,i-n)); //add substring of beginning index to incremented index
			n = i; //n captures index previous i before i increments
		}
	}
	return elements;
}
			
vector<string> capitalCheck(vector<string> elements){
	//If 1)Capital, 2)notAcronym, 3)noDigit, 4)first word of sentence
	//Mark with +
	vector<string> newVec;
	for (size_t i=0; i < elements.size(); i++){
		if ( isAcro(elements[i]) == true || hasDigit(elements[i]) == true){
			newVec.push_back(elements[i]);
			continue;
		}
		if ( i == 0 && isupper(elements[i][0]) && isAcro(elements[i]) == false && hasDigit(elements[i]) == false) {
			newVec.push_back("+" + elements[i]);
			continue;
		}
		if ( (i > 0) && (isupper(elements[i][0])) && ( elements[i-1].find('.') != string::npos || elements[i-1].find('!') != string::npos || elements[i-1].find('?') != string::npos )  &&isAcro(elements[i]) == false && (hasDigit(elements[i]) == false) ){
			newVec.push_back("+" + elements[i]);
			continue;
		}
		else{
			newVec.push_back(elements[i]);
		}
	}
	return newVec;
}

size_t alphaNumScan(string token, size_t start, size_t index){
	size_t i = start;
	size_t counter = 0;
	while ( (isalpha(token[i])  || (isdigit(token[i])) || token[i] == '\'' ) && (i != token.size())){	
		if (isdigit(token[i]) || isalpha(token[i]) || token[i] == '\''){
			i++;
			counter++;
		}
		if (token[i] == ',' && isdigit(token[i-1]) && isdigit(token[i+1])){
			i++;
			counter++;
		}
		if (token[i] == '.' && isdigit(token[i-1]) && isdigit(token[i+1])){
			i++;
			counter++;
		}
	}
	return counter;
}

size_t puncScan(string token, size_t start, size_t index){
	size_t i = start;
	size_t counter = 0;
	while ( validPunc(token, i) == true && i != token.size()){ //any punc except apostrophe
		if ((token[i] == '.') && (isdigit(token[i+1])) && counter==0){ //handle cases similar to .01
            counter+=1;
			i+=1;
			while (validPunc2(token, i) != 1){//while not punc //.9.9.39.8p.
				if ( token[i] == '.' && isalpha(token[i-1]) && i == token.size()-1 ){
					counter--;
					break;
				}
				if (isdigit(token[i]) || isalpha(token[i])){
					counter++;
					i++;
                    continue;
				}
				if ( (token[i] == '.') && isdigit(token[i-1]) && isdigit(token[i+1])){
					counter++;
					i++;
					continue;
				}
				if ( (token[i] == '.') && isdigit(token[i-1]) && !(isdigit(token[i+1])) ){
					break;
				}
				else if ( (token[i] == '.') && isdigit(token[i-1]) && !(isdigit(token[i+1])) ){
					counter++;
					i++;
					break;
				}
				if ( (token[i] == ',' ) && isdigit(token[i-1]) && isdigit(token[i+1])){
					counter++;
					i++;
					continue;
				}
				break;
			}
		}
		if (validPunc(token,i)){
			i++;
			counter++;
		}
		if (isalpha(token[i]) || isdigit(token[i])){
			break;
		}
	}
	return counter;
}

bool isAcro(string token){
	for (size_t i=1; i<token.size(); i++){
		if (isupper(token[i]) != 0){
			return true;
		}
	}
	return false;
}

bool hasDigit(string token){
	for (size_t i=0; i<token.size(); i++){
		if (isdigit(token[i]) != 0){
			return true;
		}
	}
	return false;
}

bool validPunc(string token, size_t i) {
	if ( ('!' <= token[i] && token[i] <= '&') || //exclude apostrophe
		( '(' <= token[i] && token[i] <= '/' ) ||
		(':' <= token[i] && token[i] <= '@') || 
		('[' <= token[i] && token[i] <= '`') || 
		('{' <= token[i] && token[i] <= '~') ) {
			return 1;
		}
		return 0;
}

bool validPunc2(string token, size_t i) {
	if ( ('!' <= token[i] && token[i] <= '+') || //exclude , and .
		( token[i] == '-' ) ||
		(token[i] == '/') || 
		(':' <= token[i] && token[i] <= '@') ||
		('[' <= token[i] && token[i] <= '`') || 
		('{' <= token[i] && token[i] <= '~') ) {
			return 1;
		}
		return 0;
}



bool perOrCom(char sym){
    if (sym == '.' || sym == ','){
        return 1;
    }
    return 0;
}
