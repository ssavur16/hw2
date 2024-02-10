#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  // return set of items contained in BOTH s1 and s2
  std::set<T> inter_set;
  typename std::set<T>::iterator it;

  // iterating through set + testing membership = O(nlogn)
  for(it = s1.begin(); it != s1.end(); ++it) {
    if(s2.find(*it) != s2.end()) { // found s1 item in s2
      inter_set.insert(*it);
    }
  }

  return inter_set;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  // return set of all items contained in EITHER s1 or s2
  std::set<T> union_set;
  typename std::set<T>::iterator it;

  // iterating through set 1, O(n) runtime
  for(it = s1.begin(); it != s1.end(); ++it) {
    union_set.insert(*it); // add all members of s1 to union_set
  }

  // iterating through + test membership of s2 = O(nlogn)
  for(it = s2.begin(); it != s2.end(); ++it) {
    if(union_set.find(*it) == union_set.end()) { // item is not already in union_set
      union_set.insert(*it);
    }
  }

  return union_set;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
