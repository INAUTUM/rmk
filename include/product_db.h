#ifndef PRODUCT_DB_H
#define PRODUCT_DB_H

#include <vector>
#include "product.h"

class ProductDatabase {
public:
    bool loadFromFile(const std::string& filename);
    Product* findProductByBarcode(const std::string& barcode);
    Product* findProductByName(const std::string& name);

private:
    std::vector<Product> products;
};

#endif