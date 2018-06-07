/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<StringTriple> retVal;
    vector<string> vecWords;
    ifstream words(word_list_fname);
    string w;
    if(words.is_open()){
        while(getline(words, w)){
            if(w.length() == 5)
                vecWords.push_back(w);
        }
    }
    for(auto & eachWord : vecWords){
        std::string first = eachWord.substr(1);
        std::string second;
        second.append(eachWord.begin(), eachWord.begin() + 1);
        second.append(first.begin() + 1, first.end());
        if(d.homophones(first, second) && d.homophones(eachWord, first) && d.homophones(eachWord, first)){
            StringTriple solution;
            std::get<0>(solution) = eachWord;
            std::get<1>(solution) = first;
            std::get<2>(solution) = second;
            retVal.push_back(solution);
        }
    }
    return retVal;
}
