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
using namespace std;

enum class DateRangeType
{
    LastMonth,
    CurrentMonth,
    Custom
};

class Menu
{
private:
    //TransactionLog transactionLog;

    //Category* ChooseCategory(list<Category*>& categories);
	tm calculateLastMonthStartDate(const tm& currentDate);
    tm calculateLastMonthEndDate(const tm& currentDate);
    tm calculateCurrentMonthStartDate(const tm& currentDate);
    string formatDate(const tm& date);


public:
	
	void EnterTrasactionWizard();

	void ViewTransactionsWizard();
    //void viewTransactionsLastMonth(TransactionLog* transactionLog);
    //void viewTransactionsCurrentMonth(TransactionLog* transactionLog);
    void viewLastNTransactions(TransactionLog* transactionLog, int numTransactions);
	void viewTransactionsByDateRange(TransactionLog* transactionLog, DateRangeType rangeType);
    //void viewCustomDateRange(TransactionLog* transactionLog);
    void displayTransactions(const list<Transaction*>& transactions);

	//void displayTransactionsList(const list<Transaction*>& transactions);
	void EditTransaction();

	void DeleteTransaction();

	void ViewCategories();

	void AddNewCategory(Category newCategory);

	void EnterBudgetWizard();

	void PrintBudgetStatus();

	Category* ChooseCategory(const list<Category*>& categories, TransactionType transactionType);

	void PrintAllTransactions(TransactionLog* transactionLog);

	tm getUserInputDate(const string& prompt);
};
#endif
