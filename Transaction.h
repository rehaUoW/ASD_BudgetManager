#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TransactionType.h"
#include "Date.h"
#include "std::string.h"
#include "RecurringType.h"
#include "Category.h"

class Transaction
{
private:
	int transactionID;

	TransactionType transactionType;

	Date date;

	double amount;

	std::string note;

	RecurringType recurring;

	Date recurranceEndDate;

	Category* category;

public:
	Transaction(TransactionType transactionType_, Date date_, double amount_, Category* category_);

	void AddNote(std::string note_);

	void AddRecurring(RecurringType recurring_);

	void AddRecurranceEndDate(int* endDate);

	void PrintTransaction();

	void SetTransactionID(int newTransactionID_);

	void SetTransactionType(TransactionType newTransactionType);

	void SetDate(Date newDate_);

	void SetAmount(double newAmount);

	void SetCategory(Category* newCategory);

	void SetNote(std::string newNote);

	int GetTransactionID();

	TransactionType GetTransactionType();

	Date GetDate();

	double GetAmount();

	string GetNote();

	RecurringType GetRecurring();

	Date GetRecurranceEndDate();

	Category* GetCategory();

};
#endif
