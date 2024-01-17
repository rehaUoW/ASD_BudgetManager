#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <list>
#include <ctime>

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

private:
	TransactionLog();

	TransactionLog(TransactionLog& transactionLog);

public:
	static TransactionLog* GetTransactionLog();

	std::list<Transaction*> GetListOfTransactions();

	static int GetNumberOfTransactions();

	void AddTransaction(Transaction& newTransaction);

	void DeleteTransaction(Transaction& transaction);

	Transaction** RetrieveTransactions(int start, int end); //returns pointer to an array. MUST DELETE ARRAY AFTER USE
	//usage: arguments 1 & 5 means the first thru fifth item in the list (inclusive) will be returned

	Transaction** RetrieveTransactions(tm start, tm end); //returns pointer to an array. MUST DELETE ARRAY AFTER USE

	Transaction* FindTransactionByID(int transactionID); //Vishwa 

};

#endif
