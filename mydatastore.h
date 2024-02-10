#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"
#include "cart.h"

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    
    // member functions corresponding to menu commands
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::string username, Product* prod);
    void printCart(std::string username);
    void buyCart(std::string username);

  private:
    std::vector<Product*> products_;
    std::map<User*,Cart*> users_;
};

/* 
*
*   additional member functions corresponding to menu commands:
*   VIEWCART username BUYCART username
*   ADD username search_hit_number
*
*/

#endif