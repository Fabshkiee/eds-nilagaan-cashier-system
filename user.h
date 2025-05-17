#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    string username;
    string password;
    bool isAdmin;

    User();
    User(string username, string password, bool isAdmin);
};

// Function declarations
void saveUsers();
void loadUsers();
void addCashier();
void showAllCashiers();
void updateCashier();
void deleteCashier();
bool loginUser(string username, string password, User& currentUser);

// Encryption utilities
string encrypt(string str);
string decrypt(string str);

#endif // USER_H