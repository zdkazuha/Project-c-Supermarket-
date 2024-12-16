#include <iostream>
#include <fstream>
#include <Windows.h>
#include <exception>
#include <string>
#include "Supermarket.h"

using namespace std;

static const string fname = "Supermarket.txt";

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    Supermarket supermarket;

    while (true) {
        cout << "\t [1] - Додати продукт або товар; \n\t [2] - Перегляд продуктів (товарів), впорядкованих по категоріях; \n\t [3] - Пошук певного товару (продукту) з видачею інформації про товар (продукт); \n\t [4] - Видалення певного товару (продукту) з бази; \n\t [5] - Продаж товару (з видачею чеку); \n\t [6] - Збереження бази товарів (у файл); \n\t [7] - Завантаження бази товарів з файлу; \n\t [0] - Вихід; \n\t\t Enter :: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "\tПрограма завершила свою роботу!!!";
            break;
        }

        switch (choice) {
        case 1: {
            string name, category;
            int price = 0, quantity = 0, n;
            TOC data{};

            cout << "\n\t [1] - Додати продукт; \n\t [2] - Додати товар \n\t\t Enter :: ";
            cin >> n;
            cin.ignore();

            if (n == 1) {
                cout << "\t Введіть дані: " << endl;
                cout << "\t Введіть назву товару :: ";
                getline(cin, name);
                cout << "\t Введіть категорію товару :: ";
                getline(cin, category);
                cout << "\t Введіть через пробіл: дату споживання (день місяць рік) :: ";
                cin >> data.day >> data.month >> data.year;
                cout << "\t Введіть ціну :: ";
                cin >> price;

                if (price <= 0) {
                    cout << "Помилка: Ціна повинна бути додатною!" << endl;
                    break;
                }

                cout << "\t Введіть кількість :: ";
                cin >> quantity;


                try {
                    supermarket.addGoods(new Product(name.c_str(), data, category.c_str(), price, quantity));
                    cout << "\t Продукт додано успішно!" << endl;
                }
                catch (const invalid_argument& ex) {
                    cout << "\t Помилка: " << ex.what() << endl;
                }
            }
            else if (n == 2) {
                cout << "\t Введіть назву товару :: ";
                getline(cin, name);
                cout << "\t Введіть категорію товару :: ";
                getline(cin, category);
                cout << "\t Введіть ціну :: ";
                cin >> price;

                if (price <= 0) {
                    cout << "Помилка: Ціна повинна бути додатною!" << endl;
                    break;
                }

                cout << "\t Введіть кількість :: ";
                cin >> quantity;

                try {
                    supermarket.addGoods(new Product(name.c_str(), data, category.c_str(), price, quantity));
                    cout << "\t Товар додано успішно!" << endl;
                }
                catch (const invalid_argument& ex) {
                    cout << "\t Помилка: " << ex.what() << endl;
                }
            }
            else {
                cout << "\t Помилка: Невірна опція!" << endl;
            }
            break;
        }
        case 2:
            supermarket.printSortByCategory();
            break;

        case 3: {
            string name;
            cout << "\t Введіть назву продукту (товару), який хочете знайти \n\t\t Enter :: ";
            getline(cin, name);

            try {
                supermarket.search(name.c_str());
            }
            catch (const invalid_argument& ex) {
                cout << "\t Помилка: " << ex.what() << endl;
            }
            break;
        }
        case 4: {
            string name;
            cout << "\t Введіть назву продукту (товару), який хочете видалити \n\t\t Enter :: ";
            getline(cin, name);

            try {
                supermarket.delete_(name.c_str());
            }
            catch (const invalid_argument& ex) {
                cout << "\t Помилка: " << ex.what() << endl;
            }
            break;
        }
        case 5: {
            string name;
            int n = 0;
            cout << "\t Введіть назву продукту та кількість (товару), які хочете продати через пробел\n\t\t Enter :: ";
            cin >> name >> n;

            try {
                supermarket.selling(name.c_str(), n);
            }
            catch (const invalid_argument& ex) {
                cout << "\t Помилка: " << ex.what() << endl;
            }
            break;
        }
        case 6: {
            ofstream file(fname, ios::binary);
            if (!file) {
                cout << "\t Не вдалося відкрити файл для збереження!" << endl;
                break;
            }
            supermarket.save(file);
            file.close();
            cout << "\t Базу збережено успішно!" << endl;
            break;
        }
        case 7: {
            ifstream file(fname, ios::binary);
            if (!file) {
                cout << "\t Не вдалося відкрити файл для завантаження!" << endl;
                break;
            }
            supermarket.download(file);
            file.close();
            cout << "\t Базу завантажено успішно!" << endl;
            break;
        }
        default:
            cout << "\t Помилка: Невірний вибір! Спробуйте ще раз." << endl;
            break;
        }
    }
}