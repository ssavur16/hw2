#include <sstream>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
  Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing()
{

}


// returns the appropriate keywords to index the product
std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> words;
  std::set<std::string> name_words = parseStringToWords(name_);
  std::set<std::string> brand_words = parseStringToWords(brand_);

  words.insert(name_words.begin(), name_words.end());
  words.insert(brand_words.begin(), brand_words.end());

  return words;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
  std::set<std::string> inputTerms(searchTerms.begin(), searchTerms.end());
  std::set<std::string> words = keywords();
  std::set<std::string> matches = setIntersection(inputTerms, words);

  if(!matches.empty()) { return true; }
  else { return false; }
}


// returns a string to display the product info for hits of the search
std::string Clothing::displayString() const
{
  std::string display;
  display += name_ + "\n";
  display += "Size: " + size_ + " Brand: " + brand_ + "\n";

  // convert price_ to 2 decimal places
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << price_;
  display += ss.str();
  
  display += " " + to_string(qty_) + " left.";
  return display;
}


// outputs the database format of the product info
void Clothing::dump(std::ostream& os) const {
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_ << endl;
}