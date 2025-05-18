#include <iostream>
#include <string>
#include "user.h"
#include "food_item.h"
#include "admin.h"
#include "clearSystem.h"
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
    loadUsers(); 
    loadMenu(); 
}

// Display welcome screen
void displayWelcome() {
    cout << "=============================================\n";
    cout << "   Welcome to Ed's Nilaga-an Cashier System! \n";
    cout << "=============================================\n";
    cout << "\n";
    cout << "      Ready for another flavorful day?\n";
    cout << "            LOG IN NADA MANGO!\n\n\n";
    cout << "       input 'exit' to quit the program      \n";     
    cout << "=============================================\n";
}

// Clean up dynamically allocated memory
void cleanupMemory() {
    delete[] users;
    delete[] menu;
}




int main() {
    // load the csv files
    initializeSystem();
    
    while (true) {
        displayWelcome();

        // Login process
        string username, password;
        User currentUser;

        cout << "Username: ";
        cin >> username;
            if (username == "exit"){
                cout << "Exiting the Cashier Program...\n";
                cout << "Thank you for using Ed's Nilaga-an Cashier System!\n";
                return 0;
            }
        cout << "Password: ";
        cin >> password;

        if (loginUser(username, password, currentUser)) {
            clearSystem();
            cout << "\nLogin successful! Welcome, " << username << "!\n";

            if (currentUser.isAdmin) {
                clearSystem();
                adminMenu(); 
            } else {
                // cashier menu nadi kamo nadi bahala
            }
        } else {
            cout << "Invalid username or password!\n";
        }
    }

    cleanupMemory();
    return 0;
}
