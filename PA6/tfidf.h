#include <vector>
#include <string>
#include <stdbool.h>
#include <map>
using namespace std;

/*
 * TFIDF CALCULATOR
 */
class Tfidf { 
	public:
		Tfidf(vector<map<string, int> > d) : lib(d){}
		double tf(string word, map<string, int> doc); //# of times word appears in doc
		double idf(string word);										   //# of times word appears in library
		double score(string word, map<string, int> doc); //Total TFIDF score of doc
		double Sim(map<string, int> doc1, map<string, int> doc2);
		
        /**
        * Here is a documentation of the N() function
        * Used to return the size.
        * In other words, number of documents being handled.
        * Neat?
        */
		inline size_t N(){ return lib.size();}					 //# of docs in library
		inline map<string, int> doc(int i){ return lib[i];}			 //Return document
		bool puncString(string word);
	protected:
		vector<map<string, int> > lib; //has all docs
		
};
