#include <vector>
#include <string>

vector<string> tokenSplit(string token);

vector<string> capitalCheck(vector<string> elements);

bool isAcro(string token);

bool hasDigit(string token);

bool validPunc(string token, size_t i);

size_t alphaNumScan(string token, size_t start, size_t index);

size_t puncScan(string token, size_t start, size_t index);

bool perOrCom(char sym);

bool validPunc2(string token, size_t i);
