#include <algorithm>

#include "TransactionLog.h"
#include "Transaction.h"


//initialize static members
TransactionLog* TransactionLog::instance = 0;
int TransactionLog::numberOfTransactions = 0;
int TransactionLog::IDCounter = 1;

TransactionLog::TransactionLog()
{
	//no need any special initialization of the list object I think
}

TransactionLog::TransactionLog(TransactionLog& transactionLog)
{
	//is it even necessary to declare the copy constructor?
}

TransactionLog* TransactionLog::GetTransactionLog()
{
	if (instance == 0){
		instance = new TransactionLog();
	}
	return instance;
}

std::list<Transaction*> TransactionLog::GetListOfTransactions()
{
	return transactionList;
}

int TransactionLog::GetNumberOfTransactions(){
	return numberOfTransactions;
}

void TransactionLog::AddTransaction(Transaction& newTransaction)
{

	//log must be kept in chronological order
	newTransaction.SetTransactionID(IDCounter);
	IDCounter++;
	std::list<Transaction*>::iterator iter = transactionList.begin();
	for (iter; iter!=transactionList.end(); iter++){
		if ( (*iter)->IsTransactionOlderThan(newTransaction) ) { break; }
	}
	transactionList.insert(iter,&newTransaction);
	numberOfTransactions++;
}

void TransactionLog::DeleteTransaction(Transaction* transaction)
{
	std::list<Transaction*>::iterator iter = std::find(transactionList.begin(), transactionList.end(), transaction);
	if (transaction == *iter){
		transactionList.remove(*iter);
		numberOfTransactions--;
		delete transaction;
	}//if the iter is indeed pointing to the transaction we are looking for and has not simply reached the back of the list
	//could have just used std::list remove_if?
}

std::list<Transaction*> TransactionLog::RetrieveTransactions(int start, int end)
{
    std::list<Transaction*> retrievedTransactions;

    if ((start > numberOfTransactions) || (start > end) || (start <= 0)) {
        std::cout << "invalid start/end index" << std::endl;
        return retrievedTransactions; // return an empty list
    }

    if (end > numberOfTransactions) {
        end = numberOfTransactions;
    }

    std::list<Transaction*>::iterator iterEnd = transactionList.begin();
    std::advance(iterEnd, end);

    std::list<Transaction*>::iterator iterStart = transactionList.begin();
    std::advance(iterStart, start - 1);

    // Iterate from iterStart to iterEnd (inclusive)
    for (auto iter = iterStart; iter != iterEnd; ++iter) {
        retrievedTransactions.push_back(*iter);
    }
	//std::cout << "Length of transactions: " << retrievedTransactions.size() << std::endl;
    return retrievedTransactions;
}



std::list<Transaction*> TransactionLog::RetrieveTransactions(tm start, tm end)
{
    if (mktime(&start) == -1 || mktime(&end) == -1) {
        std::cout << "Invalid tm objects" << std::endl;
        return std::list<Transaction*>();  // Return an empty list
    }

    if (mktime(&end) < mktime(&start))
	{
    	std::cout << "End is earlier than start" << std::endl;
    	return {}; // Return an empty list
	}


    std::list<Transaction*> retrievedTransactions;

    for (const auto& transaction : transactionList) {
        tm timestamp = transaction->GetDate(); 

        if (std::difftime(std::mktime(&timestamp), std::mktime(&start)) >= 0 &&
            std::difftime(std::mktime(&end), std::mktime(&timestamp)) >= 0) {
            retrievedTransactions.push_back(transaction);
        }
    }

	//std::cout << "Length of transactions: " << retrievedTransactions.size() << std::endl;
    return retrievedTransactions;
}




/*
Transaction** TransactionLog::RetrieveTransactions(tm start, tm end)
{
	if ( (mktime(&start) == -1) || (mktime(&end) == -1) ) {
		std::cout << "invalid tm objects" << std::endl;
		return nullptr;
	}
	if ( (mktime(&start) == -1) < (mktime(&end) == -1) ) {
		std::cout << "start is older than end" << std::endl;
		return nullptr;
	}

	std::list<Transaction*>::iterator iterStart = transactionList.begin();
	

	for (iterStart; iterStart!=transactionList.end(); iterStart++){
		if ( (*iterStart)->IsTransactionOlderThan(start) ) { break; }
	}

	std::list<Transaction*>::iterator iterEnd = iterStart;
	std::list<Transaction*>::iterator iter = iterStart;

	for (iterEnd; iterEnd!=transactionList.end(); iterEnd++){
		if ( (*iterEnd)->IsTransactionOlderThan(end) ) { break; }
	}


	Transaction** retrievedTransactions = new Transaction*[std::distance(iterEnd,iterStart)];
	int i = 0;

	for (;;) {
		retrievedTransactions[i] = *iter;
		if (iter == iterEnd) { break; }
		iter++; i++;
	}

	return retrievedTransactions;
	//this would have been much shorter if we returned a list or something but for now sticking with the decision to return a static array
}

*/

Transaction* TransactionLog::FindTransactionByID(int transactionID)
{
    for (const auto& transaction : transactionList)
    {
        if (transaction->GetTransactionID() == transactionID)
        {
            return transaction;
        }
    }
    
    // If no transaction is found with the given ID
    return nullptr;
}

