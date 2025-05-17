#include "admin.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


// Manage menu items
void manageMenu() {
    int choice;
    
    while (true) {
        cout << "\n==== Menu Management ====\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Back to Admin Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                addFoodItem();
                break;
            case 3:
                updateFoodItem();
                break;
            case 4:
                deleteFoodItem();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Manage cashier accounts
void manageUsers() {
    int choice;
    
    while (true) {
        cout << "\n==== Cashier Management ====\n";
        cout << "1. View All Cashiers\n";
        cout << "2. Add Cashier\n";
        cout << "3. Update Cashier\n";
        cout << "4. Delete Cashier\n";
        cout << "5. Back to Admin Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                showAllCashiers();
                break;
            case 2:
                addCashier();
                break;
            case 3:
                updateCashier();
                break;
            case 4:
                deleteCashier();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}


// Display and handle the admin menu
void adminMenu() {
    int choice;
    
    while (true) {
        cout << "\n==== Admin Menu ====\n";
        cout << "1. Manage Menu\n";
        cout << "2. Manage Cashiers\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                manageMenu();
                break;
            case 2:
                manageUsers();
                break;
            case 3:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

