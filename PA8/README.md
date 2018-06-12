The program will take two filenames and two numbers as arguments, and write out a single
filename to std::cout. The first input file is the document you are comparing to. It is a standard
text document. The second file is more complicated. It contains a series of filenames separated by
whitespace, so that they can be read using the >> operator. <br/></br>
The first filename in the second file is the
name of the exceptions file. All other filenames in the second file are the names of background
documents. <br/><br/>
The third and fourth arguments are numbers, specifically the lowest reading level (as
defined by the Coleman-Liau Index) allowed and the highest reading level. It is an error if the
third value is greater than the fourth.<br/><br/>
The program will analyze the reading level of every background document, as in PA7. Then,
for documents whose reading level is within the target range (as determined by the 3rd and 4th
arguments), compare them to the target document using TFIDF (as in PA7). The filename of the most similar document to the 
target document that is within the target reading will print to std:cout.
