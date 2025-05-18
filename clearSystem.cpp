#include <iostream>
using namespace std;

void clearSystem() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}



