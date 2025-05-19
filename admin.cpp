#include "admin.h"
#include "clearSystem.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


// Manage menu items
void manageMenu() {
    int choice;
    while (true) {
        cout << "\n\033[1;33m==== [ MENU MANAGEMENT ] ====\033[0m\n";
        cout << "\033[36m1. View Menu\033[0m\n";
        cout << "\033[36m2. Add Item\033[0m\n";
        cout << "\033[36m3. Update Item\033[0m\n";
        cout << "\033[36m4. Delete Item\033[0m\n";
        cout << "\033[91m5. Back to Admin Menu\033[0m\n";
        cout << "\033[1;33m------------------------------\033[0m\n";
        cout << "\033[36mEnter your choice:\033[0m ";
        string input;
        cin >> input;
        try {
            choice = stoi(input);
        } catch (...) {
            clearSystem();
            cout << "\033[91mInvalid input! Please enter a number.\033[0m\n";
            continue;
        }
        switch (choice) {
            case 1:
                clearSystem();
                displayMenu();
                break;
            case 2:
                clearSystem();
                addFoodItem();
                break;
            case 3:
                clearSystem();
                updateFoodItem();
                break;
            case 4:
                clearSystem();
                deleteFoodItem();
                break;
            case 5:
                clearSystem();
                cout << "\033[92mReturning to admin menu...\033[0m\n";
                return;
            default:
                clearSystem();
                cout << "\033[91mInvalid choice! Please try again.\033[0m\n";
        }
    }
}

// Manage cashier accounts
void manageUsers() {
    int choice;
    while (true) {
        cout << "\n\033[1;33m==== [ CASHIER MANAGEMENT ] ====\033[0m\n";
        cout << "\033[36m1. View All Cashiers\033[0m\n";
        cout << "\033[36m2. Add Cashier\033[0m\n";
        cout << "\033[36m3. Update Cashier\033[0m\n";
        cout << "\033[36m4. Delete Cashier\033[0m\n";
        cout << "\033[91m5. Back to Admin Menu\033[0m\n";
        cout << "\033[1;33m------------------------------\033[0m\n";
        cout << "\033[36mEnter your choice:\033[0m ";
        string input;
        cin >> input;
        try {
            choice = stoi(input);
        } catch (...) {
            clearSystem();
            cout << "\033[91mInvalid input! Please enter a number.\033[0m\n";
            continue;
        }
        switch (choice) {
            case 1:
                clearSystem();
                showAllCashiers();
                break;
            case 2:
                clearSystem();
                addCashier();
                break;
            case 3:
                clearSystem();
                updateCashier();
                break;
            case 4:
                clearSystem();
                deleteCashier();
                break;
            case 5:
                clearSystem();
                cout << "\033[92mReturning to admin menu...\033[0m\n";
                return;
            default:
                clearSystem();
                cout << "\033[91mInvalid choice! Please try again.\033[0m\n";
        }
    }
}

// Display and handle the admin menu
void adminMenu() {
    int choice;
    while (true) {
        cout << "\n\033[1;33m==== [ ADMIN MENU ] ====\033[0m\n";
        cout << "\033[36m1. Manage Menu\033[0m\n";
        cout << "\033[36m2. Manage Cashiers\033[0m\n";
        cout << "\033[91m3. Logout\033[0m\n";
        cout << "\033[1;33m------------------------------\033[0m\n";
        cout << "\033[36mEnter your choice:\033[0m ";
        string input;
        cin >> input;
        try {
            choice = stoi(input);
        } catch (...) {
            clearSystem();
            cout << "\033[91mInvalid input! Please enter a number.\033[0m\n";
            continue;
        }
        switch (choice) {
            case 1:
                clearSystem();
                manageMenu();
                break;
            case 2:
                clearSystem();
                manageUsers();
                break;
            case 3:
                clearSystem();
                cout << "\033[92mLogging out...\033[0m\n";
                return;
            default:
                clearSystem();
                cout << "\033[91mInvalid choice! Please try again.\033[0m\n";
        }
    }
}

