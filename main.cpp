#include <iostream>
#include <string>
#include "user.h"
#include "food_item.h"
#include "admin.h"
using namespace std;

//for arrays
const int MAX_USERS = 50;
const int MAX_MENU_ITEMS = 100;

// Global variables
User* users = new User[MAX_USERS];
FoodItem* menu = new FoodItem[MAX_MENU_ITEMS];

int userCount = 0;
int menuCount = 0;

// Initialize system data
void initializeSystem() {
    loadUsers(); // no arguments, uses global users
    loadMenu();  // no arguments, uses global menu
}

// Display welcome screen
void displayWelcome() {
    cout << "=============================================\n";
    cout << "   Welcome to Ed's Nilaga-an Cashier System! \n";
    cout << "=============================================\n";
    cout << "\n";
    cout << "      Ready for another flavorful day?\n";
    cout << "            LOG IN NADA MANGO!\n";
    cout << "\n";
    cout << "=============================================\n";
}

// Clean up dynamically allocated memory
void cleanupMemory() {
    delete[] users;
    delete[] menu;
}




int main() {
    // load the datas
    initializeSystem();
    
    displayWelcome();
    
    // Login process
    string username, password;
    User currentUser;
    
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    
    if (loginUser(username, password, currentUser)) {
        cout << "\nLogin successful! Welcome, " << username << "!\n";
        
        // Direct to appropriate menu based on user type
        if (currentUser.isAdmin) {
            adminMenu();
        } else {
            cout << "cashier";
        }
    } else {
        cout << "Invalid username or password!\n";
    }
    
    // Cleanup before exit
    cleanupMemory();
    
    return 0;
}
