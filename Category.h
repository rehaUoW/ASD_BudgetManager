#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

#include "TransactionType.h"

class Category
{
private:
	TransactionType transactionType;

	std::string name;

	double budget;


public:

	Category(TransactionType transactionType_, std::string name_);

	std::string GetName();

	TransactionType GetTransactionType();

	double GetBudget();

	void SetName(std::string newName);

	void SetBudget(double value);

};
#endif