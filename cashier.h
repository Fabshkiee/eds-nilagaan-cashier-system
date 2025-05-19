//CODED ALL BY NATHAN SARROSA
#ifndef CASHIER_H
#define CASHIER_H

#include "food_item.h"
#include "user.h"
#include "clearSystem.h"
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

void displayCenterMenu();
void displayFoodMenu();
void takeCustomerOrder();
void displayTotalOrder();

bool askForDiscount();

void applyDiscount(bool hasDiscount);
void takeCustomerPayment();
void calculateChange();
void printReceipt();
void cashierMenu();
void cashierMenu();

#endif