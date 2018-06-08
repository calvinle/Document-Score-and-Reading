Adding onto PA3, word strings are stemmed prior to being sorted and counted. <br/>

Punctuation strings are not changed. In addition, word strings that contains one or
more capital letters, one or more digits, or the ‘+’ marker are left unchanged, as are words with
two characters or less, like it or as. All other words are stemmed according to the Porter
Algorithm #2 word stemming algorithm. <br/>

Rules: <br/>
• A vowel is any of {‘a’, ‘e’, ‘i’, ‘o’, ‘u’} or the letter ‘y’ UNLESS the ‘y’ is the first letter
in a word or immediately follows a vowel. (Note that this is a recursive definition.)
Therefor the letter ‘y’ is considered a vowel in the word try but a consonant (non-vowel)
in the words yellow and today.<br/>
• A double is any of the following letter pairs: {‘bb’, ‘dd’, ‘ff’, ‘gg’, ‘mm’, ‘nn’, ‘pp’, ‘rr’,
‘tt’}.<br/>
• A valid li-ending is one of {‘c’, ‘d’, ‘e’, ‘g’, ‘h’, ‘k’, ‘m’, ‘n’, ‘r’, ‘t’}. <br/>
• Region1 is the substring that follows the first consonant (non-vowel) that follows a
vowel. Region1 may be empty (it often is for short words). Examples: Region1(try) is
empty, but Region1(definition) is inition. <br/>
• Region2 is the Region1 of Region1. In other words, Region2(definition) =
Region1(inition) = ition. <br/>
• The preceder is the part of a word before a given suffix. For example, if the suffix is ing
then the preceder of talking is talk. <br/>
• A string ends in a short syllable if either
1. It ends with a non-vowel followed by a vowel followed by a non-vowel that is
not one of {‘w’, ‘x’ or ‘y’} <br/>
2. The string is only two characters long, and is a vowel followed by a non-vowel
• A word is called short if both (1) it ends in a short syllable and (2) its Region1 is empty.
For example, bed, shed, and shred are short words, but bead, embed and beds are not. <br/>

If a word meets none of the criteria for Step N, it will be carried over to Step N+1.
