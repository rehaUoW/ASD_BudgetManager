#include "TransactionLog.h"
#include "Transaction.h"


//initialize static members
TransactionLog* TransactionLog::instance = 0;
int TransactionLog::numberOfTransactions = 0;

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
	std::list<Transaction*>::iterator iter = std::find(transactionList.begin(), transactionList.end(), (*iter)->IsTransactionOlder(newTransaction));
	transactionList.insert(iter,&newTransaction);
	numberOfTransactions++;
}

void TransactionLog::DeleteTransaction(Transaction& transaction)
{
	std::list<Transaction*>::iterator iter = std::find(transactionList.begin(), transactionList.end(), transaction);
	if (&transaction == *iter){
		transactionList.remove(*iter);
		numberOfTransactions--;
	}//if the iter is indeed pointing to the transaction we are looking for and has not simply reached the back of the list
	//could have just used std::list remove_if?
}

Transaction** TransactionLog::RetrieveTransactions(int start, int end)
{
	if ( (start > numberOfTransactions) || (start > end) || (start <= 0) ){
		std::cout << "invalid start/end index" << std::endl;
		return;
	}//basic input parameter validation
	if (end > numberOfTransactions){
		end = numberOfTransactions;
	}//cap to end of list

	std::list<Transaction*>::iterator iterStart = transactionList.begin();
	std::advance(iterStart,start - 1);
	std::list<Transaction*>::iterator iter = iterStart;
	std::list<Transaction*>::iterator iterEnd = transactionList.begin();
	std::advance(iterEnd,end - 1);

	Transaction** retrievedTransactions = new Transaction*[end - start + 1];
	int i = 0;

	for (;;) {
		retrievedTransactions[i] = *iter;
		if (iter == iterEnd) { break; }
		iter++; i++;
	}

	return retrievedTransactions;
}

Transaction** TransactionLog::RetrieveTransactions(tm start, tm end)
{
	if ( (mktime(&start) == -1) || (mktime(&end) == -1) ) {
		std::cout << "invalid tm objects" << std::endl;
		return;
	}
	if ( (mktime(&start) == -1) < (mktime(&end) == -1) ) {
		std::cout << "start is older than end" << std::endl;
		return;
	}

	std::list<Transaction*>::iterator iterStart = std::find(transactionList.begin(), transactionList.end(), (*iterStart)->IsTransactionOlder(start));
	std::list<Transaction*>::iterator iterEnd = std::find(transactionList.begin(), transactionList.end(), (*iterEnd)->IsTransactionOlder(end));
	std::list<Transaction*>::iterator iter = iterStart;

	Transaction** retrievedTransactions = new Transaction*[std::distance(iterEnd,iterStart)];
	int i = 0;

	for (;;) {
		retrievedTransactions[i] = *iter;
		if (iter == iterEnd) { break; }
		iter++; i++;
	}

	return retrievedTransactions;
}
