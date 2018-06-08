On top of dividing strings by whitespace, divide strings by punctuation.
"document!" (excluding quotation marks) results in "document" and "!".

• Consecutive punctation strings (e.g: "...?!") are grouped together. <br/>
• Apostrophes do not break words. For the purposes of this assignment, apostrophes should
be treated as alphanumeric characters. For example, can’t and program’s are single
words.<br/>
• A comma is not a punctuation mark if it occurs between two digits. For example, 20,000
should be considered a single word.<br/>
• A period does not break a string if it occurs both (1) before a digit and (2) after a digit or
a space. 2.0 is a single string; so is .01<br/>

Capitalization:
If the first letter in a word is uncapitalized, nothing is changed (e.g. it remains
uncapitalized). If the first letter of a word is capitalized and it is not the first word in a sentence,
then again nothing is changed (e.g. it remains capitalized). If a word is an acronym, its
capitalization is not changed. If a word contains a least one digit (e.g. Windows10 or iPhone8) it
remains unchanged. However, if a word is capitalized, is not an acronym, does not contain a digit,
and is the first word in a sentence, then we don’t know (yet) whether it should remain capitalized,
so we mark it as ambiguous by prepending a + sign. For example, the word For at the beginning
of this sentence should be marked by changing it to +For. In the worst case, this means that your
output could contain three separate counts for Herb, +Herb, and herb. (Note that ambiguous
capitals must be marked after dividing the strings by punctuation, otherwise the + would be
stripped off the word again.)
