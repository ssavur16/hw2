#include <sstream>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : 
  Product(category, name, price, qty)
{
  isbn_ = isbn;
  author_ = author;
}

Book::~Book()
{

}


// returns the appropriate keywords to index the product
std::set<std::string> Book::keywords() const
{
  std::set<std::string> words;
  std::set<std::string> name_words = parseStringToWords(name_);
  std::set<std::string> author_words = parseStringToWords(author_);
  
  words.insert(isbn_);
  words.insert(name_words.begin(), name_words.end());
  words.insert(author_words.begin(), author_words.end());

  return words;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
  std::set<std::string> inputTerms(searchTerms.begin(), searchTerms.end());
  std::set<std::string> words = keywords();
  std::set<std::string> matches = setIntersection(inputTerms, words);

  if(!matches.empty()) { return true; }
  else { return false; }
}


// returns a string to display the product info for hits of the search
std::string Book::displayString() const
{
  std::string display;
  display += name_ + "\n";
  display += "Author: " + author_ + " ISBN: " + isbn_ + "\n";

  // convert price_ to 2 decimal places
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << price_;
  display += ss.str();
  
  display += " " + to_string(qty_) + " left.";
  return display;
}

// outputs the database format of the product info
void Book::dump(std::ostream& os) const {
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << isbn_ << endl;
  os << author_ << endl;
}