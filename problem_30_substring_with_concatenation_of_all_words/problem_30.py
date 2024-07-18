"""
You are given a string s and an array of strings words. All the strings of 
words are of the same length.

A concatenated string is a string that exactly contains all the strings of any 
permutation of words concatenated.

For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", 
"cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not
 a concatenated string because it is not the concatenation of any permutation 
 of words.
Return an array of the starting indices of all the concatenated substrings in 
s. You can return the answer in any order.

 

Example 1:
Input: s = "barfoothefoobarman", words = ["foo","bar"]

Output: [0,9]

Explanation:

The substring starting at 0 is "barfoo". 
It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". 
It is the concatenation of ["foo","bar"] which is a permutation of words.

Example 2:
Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]

Output: []

Explanation:

There is no concatenated substring.

Example 3:
Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]

Output: [6,9,12]

Explanation:

The substring starting at 6 is "foobarthe".
It is the concatenation of ["foo","bar","the"].
The substring starting at 9 is "barthefoo".
It is the concatenation of ["bar","the","foo"].
The substring starting at 12 is "thefoobar".
It is the concatenation of ["the","foo","bar"].

 

Constraints:

1 <= s.length <= 104
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.
"""

import typing as tp
import collections


class Solution:
    
    def checkFromHere(self,
                      s: str,
                      from_idx: int,
                      k: int,
                      words: tp.List[str]) \
        -> bool:
        """
        Checks in s if the following subwords of length k are the items of 
        words (in whatever order).
        Args:
            s: the string of interest.
            from_idx: the index (0-based) at which to start searching in s.
            k: the lenght of the subwords
            words: the set of subwords, they must have length k.
        """

        l = len(s)
        n_words = len(words)
        # nb of occurence to find left for each word
        counter = collections.Counter(words)
        n_found = 0

        for start in range(from_idx, l-k+1, k):
            end = start + k
            word = s[start:end]
            # print(f"[{start} {end}) -- {word}")
            # print(counter)
            # not found yet
            if counter[word] > 0:
                counter[word] -= 1
                n_found += 1
                if n_found == n_words:
                    return True
            # it is either already found or not part of words
            else:
                return False
            

    def findSubstring(self,
                      s: str, 
                      words: tp.List[str]) \
        -> tp.List[int]:
        """
        """
        l = len(s)
        k = len(words[0])
        n_words = len(words)

        results = list()

        for i in range(0, l-k+1):
            print(f"i -- {i}")
            if (self.checkFromHere(s, i, k, words)):
                # print(f"match")
                results.append(i)
        return results


if __name__ == "__main__":

    s = Solution()
    # print(s.findSubstring("abcdef", ["abc","def"]))
    assert(s.findSubstring("barfoothefoobarman", ["foo","bar"]) == [0,9])
    assert(s.findSubstring("wordgoodgoodgoodbestword", ["word","good","best","word"]) == [])
    assert(s.findSubstring("wordgoodgoodgoodbestword", ["word","good","best"]) == [12])
    assert(s.findSubstring("barfoofoobarthefoobarman", ["bar","foo","the"]) == [6,9,12])
    # assert(s.findSubstring() == )
    # assert(s.findSubstring() == )
