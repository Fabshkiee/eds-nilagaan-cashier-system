#include "food_item.h"
#include "clearSystem.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

string dataPath(const string &filename);

const int MAX_MENU_ITEMS = 100;

extern FoodItem *menu;
extern int menuCount;

// Constructor
FoodItem::FoodItem() {
  category = 0;
  code = "";
  name = "";
  price = 0.0;
}

FoodItem::FoodItem(int category, string code, string name, double price) {
  this->category = category;
  this->code = code;
  this->name = name;
  this->price = price;
}

string categoryToString(int category) { // para ma convert to string when input
  switch (category) {
  case 1:
    return "Meals";
  case 2:
    return "Drinks";
  case 3:
    return "Extras";
  default:
    return "Unknown";
  }
}

// Save menu to file
void saveMenu() {
  ofstream file(dataPath("menu.csv"));
  for (int i = 0; i < menuCount; i++) {
    file << categoryToString(menu[i].category) << ";" << menu[i].code << ";"
         << menu[i].name << ";" << fixed << setprecision(2) << menu[i].price
         << "\n";
  }
  file.close();
}

// Load menu from file
void loadMenu() {
  ifstream file(dataPath("menu.csv"));
  string line;
  menuCount = 0;
  while (getline(file, line) && menuCount < MAX_MENU_ITEMS) {
    size_t pos1 = line.find(';');
    size_t pos2 = line.find(';', pos1 + 1);
    size_t pos3 = line.find(';', pos2 + 1);
    if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
      continue; // skips invalid
    string catStr = line.substr(0, pos1);
    if (catStr == "Meals")
      menu[menuCount].category = 1;
    else if (catStr == "Drinks")
      menu[menuCount].category = 2;
    else if (catStr == "Extras")
      menu[menuCount].category = 3;
    else
      menu[menuCount].category = 0;
    menu[menuCount].code = line.substr(pos1 + 1, pos2 - pos1 - 1);
    menu[menuCount].name = line.substr(pos2 + 1, pos3 - pos2 - 1);
    menu[menuCount].price = stod(line.substr(pos3 + 1));
    menuCount++;
  }
  file.close();
}

// Add a new food item
void addFoodItem() {
  if (menuCount >= MAX_MENU_ITEMS) {
    cout << "Menu is full!\n";
    return;
  }

  int category;
  string code, name;
  double price;

  cout << "Enter category (1=Meals, 2=Drinks, 3=Extras or type 'exit' to "
          "cancel): ";
  string catInput;
  cin >> catInput;

  if (catInput == "exit") {
    clearSystem();
    return;
  }

  try {
    category = stoi(catInput);
  } catch (...) {
    clearSystem();
    cout << "Invalid input. Returning to menu management.\n";
    return;
  }

  cout << "Enter code (e.g., D01): ";
  cin >> code;
  cin.ignore();
  cout << "Enter name: ";
  getline(cin, name);
  cout << "Enter price: ";
  string priceInput;
  cin >> priceInput;
  try {
    price = stod(priceInput);
  } catch (...) {
    clearSystem();
    cout << "Invalid price. Returning to menu management.\n";
    return;
  }
  while (price <= 0) {
    cout << "Price must be greater than 0. Enter again: ";
    cin >> priceInput;
    try {
      price = stod(priceInput);
    } catch (...) {
      clearSystem();
      cout << "Invalid price. Returning to menu management.\n";
      return;
    }
  }

  menu[menuCount++] = FoodItem(category, code, name, price);
  saveMenu();
  cout << "Item added successfully!\n";
}

// Display the menu
void displayMenu() {
  cout << "\n--- Current Menu ---\n";
  cout << left << setw(10) << "Category" << setw(10) << "Code" << setw(30)
       << "Name" << right << setw(10) << "Price" << endl;
  cout << "--------------------------------------------------------------------"
          "------\n";
  string categories[] = {"Meals", "Drinks", "Extras"};
  for (int c = 0; c < 3; c++) {
    bool printed = false;
    for (int i = 0; i < menuCount; i++) {
      if (categoryToString(menu[i].category) == categories[c]) {
        cout << left << setw(10) << categories[c] << setw(10) << menu[i].code
             << setw(30) << menu[i].name << right << setw(7) << fixed
             << setprecision(2) << "PHP" << menu[i].price << endl;
        printed = true;
      }
    }
    if (printed)
      cout << endl; // Add a blank line after each category
  }
  if (menuCount == 0) {
    cout << "No items in the menu.\n";
  }
}

// Update a food item
void updateFoodItem() {
  displayMenu();
  if (menuCount == 0)
    return;
  string code;
  cout << "Enter code of item to update (or type 'exit' to cancel): ";
  cin >> code;
  if (code == "exit") {
    clearSystem();
    cout << "Returning to menu management.\n";
    return;
  }
  for (int i = 0; i < menuCount; i++) {
    if (menu[i].code == code) {
      int category;
      string name;
      double price;
      cout << "Enter new category (1= Drinks, 2= Meals, 3= Extras, 0 to keep current): ";
      string catInput;
      cin >> catInput;
      try {
        category = stoi(catInput);
      } catch (...) {
        category = 0;
      }
      if (category != 0)
        menu[i].category = category;
      cin.ignore();
      cout << "Enter new name (or 0 to keep current): ";
      getline(cin, name);
      if (name != "0")
        menu[i].name = name;
      cout << "Enter new price (or 0 to keep current): ";
      string priceInput;
      cin >> priceInput;
      try {
        price = stod(priceInput);
      } catch (...) {
        price = 0;
      }
      if (price > 0)
        menu[i].price = price;
      saveMenu();
      cout << "Item updated successfully!\n";
      return;
    }
  }
  cout << "Item not found!\n";
}

// Delete a food item
void deleteFoodItem() {
  displayMenu();
  if (menuCount == 0)
    return;
  string code;
  cout << "Enter code of item to delete (or type 'exit' to cancel): ";
  cin >> code;
  if (code == "exit") {
    clearSystem();
    cout << "Returning to menu management.\n";
    return;
  }
  for (int i = 0; i < menuCount; i++) {
    if (menu[i].code == code) {
      char confirm;
      cout << "Are you sure you want to delete this item? (y/n): ";
      cin >> confirm;
      if (confirm == 'y' || confirm == 'Y') {
        for (int j = i; j < menuCount - 1; j++) {
          menu[j] = menu[j + 1];
        }
        menuCount--;
        saveMenu();
        cout << "Item deleted successfully!\n";
      }
      return;
    }
  }
  cout << "Item not found!\n";
}
