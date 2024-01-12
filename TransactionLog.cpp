#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TransactionLog.h"

TransactionLog* TransactionLog::instance;
int TransactionLog::numberOfTransactions;

TransactionLog::TransactionLog()
{
}

TransactionLog::TransactionLog(TransactionLog& transactionLog)
{
}

TransactionLog* TransactionLog::GetTransactionLog()
{
	return 0;
}

stdListOfPointersToTransactionObjects TransactionLog::GetListOfTransactions()
{
	return 0;
}

void TransactionLog::AddTransaction(Transaction* newTransaction)
{
}

void TransactionLog::DeleteTransaction(Transaction* transaction)
{
}

Transaction*[] TransactionLog::RetrieveTransactions(int start, int end)
{
	return 0;
}

Transaction*[] TransactionLog::RetrieveTransactions(Date start, Date end)
{
	return 0;
}
