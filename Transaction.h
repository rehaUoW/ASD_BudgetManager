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

	/*attributes*/
	int transactionID; //handled by Transaction Log - used as unique identifier

	TransactionType transactionType; //primary attribute

	tm date; //primary attribute

	double amount; //primary attribute

	std::string note; //secondary attribute

	RecurringType recurring; //used with recurring transactions

	tm recurranceEndDate; //used with recurring transactions

	int recurringID; //used with recurring transactions

	Category* category; //primary attribute

public:

	/*constructors*/
	Transaction(TransactionType transactionType_, tm date_, double amount_, Category* category_);

	Transaction(Transaction& t); // copy constructor


	/*Setters*/
	void AddNote(std::string note_);

	void AppendNote(std::string note_);

	void AddRecurring(RecurringType recurring_);

	void AddRecurranceEndDate(tm endDate);	

	void SetTransactionID(int ID);
	
	void SetTransactionType(TransactionType newTransactionType);

	void SetDate(tm newDate_);

	void SetAmount(double newAmount);

	void SetCategory(Category* newCategory);

	void SetRecurringID(int id);



	/*Getters*/
	void PrintTransaction();

	int GetTransactionID();

	TransactionType GetTransactionType();

	tm GetDate();

	double GetAmount();

	std::string GetNote();

	RecurringType GetRecurring();

	tm GetRecurranceEndDate();

	Category* GetCategory();



	/*Predicates*/
	bool IsTransactionOlderThan(Transaction& anotherTransaction); //predicate for use in TransactionLog when adding Transactions to the list chronologically

	bool IsTransactionOlderThan(tm& time); //predicate	

};
#endif
