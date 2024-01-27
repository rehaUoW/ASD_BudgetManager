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

	/*Helper functions*/
	tm calculateLastMonthStartDate(const tm& currentDate);
    tm calculateLastMonthEndDate(const tm& currentDate);
    tm calculateCurrentMonthStartDate(const tm& currentDate);
    string formatDate(const tm& date);


public:
	
	/*Wizards*/
	void EnterTrasactionWizard();

	void ViewTransactionsWizard();

	void EditTransaction();

	void DeleteTransaction();

	void ViewCategories();

	void AddNewCategory();

	void EnterBudgetWizard();

	void PrintBudgetStatus();


	/*Helper functions*/
    void viewLastNTransactions(TransactionLog* transactionLog, int numTransactions);

	void viewTransactionsByDateRange(TransactionLog* transactionLog, DateRangeType rangeType);

	std::list<Transaction*> GetTransactionsByDateRange(TransactionLog* transactionLog, DateRangeType rangeType);

    void displayTransactions(const list<Transaction*>& transactions);	

	Category* ChooseCategory(const list<Category*>& categories, TransactionType transactionType);

	void PrintAllTransactions(TransactionLog* transactionLog);

	tm getUserInputDate(const string& prompt);
};
#endif
