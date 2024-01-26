#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <list>
#include <ctime>
#include <iostream>

#include "Transaction.h"


/**
 * Singleton class for the log of transactions (contains a std::list of pointers to objects of the Transaction class)
 */
class TransactionLog
{
private:
	static TransactionLog* instance;

	static int numberOfTransactions;

	std::list<Transaction*> transactionList; //front of list is the most recent

	static int IDCounter;

	static int recurringIDCounter;

private:
	/*Constructors*/
	TransactionLog();

	TransactionLog(TransactionLog& transactionLog);

public:
	static TransactionLog* GetTransactionLog(); //Singleton accessor

	std::list<Transaction*> GetListOfTransactions();

	static int GetNumberOfTransactions();

	void AddTransaction(Transaction& newTransaction);

	void AddRecurringTransactions(Transaction& newTransaction, tm endDate);

	void DeleteTransaction(Transaction* transaction);

	std::list<Transaction*> RetrieveTransactions(int start, int end); //retrieve certain interval of transactions

	std::list<Transaction*> RetrieveTransactions(tm start, tm end); //retrieve certain interval of transactions

	Transaction* FindTransactionByID(int transactionID); 
};

#endif
