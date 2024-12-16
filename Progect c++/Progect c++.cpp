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
        cout << "\t [1] - ������ ������� ��� �����; \n\t [2] - �������� �������� (������), ������������� �� ���������; \n\t [3] - ����� ������� ������ (��������) � ������� ���������� ��� ����� (�������); \n\t [4] - ��������� ������� ������ (��������) � ����; \n\t [5] - ������ ������ (� ������� ����); \n\t [6] - ���������� ���� ������ (� ����); \n\t [7] - ������������ ���� ������ � �����; \n\t [0] - �����; \n\t\t Enter :: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "\t�������� ��������� ���� ������!!!";
            break;
        }

        switch (choice) {
        case 1: {
            string name, category;
            int price = 0, quantity = 0, n;
            TOC data{};

            cout << "\n\t [1] - ������ �������; \n\t [2] - ������ ����� \n\t\t Enter :: ";
            cin >> n;
            cin.ignore();

            if (n == 1) {
                cout << "\t ������ ���: " << endl;
                cout << "\t ������ ����� ������ :: ";
                getline(cin, name);
                cout << "\t ������ �������� ������ :: ";
                getline(cin, category);
                cout << "\t ������ ����� �����: ���� ���������� (���� ����� ��) :: ";
                cin >> data.day >> data.month >> data.year;
                cout << "\t ������ ���� :: ";
                cin >> price;

                if (price <= 0) {
                    cout << "�������: ֳ�� ������� ���� ��������!" << endl;
                    break;
                }

                cout << "\t ������ ������� :: ";
                cin >> quantity;


                try {
                    supermarket.addGoods(new Product(name.c_str(), data, category.c_str(), price, quantity));
                    cout << "\t ������� ������ ������!" << endl;
                }
                catch (const invalid_argument& ex) {
                    cout << "\t �������: " << ex.what() << endl;
                }
            }
            else if (n == 2) {
                cout << "\t ������ ����� ������ :: ";
                getline(cin, name);
                cout << "\t ������ �������� ������ :: ";
                getline(cin, category);
                cout << "\t ������ ���� :: ";
                cin >> price;

                if (price <= 0) {
                    cout << "�������: ֳ�� ������� ���� ��������!" << endl;
                    break;
                }

                cout << "\t ������ ������� :: ";
                cin >> quantity;

                try {
                    supermarket.addGoods(new Product(name.c_str(), data, category.c_str(), price, quantity));
                    cout << "\t ����� ������ ������!" << endl;
                }
                catch (const invalid_argument& ex) {
                    cout << "\t �������: " << ex.what() << endl;
                }
            }
            else {
                cout << "\t �������: ������ �����!" << endl;
            }
            break;
        }
        case 2:
            supermarket.printSortByCategory();
            break;

        case 3: {
            string name;
            cout << "\t ������ ����� �������� (������), ���� ������ ������ \n\t\t Enter :: ";
            getline(cin, name);

            try {
                supermarket.search(name.c_str());
            }
            catch (const invalid_argument& ex) {
                cout << "\t �������: " << ex.what() << endl;
            }
            break;
        }
        case 4: {
            string name;
            cout << "\t ������ ����� �������� (������), ���� ������ �������� \n\t\t Enter :: ";
            getline(cin, name);

            try {
                supermarket.delete_(name.c_str());
            }
            catch (const invalid_argument& ex) {
                cout << "\t �������: " << ex.what() << endl;
            }
            break;
        }
        case 5: {
            string name;
            int n = 0;
            cout << "\t ������ ����� �������� �� ������� (������), �� ������ ������� ����� ������\n\t\t Enter :: ";
            cin >> name >> n;

            try {
                supermarket.selling(name.c_str(), n);
            }
            catch (const invalid_argument& ex) {
                cout << "\t �������: " << ex.what() << endl;
            }
            break;
        }
        case 6: {
            ofstream file(fname, ios::binary);
            if (!file) {
                cout << "\t �� ������� ������� ���� ��� ����������!" << endl;
                break;
            }
            supermarket.save(file);
            file.close();
            cout << "\t ���� ��������� ������!" << endl;
            break;
        }
        case 7: {
            ifstream file(fname, ios::binary);
            if (!file) {
                cout << "\t �� ������� ������� ���� ��� ������������!" << endl;
                break;
            }
            supermarket.download(file);
            file.close();
            cout << "\t ���� ����������� ������!" << endl;
            break;
        }
        default:
            cout << "\t �������: ������� ����! ��������� �� ���." << endl;
            break;
        }
    }
}