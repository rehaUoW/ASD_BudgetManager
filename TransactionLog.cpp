#include <algorithm>

#include "TransactionLog.h"
#include "Transaction.h"


//initialize static members
TransactionLog* TransactionLog::instance = 0;
int TransactionLog::numberOfTransactions = 0;
int TransactionLog::IDCounter = 1;
int TransactionLog::recurringIDCounter = 1;

TransactionLog::TransactionLog()
{
	//no need any special initialization of the list object
}

TransactionLog::TransactionLog(TransactionLog& transactionLog)
{
	
}

TransactionLog* TransactionLog::GetTransactionLog()
{
	if (instance == 0){
		instance = new TransactionLog();
	}
	return instance;
}//singleton accessor

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
	newTransaction.SetTransactionID(IDCounter); //assigns unique ID
	IDCounter++;
	std::list<Transaction*>::iterator iter = transactionList.begin();
	for (iter; iter!=transactionList.end(); iter++){
		if ( (*iter)->IsTransactionOlderThan(newTransaction) ) { break; }
	}
	transactionList.insert(iter,&newTransaction);
	numberOfTransactions++;
}

void TransactionLog::AddRecurringTransactions(Transaction& newTransaction, tm EndDate){
	RecurringType rf = newTransaction.GetRecurring();
	newTransaction.SetRecurringID(recurringIDCounter); //sets unique recurring ID for the entire set of transactions that will be cloned
	recurringIDCounter++;
	tm currentDate = newTransaction.GetDate();
	time_t currentDateS = std::mktime(&currentDate);
	time_t endDateS = std::mktime(&EndDate);
	switch (rf)
	{
	case 1:
		// recur annually
		while(currentDateS < endDateS){
			Transaction* recurTransaction = new Transaction(newTransaction);
			currentDate.tm_year = currentDate.tm_year + 1;
			currentDateS = std::mktime(&currentDate);
			recurTransaction->SetDate(currentDate);
			AddTransaction(*recurTransaction);
		}
		break;
	case 2:
		//recur monthly
		while(currentDateS < endDateS){
			Transaction* recurTransaction = new Transaction(newTransaction);
			currentDate.tm_mon = currentDate.tm_mon + 1;
			currentDateS = std::mktime(&currentDate);
			recurTransaction->SetDate(currentDate);
			AddTransaction(*recurTransaction);
		}
		break;	
	case 3:
		//recur weekly
		while(currentDateS < endDateS){
			Transaction* recurTransaction = new Transaction(newTransaction);
			currentDate.tm_yday = currentDate.tm_yday + 7;
			currentDateS = std::mktime(&currentDate);
			recurTransaction->SetDate(currentDate);
			AddTransaction(*recurTransaction);
		}
		break;	
	case 4:
		//recur daily
		while(currentDateS < endDateS){
			Transaction* recurTransaction = new Transaction(newTransaction);
			currentDate.tm_yday = currentDate.tm_yday + 1;
			currentDateS = std::mktime(&currentDate);
			recurTransaction->SetDate(currentDate);
			AddTransaction(*recurTransaction);
		}
		break;	
	default:
		break;
	}
} // feeds cloned transaction objects to the TransactionLog::AddTransaction function

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

    return retrievedTransactions;
}



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

