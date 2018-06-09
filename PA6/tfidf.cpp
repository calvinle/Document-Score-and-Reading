#include <tfidf.h>
#include <tgmath.h>
#include <string>
#include <algorithm>
#include <iostream>

//return word count in doc
double Tfidf::tf(string word, map<string, int> doc){
		return double(doc[word]); 
}

//return n docs that word appears within N
double Tfidf::idf(string word){ //n <= N
	double n = 0.0;
	
	for (size_t i=0; i < this->N(); i++){
		map<string, int> d = doc(i);
		if (d.find(word) != d.end()){
			n+=1;
		}
	}
	return double(log10(double(this->N())/n));
}

double Tfidf::score(string word, map<string, int> doc){
	return double(tf(word, doc) * idf(word));
}

double Tfidf::Sim(map<string, int> doc1, map<string, int> doc2){
	double sum = 0.0;
	map<string, int>::iterator itr;
	vector<string> intersect;
	for (itr = doc2.begin(); itr != doc2.end(); ++itr){
		if (doc1.find(itr->first) != doc1.end()){
			intersect.push_back(itr->first);
		}
	}
	double f1, f2;
	for (size_t i=0; i < intersect.size(); i++){
		if (puncString(intersect[i]) == 0){
			f1 = score(intersect[i], doc1);
			f2 = score(intersect[i], doc2);
			sum += f1 * f2;
		}
	}
	return sum;

}

bool Tfidf::puncString(string token){
	for (size_t i=0; i < token.size(); i++){
		if ( ('!' <= token[i] && token[i] <= '&') ||
		( '(' <= token[i] && token[i] <= '/' ) ||
		(':' <= token[i] && token[i] <= '@') || 
		('[' <= token[i] && token[i] <= '`') || 
		('{' <= token[i] && token[i] <= '~') ) {
			return 1;
		}
	}
	return 0;
}
