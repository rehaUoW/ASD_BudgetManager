#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <limits> 
#include <ctime>
#include "Category.h"
#include "CategoryLog.h"
#include "TransactionLog.h"
#include "Transaction.h"
#include "TransactionType.h"
// #include "CommonFunctions.h"

class Menu
{
private:
    TransactionLog transactionLog;

    Category* ChooseCategory(std::list<Category*>& categories);


public:
	Menu();

	void EnterTrasactionWizard();

	void ViewTransactionsWizard();
    void viewTransactionsLastMonth(TransactionLog* transactionLog);
    void viewTransactionsCurrentMonth(TransactionLog* transactionLog);
    void viewLastNTransactions(TransactionLog* transactionLog, int numTransactions);
    void viewCustomDateRange(TransactionLog* transactionLog);
    void displayTransactions(Transaction** transactions);

	void Menu::displayTransactionsList(const std::list<Transaction*>& transactions);
	void EditTransaction();

	void DeleteTransaction();

	void ViewCategories();

	void AddNewCategory(Category newCategory);

	void EnterBudgetWizard();

	void PrintBudgetStatus();

};
#endif
