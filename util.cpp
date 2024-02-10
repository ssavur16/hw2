#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <set>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  string input = rawWords;
  set<string> parsedWords;
  string word;
  string delimiters = " .',-&+\n";

  while(input.size() > 1) {
    size_t startIndex = input.find_first_not_of(delimiters);
    size_t delimIndex = input.substr(startIndex).find_first_of(delimiters);
    if(delimIndex != std::string::npos) {
      word = input.substr(startIndex, (delimIndex-startIndex));
      input = input.substr(delimIndex+1);
    }
    else { // last word of string
      word = input.substr(startIndex);
      input = "";
    }
    if(word.size() >= 2) {
      parsedWords.insert(convToLower(word));
    }
  }

  return parsedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
