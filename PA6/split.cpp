#include "split.h"
#include <iostream>
#include <vector>
using namespace std;

vector<string> tokenSplit(string token){
	vector<string> elements;
	size_t i = 0;
	size_t n = 0; 
	while (i != token.size()){
		if ( isalpha(token[n]) || isdigit(token[n]) || (token[n] == '\'') ){
			i += alphaNumScan(token, n, i);	
			elements.push_back(token.substr(n,i-n));
			n = i; 
		}
		
		if ( validPunc(token, i) == true){
			i += puncScan(token, n, i);
			elements.push_back(token.substr(n,i-n));
			n = i;
		}
	}
	return elements;
}

//If 1)Capital, 2)notAcronym, 3)noDigit, 4)first word of sentence
//Mark with +			
vector<string> capitalCheck(vector<string> elements){
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

//next set of iterating begins on alphaNum'
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

//next set of iterating begins on punc
size_t puncScan(string token, size_t start, size_t index){
	size_t i = start;
	size_t counter = 0;
	while ( validPunc(token, i) == true && i != token.size()){ //any punc except apostrophe
		if ((token[i] == '.') && (isdigit(token[i+1])) && counter==0){ //handle cases similar to .01
            counter+=1;
			i+=1;
			while (validPunc2(token, i) != 1){
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

//check if token is acroNym
bool isAcro(string token){
	for (size_t i=1; i<token.size(); i++){
		if (isupper(token[i]) != 0){
			return true;
		}
	}
	return false;
}

//check if token contains d1git
bool hasDigit(string token){
	for (size_t i=0; i<token.size(); i++){
		if (isdigit(token[i]) != 0){
			return true;
		}
	}
	return false;
}

//check if character is punc (exclude apostrophe)
bool validPunc(string token, size_t i) {
	if ( ('!' <= token[i] && token[i] <= '&') ||
		( '(' <= token[i] && token[i] <= '/' ) ||
		(':' <= token[i] && token[i] <= '@') || 
		('[' <= token[i] && token[i] <= '`') || 
		('{' <= token[i] && token[i] <= '~') ) {
			return 1;
		}
		return 0;
}

//check if character is , or .
bool validPunc2(string token, size_t i) {
	if ( ('!' <= token[i] && token[i] <= '+') ||
		( token[i] == '-' ) ||
		(token[i] == '/') || 
		(':' <= token[i] && token[i] <= '@') ||
		('[' <= token[i] && token[i] <= '`') || 
		('{' <= token[i] && token[i] <= '~') ) {
			return 1;
		}
		return 0;
}

//check if char is , or .
bool perOrCom(char sym){
    if (sym == '.' || sym == ','){
        return 1;
    }
    return 0;
}
