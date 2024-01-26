#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <ctime>

#include "TransactionType.h"
#include "RecurringType.h"
#include "Category.h"



class Transaction
{
private:
	int transactionID;

	TransactionType transactionType;

	tm date;

	double amount;

	std::string note;

	RecurringType recurring;

	tm recurranceEndDate;

	int recurringID;

	Category* category;

public:
	Transaction(TransactionType transactionType_, tm date_, double amount_, Category* category_);

	Transaction(Transaction& t); // copy constructor

	void AddNote(std::string note_);

	void AppendNote(std::string note_);

	void AddRecurring(RecurringType recurring_);

	void AddRecurranceEndDate(tm endDate);	

	void SetTransactionID(int ID);
	
	void SetTransactionType(TransactionType newTransactionType);

	void SetDate(tm newDate_);

	void SetAmount(double newAmount);

	void SetCategory(Category* newCategory);

	void PrintTransaction();

	int GetTransactionID();

	TransactionType GetTransactionType();

	tm GetDate();

	double GetAmount();

	std::string GetNote();

	RecurringType GetRecurring();

	tm GetRecurranceEndDate();

	Category* GetCategory();

	bool IsTransactionOlderThan(Transaction& anotherTransaction); //predicate for use in TransactionLog when adding Transactions to the list chronologically

	bool IsTransactionOlderThan(tm& time);

	void SetRecurringID(int id);

};
#endif
