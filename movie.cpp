#include <sstream>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
  Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie()
{

}

// returns the appropriate keywords to index the product
std::set<std::string> Movie::keywords() const
{
  std::set<std::string> words;
  std::set<std::string> name_words = parseStringToWords(name_);
  std::set<std::string> genre_words = parseStringToWords(genre_);

  words.insert(name_words.begin(), name_words.end());
  words.insert(genre_words.begin(), genre_words.end());

  return words;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
  std::set<std::string> inputTerms(searchTerms.begin(), searchTerms.end());
  std::set<std::string> words = keywords();
  std::set<std::string> matches = setIntersection(inputTerms, words);

  if(!matches.empty()) { return true; }
  else { return false; }
}


// returns a string to display the product info for hits of the search
std::string Movie::displayString() const
{
  std::string display;
  display += name_ + "\n";
  display += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
  
  // convert price_ to 2 decimal places
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << price_;
  display += ss.str();
  
  display += " " + to_string(qty_) + " left.";
  return display;
}


// outputs the database format of the product info
void Movie::dump(std::ostream& os) const {
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}