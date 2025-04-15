#include "../include/receipt.h"
#include <string>

void Receipt::addItem(const Product& product, int quantity) {
    items.emplace_back(product, quantity);
}

double Receipt::calculateTotal() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.first.getPrice() * item.second;
    }
    return total;
}

bool Receipt::close(const std::string& paymentType, double paymentAmount, double& change) {
    if (isClosed) return false;
    double total = calculateTotal();
    
    if (paymentType == "cash") {
        if (paymentAmount < total) return false;
        change = paymentAmount - total;
    } else if (paymentType == "card") {
        if (paymentAmount != total) return false;
        change = 0;
    } else return false;

    this->paymentType = paymentType;
    this->paymentAmount = paymentAmount;
    this->change = change;
    isClosed = true;
    return true;
}

const std::vector<std::pair<Product, int>>& Receipt::getItems() const { return items; }
std::string Receipt::getPaymentType() const { return paymentType; }
double Receipt::getPaymentAmount() const { return paymentAmount; }
double Receipt::getChange() const { return change; }