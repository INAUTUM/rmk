#include <iostream>
#include <sstream>
#include <string>
#include "../include/product_db.h"
#include "../include/shift.h"
#include "../include/receipt.h"

using namespace std;

ProductDatabase productDB;
Shift shift;
Receipt currentReceipt;

void printHelp() {
    cout << "Доступные команды:\n"
         << "open_shift <имя> <начальная сумма>\n"
         << "close_shift\n"
         << "add_product <штрих-код/название> <количество>\n"
         << "close_receipt <cash/card> [сумма]\n"
         << "exit\n";
}

void processCommand(const string& commandLine) {
    istringstream iss(commandLine);
    string cmd;
    iss >> cmd;

    if (cmd == "open_shift") {
        string name;
        double cash;
        if (iss >> name >> cash) {
            shift.open(name, cash);
            cout << "Смена открыта\n";
        } else cerr << "Ошибка: неверные параметры\n";
    } else if (cmd == "close_shift") {
        shift.close();
    } else if (cmd == "add_product") {
        string id;
        int qty;
        if (iss >> id >> qty) {
            Product* product = productDB.findProductByBarcode(id);
            if (!product) product = productDB.findProductByName(id);
            if (product) {
                currentReceipt.addItem(*product, qty);
                cout << "Товар добавлен\n";
            } else cerr << "Товар не найден\n";
        } else cerr << "Ошибка: неверные параметры\n";
    } else if (cmd == "close_receipt") {
        string type;
        double amount;
        if (iss >> type) {
            double total = currentReceipt.calculateTotal();
            if (type == "cash") {
                if (!(iss >> amount)) {
                    cerr << "Укажите сумму\n";
                    return;
                }
            } else amount = total;

            double change;
            if (currentReceipt.close(type, amount, change)) {
                shift.addReceipt(total, type);
                cout << "Чек закрыт:\n";
                for (const auto& item : currentReceipt.getItems()) {
                    cout << item.first.getName() << " x" << item.second 
                         << " @ " << item.first.getPrice() << endl;
                }
                cout << "Итого: " << total << "\nОплата: " << type 
                     << "\nСдача: " << change << endl;
                currentReceipt = Receipt();
            } else cerr << "Ошибка закрытия чека\n";
        }
    } else if (cmd == "exit") exit(0);
    else cerr << "Неизвестная команда\n";
}

int main() {
    if (!productDB.loadFromFile("../data/products.csv")) {
        cerr << "Ошибка загрузки товаров\n";
        return 1;
    }

    string line;
    cout << "РМК запущен. Введите команду:\n";
    printHelp();
    while (getline(cin, line)) {
        processCommand(line);
    }
    return 0;
}