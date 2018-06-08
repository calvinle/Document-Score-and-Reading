Capitalization Fixes: <br/>
If a word is marked ambiguously capitalized at least twice in the same document (i.e: a "+" appended to the beginning, e.g: "+word" appears twice in our list of separated words), remove the "+" and capitalize it. This occurs prior to Porter Stemming. 
Otherwise, remove the "+" and convert the first letter to lowercase.

Exception Cases: <br/>
The Porter algorithm stems words correctly most of the time – more than other approaches. But it makes
mistakes, so your PA5 algorithm will take two filenames as arguments. The second is the text file to be
analyzed. The first, however, is now a file of stemming exceptions. Each line of the exception file contains
two words, separated by a space. The first is a word to be stemmed. The second is what the word should be
stemmed to. For example, two lines in the exception file might look like: <br/><br/>
proceed proceed <br/>
proceeds proceed <br/><br/>
In the example above, the word proceed should be replaced by proceed (in other words, it remains
unchanged), instead of going through the Porter stemming algorithm. The word proceeds should be
shortened to proceed instead of being Porter stemmed. Any word that is not in the exception file should be
stemmed as in PA4.
