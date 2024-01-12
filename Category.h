#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TransactionType.h"
#include "Transaction.h"
#include "std::string.h"

class Category
{
private:
	TransactionType transactionType;

	string name :std:;

	double budget;

	Transaction transaction[];

public:
	Category(TransactionType transactionType_, std::string name_);

	std::string GetName();

	double GetBudget();

	void SetName(std::string newName);

	void SetBudget(double value);

};
#endif
