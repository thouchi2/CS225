/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream wordsFile(filename);
    string w;
    if(wordsFile.is_open()){
        while(getline(wordsFile, w)){
            words.push_back(w);
        }
    }

    string word;
    for(size_t i = 0; i < words.size(); i++){
        word = words[i];
        std::sort(word.begin(), word.end());
        auto lookup = dict.find(word);
        if(lookup == dict.end()){
            dict.insert(std::pair<string, vector<string>>(word, vector<string>()));
            dict[word].push_back(words[i]);
        }
        else
            dict[word].push_back(words[i]);
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    string word;
    for(size_t i = 0; i < words.size(); i++){
        word = words[i];
        std::sort(word.begin(), word.end());
        auto lookup = dict.find(word);
        if(lookup == dict.end()){
            dict.insert(std::pair<string, vector<string>>(word, vector<string>()));
            dict[word].push_back(words[i]);
        }
        else
            dict[word].push_back(words[i]);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string w = word;
    vector<string> retVal;
    std::sort(w.begin(), w.end());
    for(auto & dictIt : dict){
        if(dictIt.first.compare(w) == 0){
            for(size_t i = 0; i < dictIt.second.size(); i++){
                retVal.push_back(dictIt.second.at(i));
            }
        }
    }
    return retVal;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> allVec;
    for(auto& dictIt : dict){
        if(dictIt.second.size() > 1)
            allVec.push_back(dictIt.second);
    }
    return allVec;
}
