The program will take a single filename as its argument, and will write a single number -- the
reading level of the document -- to std::cout. (Unless, of course, there is an error, in which case it
will print an error message to std::cerr and return -1.) <br/>
The reading level of the input file is determined by the CL index. You will parse the input file
into a sequence of word strings and punctuation strings as in PA3. <br/><br/>
You will calculate the termL(doc) by counting the total number of letters in the word strings in the file (i.e. not including
punctuation or spaces). You will also count the number of word strings in the document, and
divide the number of letters by 100 times the number of word strings. Note that you should not
assume that there are 100 words in the document. <br/><br/>
To compute S(doc) you need to know the number of sentences, which is the same as the number
of punctuation strings that end sentences (i.e. that contain a period, question mark, or exclamation
point). You then divide this number by 100 times the number of words.
Finally, you compute the CL index as: <br/>
CL(doc) = 0.0588L(doc) – 0.296S(doc) – 15.8
