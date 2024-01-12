#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Transaction.h"
#include "stdListOfPointersToTransactionObjects.h"
#include "Date.h"

/**
 * Singleton class for the log of transactions (contains a std::list of pointers to objects of the Transaction class)
 */
class TransactionLog
{
private:
	static TransactionLog* instance;

	static int numberOfTransactions;

	Transaction* transactionList[];

private:
	TransactionLog();

	TransactionLog(TransactionLog& transactionLog);

public:
	static TransactionLog* GetTransactionLog();

	static stdListOfPointersToTransactionObjects GetListOfTransactions();

	static void AddTransaction(Transaction* newTransaction);

	static void DeleteTransaction(Transaction* transaction);

	static Transaction*[] RetrieveTransactions(int start, int end);

	static Transaction*[] RetrieveTransactions(Date start, Date end);

};
#endif
