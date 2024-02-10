#include <set>
#include <string>
#include "mydatastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
using namespace std;
/*
*
*   this derived class may define non-virtual functions to do other specific 
*   commands that the menu supports.
*
*/

MyDataStore::MyDataStore()
{

}


MyDataStore::~MyDataStore()
{
  // delete products_ data member
  for(size_t i = 0; i < products_.size(); ++i) {
    delete products_[i];
  }
  products_.clear();

  // delete users_ data member
  map<User*,Cart*>::iterator it;
  for(it = users_.begin(); it != users_.end(); ++it) {
    delete it->first;
    delete it->second;
  }
  users_.clear();
}


/**
  * Adds a product to the data store
  */
void MyDataStore::addProduct(Product* p) 
{
  products_.push_back(p);
}

/**
  * Adds a user to the data store
  */
void MyDataStore::addUser(User* u)
{
  Cart* u_cart = new Cart;
  users_.insert(make_pair(u, u_cart));
}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  vector<Product*> matches; // return vector

  // type 0 = AND search (intersection of results)
  if(type == 0) {
    set<string> terms_set(terms.begin(), terms.end());

    // iterate through vector of product pointers
    for(size_t i = 0; i < products_.size(); ++i) {
      set<string> product_keys = products_[i]->keywords();
      set<string> inter_set = setIntersection(terms_set, product_keys);

      if(terms_set.size() != 0) {
        // add product to output if every string in terms is in keywords()
        if(inter_set.size() == terms_set.size()) {
          matches.push_back(products_[i]);
        }
      }
    }
  }

  // type 1 = OR search (union of results)
  if(type == 1) {
    // iterate through vector of product pointers
    for(size_t i = 0; i < products_.size(); ++i) {
      // add product to output if any terms match product's keywords
      if(products_[i]->isMatch(terms)) {
        matches.push_back(products_[i]);
      }
    }
  }

  return matches;
}

/**
  * Reproduce the database file from the current Products and User values
  */
void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << endl;
  for(size_t i = 0; i < products_.size(); ++i) {
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  map<User*,Cart*>::iterator it;
  for(it = users_.begin(); it != users_.end(); ++it) {
    it->first->dump(ofile);
  }
  ofile << "</users>" << endl;
}

/* 
*   should cause the product with index search_hit_number
*   from the previous search result to be added to
*   username's cart. MUST MAINTAIN FIFO ORDER
*/
void MyDataStore::addCart(string username, Product* prod) 
{
  bool found = false;
  map<User*,Cart*>::iterator it;
  for(it = users_.begin(); it != users_.end(); ++it) {
    if(it->first->getName() == username) {
      found = true;
      it->second->push_back(prod);
    }
  }
  if(!found) {
    cout << "Invalid request" << endl;
    return;
  }
}

/*
*   should print products in username's cart with some
*   ascending index number to tell how many items in cart
*/
void MyDataStore::printCart(std::string username)
{
  bool found = false;
  map<User*,Cart*>::iterator it;
  for(it = users_.begin(); it != users_.end(); ++it) {
    if(it->first->getName() == username) {
      found = true;
      if(it->second->getSize() > 0) {
        int resultNo = 1;
        vector<Product*>::iterator it2;
        for(it2 = (it->second->cart_).begin(); it2 != (it->second->cart_).end(); ++it2) {
          cout << "Item " << resultNo << endl;
          cout << (*it2)->displayString() << endl;
          cout << endl;
          resultNo++;
        }
      }
    }
  }
  if(!found) { 
    cout << "Invalid username" << endl;
    return;
  }
}

/*
*   should cause program to iterate through items in
*   username's cart. if item is in stock AND user has enough
*   money: 1) item should be removed from cart, 2) in stock 
*   quantity should be reduced by 1, and 3) product price
*   should be debited from user's available credit
*
*   if item not in stock or user does not have enough credit,
*   simply leave item in cart and go on to next product
*/
void MyDataStore::buyCart(std::string username)
{
  bool found = false;
  map<User*,Cart*>::iterator it;
  for(it = users_.begin(); it != users_.end(); ++it) {
    if(it->first->getName() == username) {
      found = true;

      // iterate through items in username's cart
      vector<Product*>::iterator it2;
      for(it2 = (it->second->cart_).begin(); it2 != (it->second->cart_).end(); ++it2) {
        // check to see if can buy
        if((it->first->getBalance() >= (*it2)->getPrice()) && ((*it2)->getQty() > 0)) {
          (*it2)->subtractQty(1);
          it->first->deductAmount((*it2)->getPrice());
          *it2 = NULL;
        }
      }

      // remove purchased items from username's cart
      (it->second->cart_).erase(
        remove_if(
          (it->second->cart_).begin(), (it->second->cart_).end(), [&](Product* item) {
            return item == NULL;
          }), (it->second->cart_).end());
    }
  }
  if(!found) {
    cout << "Invalid username" << endl;
    return;
  }
}