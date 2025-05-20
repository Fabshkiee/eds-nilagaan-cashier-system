#include <iostream>
#include <string>
#include "user.h"
#include "food_item.h"
#include "admin.h"
#include "clearSystem.h"
#include "cashier.h"
using namespace std;

//for arrays
const int MAX_USERS = 50;
const int MAX_MENU_ITEMS = 100;

// Global variables
User* users = new User[MAX_USERS];
FoodItem* menu = new FoodItem[MAX_MENU_ITEMS];
string lastCashierUsername;

int userCount = 0;
int menuCount = 0;

// Initialize system data
void initializeSystem() {
    loadUsers(); 
    loadMenu(); 
}

// Display welcome screen
void displayWelcome() {
    cout << "\033[1;33m===============================================================================\n";
    cout << "_____ _____  _ ____    ____   ___  ____    ______   ______ _____ ________  ___             \n"; 
    cout << "| ____|  _  ( ) ___|  |  _ \\ / _ \\\\ ___|  / ___\\\\ \\ / / ___|_   _| ____| \\/  |\n";
    cout << "|  _| | | | |/\\___ \\  | |_) | | | \\\\___ \\  \\\\___ \\\\ V /\\___ \\ | | | __| |\\/| |\n";
    cout << "| |___| |_| |  ___) | |  __/| |_| |___) |  ___) || |  ___) || | | |___| |  | |\n";
    cout << "|_____|____/  |____/  |_|    \\___/|____/  |____/ |_| |____/ |_| |_____|_|  |_|\n";
    cout << "===============================================================================\033[0m\n";
    cout << "                               \033[97m(  )   (   )  )\033[0m\n";
    cout << "                                \033[97m) (   )  (  (\033[0m\n"; 
    cout << "                               \033[97m( )  (    ) )\033[0m\n";
    cout << "                               \033[36m_____________\033[0m\n";
    cout << "                               \033[36m<_____________> ___\033[0m\n";
    cout << "                               \033[36m|             |/ _ \\\033[0m\n";
    cout << "                               \033[36m|               | | |\033[0m\n";
    cout << "                               \033[36m|               |_| |\033[0m\n";
    cout << "                            \033[36m___|             |\\___/\033[0m\n";
    cout << "                           \033[36m/    \\___________/    \\\033[0m\n";
    cout << "                           \033[36m\\_____________________/\033[0m\n";

    cout << "\n";
    cout << "                           \033[32mLinaga para sa Maayong Aga\033[0m\n";
    cout << "                             \033[32mLOG IN YOUR INFO BELOW!\033[0m\n";
    cout << "\n";
    cout << "                        input \033[91m'exit'\033[0m to quit the program\n";
    cout << "\033[1;33m===============================================================================\033[0m\n";
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
        clearSystem();
        displayWelcome();

        // Login process
        string username, password;
        User currentUser;

        cout << "\033[36mUsername:\033[0m ";
        cin >> username;
            if (username == "exit"){
                clearSystem();
                cout << "\033[91mExiting the Cashier Program...\033[0m\n";
                cout << "\033[92mThank you for using Ed's Nilaga-an POS System!\033[0m\n";
                cleanupMemory();
                return 0;
            }
        cout << "\033[36mPassword:\033[0m ";
        cin >> password;

        if (loginUser(username, password, currentUser)) {
            clearSystem();
            cout << "\n\033[92mLogin successful! Welcome, " << username << "!\033[0m\n";

            if (currentUser.isAdmin) {
                clearSystem();
                adminMenu(); 
            } else {
                clearSystem();
                lastCashierUsername = username;
                cashierMenu();
            }
        } else {
            clearSystem();
            cout << "\033[91mInvalid username or password!\033[0m\n";
        }
    }

    cleanupMemory();
    return 0;
}
