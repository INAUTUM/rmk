#include "../include/shift.h"
#include <iostream>

using namespace std;

void Shift::open(const string& cashier, double initial) {
    cashierName = cashier;
    initialCash = initial;
    openStatus = true;
}

void Shift::close() {
    openStatus = false;
    printShiftReport();
}

bool Shift::isOpen() const { return openStatus; }

void Shift::addReceipt(double amount, const string& paymentType) {
    if (paymentType == "cash") totalCash += amount;
    else if (paymentType == "card") totalCard += amount;
}

void Shift::printShiftReport() const {
    cout << "Отчет по смене:" << endl;
    cout << "Кассир: " << cashierName << endl;
    cout << "Начальная сумма: " << initialCash << endl;
    cout << "Продажи наличными: " << totalCash << endl;
    cout << "Продажи картой: " << totalCard << endl;
    cout << "Итоговая наличность: " << initialCash + totalCash << endl;
}