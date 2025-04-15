#include "../include/product_db.h"
#include <fstream>
#include <sstream>

using namespace std;

bool ProductDatabase::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, barcode;
        double price;
        if (getline(iss, name, ',') && getline(iss, barcode, ',') && (iss >> price)) {
            products.emplace_back(name, barcode, price);
        }
    }
    return true;
}

Product* ProductDatabase::findProductByBarcode(const string& barcode) {
    for (auto& product : products) {
        if (product.getBarcode() == barcode) return &product;
    }
    return nullptr;
}

Product* ProductDatabase::findProductByName(const string& name) {
    for (auto& product : products) {
        if (product.getName() == name) return &product;
    }
    return nullptr;
}