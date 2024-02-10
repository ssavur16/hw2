#ifndef CART_H
#define CART_H
#include <vector>

struct Cart {
  public:
    void push_back(Product* prod) { cart_.push_back(prod); }
    int getSize() { return cart_.size(); }
    std::vector<Product*> cart_;
};

#endif