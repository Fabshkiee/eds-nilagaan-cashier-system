#include "user.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_USERS = 50;

extern User* users;
extern int userCount;

// Constructor 
User::User() {
    username = "";
    password = "";
    isAdmin = false;
}

User::User(string uname, string pwd, bool admin) {
    username = uname;
    password = pwd;
    isAdmin = admin;
}

// caesar cipher for pass
string encrypt(string str) {
    for (char &c : str) c += 3;
    return str;
}

string decrypt(string str) {
    for (char &c : str) c -= 3;
    return str;
}

string dataPath(const string& filename);

// Save users to file
void saveUsers() {
    ofstream file(dataPath("employees.csv"));
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << ";"
             << users[i].password << ";"
             << (users[i].isAdmin ? "1" : "0") << "\n";
    }
    file.close();
}

// Load users from file
void loadUsers() {
    ifstream file(dataPath("employees.csv"));
    string line;
    userCount = 0;

    while (getline(file, line) && userCount < MAX_USERS) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        
        users[userCount].username = line.substr(0, pos1);
        users[userCount].password = line.substr(pos1 + 1, pos2 - pos1 - 1);
        users[userCount].isAdmin = (line.substr(pos2 + 1) == "1");
        userCount++;
    }
    file.close();

    if (userCount == 0) { // Create default accounts
        users[0] = User("admin", encrypt("admin"), true);
        users[1] = User("cashier", encrypt("cashier"), false);
        userCount = 2;
        saveUsers();
    }
}

// Add a new cashier account
void addCashier() {
    if (userCount >= MAX_USERS) {
        cout << "Maximum users reached!\n";
        return;
    }
    
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    
    // Check if username already exists
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "Username already exists!\n";
            return;
        }
    }
    
    cout << "Enter password: ";
    cin >> password;
    
    users[userCount++] = User(username, encrypt(password), false);
    saveUsers();
    cout << "Cashier added successfully!\n";
}

// Display all cashiers
void showAllCashiers() {
    cout << "\n--- All Cashiers ---\n";
    bool found = false;
    
    for (int i = 0; i < userCount; i++) {
        if (!users[i].isAdmin) {
            cout << i + 1 << ". Username: " << users[i].username << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No cashiers found.\n";
    }
}

// Update cashier information
void updateCashier() {
    showAllCashiers();
    
    string username;
    cout << "Enter username to update: ";
    cin >> username;
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && !users[i].isAdmin) {
            string newPassword;
            cout << "Enter new password (or enter '0' to keep current): ";
            cin >> newPassword;
            
            if (newPassword != "0") {
                users[i].password = encrypt(newPassword);
                cout << "Password updated successfully!\n";
            }
            
            saveUsers();
            return;
        }
    }
    
    cout << "Cashier not found!\n";
}

// Delete a cashier
void deleteCashier() {
    showAllCashiers();
    
    string username;
    cout << "Enter username to delete: ";
    cin >> username;
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && !users[i].isAdmin) {
            // Confirm deletion
            char confirm;
            cout << "Are you sure you want to delete this cashier? (y/n): ";
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                // Shift all elements after the deleted one
                for (int j = i; j < userCount - 1; j++) {
                    users[j] = users[j + 1];
                }
                userCount--;
                saveUsers();
                cout << "Cashier deleted successfully!\n";
            }
            return;
        }
    }
    
    cout << "Cashier not found!\n";
}

// Login validation
bool loginUser(string username, string password, User& currentUser) {
    string encrypted = encrypt(password);
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == encrypted) {
            currentUser = users[i];
            return true;
        }
    }
    
    return false;
}

string dataPath(const string& filename) {
    return "output/data/" + filename;
}