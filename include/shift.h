#ifndef SHIFT_H
#define SHIFT_H

#include <string>

class Shift {
public:
    void open(const std::string& cashierName, double initialCash);
    void close();
    bool isOpen() const;
    void addReceipt(double amount, const std::string& paymentType);
    void printShiftReport() const;

private:
    std::string cashierName;
    double initialCash;
    double totalCash = 0;
    double totalCard = 0;
    bool openStatus = false;
};

#endif