// CODED ALL BY NATHAN SARROSA
// CHANGES MADE BY RYUSKE:
// SAVE RECEIPT TO TXT FILE
// MADE THE SYSTEM DYNAMIC WITH THE MENU FROM FOOD_ITEM.CPP
// REMOVED void displayFoodMenu() because void displayMenu() is already in
// food_item.cpp
#include "cashier.h"
#include "clearSystem.h"
#include "food_item.h"
#include "user.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

extern FoodItem *menu;
extern int menuCount;
extern User *users;
extern int userCount;
extern string categoryToString(int category);

// Order variables
vector<int> quantities;
vector<int> orderItems;

double total = 0.0;
double payment = 0.0;
double change = 0.0;
bool hasDiscount = false;
const double DISCOUNT_RATE = 0.20; // 20% discount

void displayCenterMenu() {
  cout << "\n\033[1;33m==== [ CASHIER MENU ] ====\033[0m\n";
  cout << "\033[36m1. View Food Menu\033[0m\n";
  cout << "\033[36m2. Place Order\033[0m\n";
  cout << "\033[91m3. Exit\033[0m\n";
  cout << "\033[1;33m--------------------------\033[0m\n";
}

void takeCustomerOrder() {
  quantities.clear();
  orderItems.clear();
  total = 0.0;
  while (true) {
    clearSystem();
    displayMenu();
    // Show current order so far
    if (!orderItems.empty()) {
      cout << "\n\033[1;33mCurrent Order:\033[0m\n";
      for (size_t i = 0; i < orderItems.size(); i++) {
        int itemIndex = orderItems[i];
        cout << quantities[i] << " x " << menu[itemIndex].name << " - PHP"
             << fixed << setprecision(2)
             << menu[itemIndex].price * quantities[i] << "\n";
      }
      cout << "\033[1;33m-------------------------\033[0m\n";
      cout << "Subtotal: \033[32mPHP" << fixed << setprecision(2) << total
           << "\033[0m\n";
    }
    cout << '\n';
    cout << "\033[1;33m-------------------------------------------------------"
            "\033[0m\n"
         << "Enter the \033[1;4;36mITEM CODE\033[0m to order\n"
         << "Type '\033[91mexit\033[0m' to cancel\n"
         << "Type '\033[92m0\033[0m' to finish and checkout\n"
         << "\033[1;33m-------------------------------------------------------"
            "\033[0m\n";
    string codeInput;
    cin >> codeInput;
    if (codeInput == "exit") {
      cout << "\033[91mOrder cancelled. Returning to menu...\033[0m\n";
      quantities.clear();
      orderItems.clear();
      total = 0.0;
      cout << "Press \033[1;4;36menter\033[0m to continue...";
      cin.ignore();
      cin.get();
      clearSystem();
      return;
    }
    if (codeInput == "0") {
      clearSystem();
      break;
    }
    int foundIndex = -1;
    for (int i = 0; i < menuCount; i++) {
      if (menu[i].code == codeInput) {
        foundIndex = i;
        break;
      }
    }
    if (foundIndex != -1) {
      int quantity;
      cout << "\033[36mEnter quantity for \033[0m" << menu[foundIndex].name
           << ": ";
      string qtyInput;
      cin >> qtyInput;
      try {
        quantity = stoi(qtyInput);
      } catch (...) {
        cout << "\033[91mInvalid quantity. Please enter a valid "
                "number.\033[0m\n";
        continue;
      }
      if (quantity <= 0) {
        cout << "\033[91mQuantity must be greater than 0.\033[0m\n";
        continue;
      }
      orderItems.push_back(foundIndex);
      quantities.push_back(quantity);
      total += menu[foundIndex].price * quantity;
      cout << "\033[92mAdded " << quantity << " " << menu[foundIndex].name
           << "(s) to your order.\033[0m\n";
      cout << "Press \033[1;4;36menter\033[0m to continue...";
      cin.ignore();
      cin.get();
    } else {
      cout << "\033[91mInvalid code. Please try again.\033[0m\n";
      cout << "Press \033[1;4;36menter\033[0m to continue...";
      cin.ignore();
      cin.get();
    }
  }
}

void displayTotalOrder() {
  cout << "\n\033[1;33m===== YOUR ORDER =====\033[0m\n";
  for (size_t i = 0; i < orderItems.size(); i++) {
    int itemIndex = orderItems[i];
    cout << quantities[i] << " x " << menu[itemIndex].name << " - PHP" << fixed
         << setprecision(2) << menu[itemIndex].price * quantities[i] << "\n";
  }
  cout << "\033[1;33m======================\033[0m\n";
  cout << "TOTAL: \033[32mPHP" << fixed << setprecision(2) << total
       << "\033[0m\n";
}

bool askForDiscount() {
  while (true) {
    cout << "\n\033[36mDo you have a Senior/PWD card? (y/n): \033[0m";
    string response;
    cin >> response;
    if (response == "y" || response == "Y")
      return true;
    if (response == "n" || response == "N")
      return false;
    cout << "\033[91mPlease enter 'y' or 'n' only.\033[0m\n";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void applyDiscount(bool hasDiscount) {
  if (hasDiscount) {
    double discountAmount = total * DISCOUNT_RATE;
    cout << "Discount applied (20%): -\033[32mPHP" << fixed << setprecision(2)
         << discountAmount << "\033[0m\n";
    total -= discountAmount;
    cout << "NEW TOTAL: \033[32mPHP" << fixed << setprecision(2) << total
         << "\033[0m\n";
  }
}

void takeCustomerPayment() {
  while (true) {
    cout << "\nEnter payment amount: \033[32mPHP\033[0m";
    string paymentInput;
    cin >> paymentInput;
    try {
      payment = stod(paymentInput);
    } catch (...) {
      cout << "\033[91mInvalid payment. Please enter a valid number.\033[0m\n";
      continue;
    }
    if (payment < total) {
      cout << "\033[91mInsufficient payment. Please enter at least \033[32mPHP"
           << fixed << setprecision(2) << total << "\033[0m.\033[0m\n";
      continue;
    }
    break;
  }
}

void calculateChange() {
  change = payment - total;
  cout << "Change: \033[32mPHP" << fixed << setprecision(2) << change
       << "\033[0m\n";
  cout << "\nPress enter to see Receipt...";
  cin.ignore();
  cin.get();
  clearSystem();
}

void printReceipt(const string &username) {
  time_t now = time(0);
  tm *ltm = localtime(&now);

  // Generate receipt code string
  char receiptCode[20]; // inspired by user "Ganado" in CPP.com Forums tysm
  sprintf(receiptCode, "%04d%02d%02d_%02d%02d%02d", // date
          1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, // ltm = year and so on great way use of pointers ty nathsarr
          ltm->tm_hour, ltm->tm_min, ltm->tm_sec); // sprintf basically replaces those formats with the pointers

  char filename[100];
  sprintf(filename, "output/receipt/receipt_%s.txt",
          receiptCode); // sprintf function replace %s with receiptCode value
  ofstream receiptFile(filename);

  // Print to console
  cout << "\n===== RECEIPT =====\n";
  cout << "Receipt: " << receiptCode << "\n";
  cout << "Cashier: " << username << "\n";
  cout << "Date: " << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-"
       << ltm->tm_mday << "\n";
  cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec
       << "\n";
  cout << "------------------\n";
  for (size_t i = 0; i < orderItems.size(); i++) {
    int itemIndex = orderItems[i];
    cout << quantities[i] << " x " << menu[itemIndex].name << " - PHP" << fixed
         << setprecision(2) << menu[itemIndex].price * quantities[i] << "\n";
  }
  cout << "------------------\n";
  if (hasDiscount) {
    cout << "Subtotal: \033[32mPHP" << fixed << setprecision(2)
         << total / (1 - DISCOUNT_RATE) << "\033[0m\n";
    cout << "Discount (20%): -\033[32mPHP" << fixed << setprecision(2)
         << total * DISCOUNT_RATE / (1 - DISCOUNT_RATE) << "\033[0m\n";
  }
  cout << "TOTAL: \033[32mPHP" << fixed << setprecision(2) << total
       << "\033[0m\n";
  cout << "PAID: \033[32mPHP" << fixed << setprecision(2) << payment
       << "\033[0m\n";
  cout << "CHANGE: \033[32mPHP" << fixed << setprecision(2) << change
       << "\033[0m\n";
  cout << "==================\n";
  cout << "Thank you for your order!\n";

  // Print to file
  if (receiptFile) {
    receiptFile << "===== RECEIPT =====\n";
    receiptFile << "Receipt: " << receiptCode << "\n";
    receiptFile << "Cashier: " << username << "\n";
    receiptFile << "Date: " << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon
                << "-" << ltm->tm_mday << "\n";
    receiptFile << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":"
                << ltm->tm_sec << "\n";
    receiptFile << "------------------\n";
    for (size_t i = 0; i < orderItems.size(); i++) {
      int itemIndex = orderItems[i];
      receiptFile << quantities[i] << " x " << menu[itemIndex].name << " - PHP"
                  << fixed << setprecision(2)
                  << menu[itemIndex].price * quantities[i] << "\n";
    }
    receiptFile << "------------------\n";
    if (hasDiscount) {
      receiptFile << "Subtotal: \033[32mPHP" << fixed << setprecision(2)
                  << total / (1 - DISCOUNT_RATE) << "\033[0m\n";
      receiptFile << "Discount (20%): -\033[32mPHP" << fixed << setprecision(2)
                  << total * DISCOUNT_RATE / (1 - DISCOUNT_RATE) << "\033[0m\n";
    }
    receiptFile << "TOTAL:  PHP" << fixed << setprecision(2) << total << "\n";
    receiptFile << "PAID:   PHP" << fixed << setprecision(2) << payment << "\n";
    receiptFile << "CHANGE: PHP" << fixed << setprecision(2) << change << "\n";
    receiptFile << "==================\n";
    receiptFile << "Thank you for your order!\n";
    receiptFile.close();
  }
  cout << "\nPress enter to continue...";
  cin.ignore();
  clearSystem();
}

void printReceipt() {
  extern string lastCashierUsername;
  printReceipt(lastCashierUsername);
}

void cashierMenu() {
  int mainChoice;
  while (true) {
    displayCenterMenu();
    cout << "\033[36mEnter your choice:\033[0m ";
    string input;
    cin >> input;
    try {
      mainChoice = stoi(input);
    } catch (...) {
      clearSystem();
      cout << "\033[91mInvalid input! Please enter a number.\033[0m\n";
      continue;
    }
    switch (mainChoice) {
    case 1:
      clearSystem();
      displayMenu();
      break;
    case 2:
      clearSystem();
      takeCustomerOrder();
      if (!orderItems.empty()) {
        displayTotalOrder();
        hasDiscount = askForDiscount();
        applyDiscount(hasDiscount);
        takeCustomerPayment();
        calculateChange();
        printReceipt();
        continue;
      }
      break;
    case 3:
      clearSystem();
      cout << "\033[92mExiting cashier menu...\033[0m\n";
      return;
    default:
      clearSystem();
      cout << "\033[91mInvalid choice. Please try again.\033[0m\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}
