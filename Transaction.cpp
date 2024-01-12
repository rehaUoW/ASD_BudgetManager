#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Transaction.h"


Transaction::Transaction(TransactionType transactionType_, Date date_, double amount_, Category* category_)
{
}

void Transaction::AddNote(std::string note_)
{
}

void Transaction::AddRecurring(RecurringType recurring_)
{
}

void Transaction::AddRecurranceEndDate(int* endDate)
{
}

void Transaction::PrintTransaction()
{
}

void Transaction::SetTransactionID(int newTransactionID_)
{
}

void Transaction::SetTransactionType(TransactionType newTransactionType)
{
}

void Transaction::SetDate(Date newDate_)
{
}

void Transaction::SetAmount(double newAmount)
{
}

void Transaction::SetCategory(Category* newCategory)
{
}

void Transaction::SetNote(std::string newNote)
{
}

int Transaction::GetTransactionID()
{
	return 0;
}

TransactionType Transaction::GetTransactionType()
{
	return 0;
}

Date Transaction::GetDate()
{
	return 0;
}

double Transaction::GetAmount()
{
	return 0;
}

string Transaction::GetNote()
{
	return 0;
}

RecurringType Transaction::GetRecurring()
{
	return 0;
}

Date Transaction::GetRecurranceEndDate()
{
	return 0;
}

Category* Transaction::GetCategory()
{
	return 0;
}
