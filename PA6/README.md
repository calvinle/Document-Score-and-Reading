Three or more (generally more) file names as read in as arguments. The first file is
the stemming exceptions file, as in PA5. The remaining N files are input files. The program will
read all the input files and process them (including stemming with exceptions) as in PA5 to create
a set of stemmed words. (Punctuation strings can be
ignored.) Instead of printing word frequencies, however, it will use the word counts to compare
input files to each other using TFIDF (see below). The output will no longer be a set list of term
frequencies. Instead, the output will have N lines of text, where N is the number of input files,
excluding the exceptions file. Each line of output contains N TFIDF similarity scores. The first
line of output contains the TFIDF score between the first file (excluding the exceptions file) and
itself, then the first file and the second file, the first file and the third file, and so on, ending with
the score between the first file and the Nth file. The second line of input contains the TFIDF
scores between the second file and the first file, the second file and itself, and so on. The scores
on a line should be separated by whitespace. <br/>
The first step is to associate a TFIDF score with every word in the document (punctuation strings
can be ignored). The TFIDF score for a word in a document is the product of two numbers, one of
which you have already computed:<br/><br/>

TFIDF(word,	doc)	=	tf(word,	doc)	*	idf(word) <br/><br/>

In this equation, tf(word, doc) is simply the number of times the word appears in the document.
This is what you have been computing and printing in PA5. The second term is the inverse
document frequency, and it is defined in terms of N (the total number of documents) and n, the
number of documents containing at least one instance of the word: <br/><br/>

idf(word) = log10(N / n) <br/><br/>

The idea of idf is that matching a really common word is less important than matching a rare one.
In the extreme, a word might appear in every document, in which case idf = log(1) = 0.
To measure the similarity between two documents, find the set of words that appear in both
documents. For every word in the intersection of the documents, multiply the two TFIDF scores
together, and sum those products. In other words: <br/><br/>

Sim(doc1, doc2) = Sw TFIDF(w, doc1) * TFIDF(w, doc2) <br/><br/>

Where the summation is over all words (including capitalized words, etc., but excluding
punctuation) that are common to both documents.
For PA6, your task is to compare every input document to every input document and print out the
matrix of document similarity. As described above, this should be N lines of output, each with N
similarity scores in order. Since similarity scores are higher when documents are similar, the
diagonal elements of this table (which compare documents to themselves) should be large.
