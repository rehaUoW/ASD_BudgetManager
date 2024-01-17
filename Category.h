#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <list>
#include <iostream>


#include "TransactionType.h"
// #include "Transaction.h"
// #include "CategoryLog.h"
// #include "std::string.h"

class Category
{
private:
	TransactionType transactionType;

	std::string name;

	double budget;

	// std::list<Transaction> transactions;
	// Transaction transaction;
	// CategoryLog categoryLog;

public:
	// constructor for the category 
	Category(TransactionType transactionType_, std::string name_);

	std::string GetName();

	double GetBudget();

	void SetName(std::string newName);

	void SetBudget(double value);

};
#endif