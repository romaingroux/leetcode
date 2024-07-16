"""
Given an array of strings words and a width maxWidth, format the text such that 
each line has exactly maxWidth characters and is fully (left and right) 
justified.

You should pack your words in a greedy approach; that is, pack as many words as 
you can in each line. Pad extra spaces ' ' when necessary so that each line has 
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the 
number of spaces on a line does not divide evenly between words, the empty 
slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is 
inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters 
only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
 

Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", 
because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified because it contains only one 
word.
Example 3:

Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
 

Constraints:

1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth
"""

import typing as tp


class Solution:
    
    @staticmethod
    def getLine(words: tp.List[str], 
                start: int, 
                maxWidth: int) \
        -> int:
        """
        Finds the index of the last word in words such the summed length of 
        all words[stat:end) is at most maxWidth length.
        Args:
            words: a list of words.
            start: the index of the first item to consider in words.
            maxWidth: the total max allowed length of words[start:end)
        Returns:
            The past the last index of words.
        """
        # make it -1 because the last word in line will not have a space
        n = -1
        i = start
        while i<len(words):
            if (n + len(words[i]) + 1) <= maxWidth:
                # add +1 because word + space
                # last word should not have a space -> +1 and -1 will cancel 
                # each other out 
                n += len(words[i]) + 1
                # print(f"updated N {n}")
                i += 1
            else:
                break
        return i
    
    @staticmethod
    def justifyLine(words: tp.List[str],
                    maxWidth: int) \
        -> str:
        """
        Justifies a line with extra spaces such that the total length is 
        maxWidth.
        Args:
            words: a list containing the words of the line. The words must 
                have no space ! Space for word separation will be taken care of.
            maxWidth: the max line length.
        Returns:
            The justified line.
        """

        if len(words) == 1:
            return words[0] + " "*(maxWidth-len(words[0])) 

        # total number of words
        n_words = len(words)

        # number of words that can get extra spaces (last word cannot)
        n_words_to_just = n_words -1

        # there are len(words)-1 spaces between words to separate the words
        # this accounts for word separator space that would already be here w/o 
        # justification
        words_len = len(words)-1 + sum([len(word) for word in words]) 

        # total number of spaces to put
        n_spaces_tot = maxWidth - words_len
        # each word (but last one) will get at least this number of spaces
        n_spaces_all = n_spaces_tot // n_words_to_just
        # remaining spaces to spread among some words only
        n_spaces_left = n_spaces_tot - (n_words_to_just*n_spaces_all)

        # all words get some spaces
        for i in range(0, n_words_to_just):
            words[i] = words[i] + " "*n_spaces_all
        
        # only first words get of the left spaces each
        for i in range(0, n_spaces_left):
            words[i] = words[i] + " "

        return " ".join(words)

    @staticmethod
    def justifyLastLine(words: tp.List[str],
                        maxWidth: int) \
        -> str:
        """
        Justifies the last line, that is only the last word
        get extra spaces such that the total length is maxWidth.
        Args:
            words: a list containing the words of the line. The words must 
                have no space ! Space for word separation will be taken care of.
            maxWidth: the max line length.
        Returns:
            The justified line.
        """

        # total number of words
        n_words = len(words)

        # only last word to justify
        n_words_to_just = 1

        # there are len(words)-1 spaces between words to separate the words
        # this accounts for word separator space that would already be here w/o 
        # justification
        words_len = len(words)-1 + sum([len(word) for word in words]) 

        # total number of spaces to put
        n_spaces_tot = maxWidth - words_len

        words[-1] = words[-1] + " "*n_spaces_tot

        return " ".join(words)

    def fullJustify(self, 
                    words: tp.List[str], 
                    maxWidth: int) \
        -> tp.List[str]:
        word_justified = list()

        start = 0
        end = 0
        while end <= (len(words) - 1):
            end = self.getLine(words, start, maxWidth)
            # last line must be justified differently
            if end != len(words):
                word_justified.append(self.justifyLine(words[start:end], 
                                                       maxWidth))
            else:
                word_justified.append(self.justifyLastLine(words[start:end], 
                                                           maxWidth))
            start = end
        return word_justified
        

if __name__ == "__main__":
    s = Solution()

    words_1 = ["This", "is", "an", "example", "of", "text", "justification."]
    words_2 = ["What","must","be","acknowledgment","shall","be"]
    words_3 = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]

    words_1_j = s.fullJustify(words_1, 16)
    words_1_e = ["This    is    an", "example  of text", "justification.  "]
    assert(words_1_j == words_1_e)

    words_2_j = s.fullJustify(words_2, 16)
    words_2_e = ["What   must   be", "acknowledgment  ", "shall be        "]
    assert(words_2_j == words_2_e)

    words_3_j = s.fullJustify(words_3, 20)
    print(words_3_j)
    words_3_e = ["Science  is  what we",
                 "understand      well", 
                 "enough to explain to", 
                 "a  computer.  Art is", 
                 "everything  else  we", 
                 "do                  "]
    assert(words_3_j == words_3_e)