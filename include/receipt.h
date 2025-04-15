#ifndef RECEIPT_H
#define RECEIPT_H

#include <vector>
#include <string>
#include "product.h"

class Receipt {
public:
    void addItem(const Product& product, int quantity);
    double calculateTotal() const;
    bool close(const std::string& paymentType, double paymentAmount, double& change); // Явное указание std::

    const std::vector<std::pair<Product, int>>& getItems() const;
    std::string getPaymentType() const;
    double getPaymentAmount() const;
    double getChange() const;

private:
    std::vector<std::pair<Product, int>> items;
    std::string paymentType;
    double paymentAmount = 0;
    double change = 0;
    bool isClosed = false;
};

#endif