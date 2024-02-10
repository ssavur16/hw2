#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    ~Clothing();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

  private:
    std::string size_;
    std::string brand_;
};

#endif