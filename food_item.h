#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

#include <string>
using namespace std;

class FoodItem {
public:
    int category;  // 1=Drinks, 2=Meals, 3=Extras
    string code;   // e.g., "D01"
    string name;
    double price;

    FoodItem();
    FoodItem(int category, string code, string name, double price);
};

// Function declarations for menu management
void saveMenu();
void loadMenu();
void addFoodItem();
void displayMenu();
void updateFoodItem();
void deleteFoodItem();
int getNextFoodId();

#endif // FOOD_ITEM_H