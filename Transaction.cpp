
#include "Transaction.h"
#include "CommonFunctions.h"


Transaction::Transaction(TransactionType transactionType_, tm date_, double amount_, Category* category_)
{
	transactionID = 1;
	transactionType = transactionType_;
	date = date_;
	amount = amount_;
	note = "";
	recurring = RecurringType::none;
	category = category_;
}

void Transaction::AddNote(std::string note_)
{
	note = note_;
}

void Transaction::AppendNote(std::string note_)
{
	note += note_;
}

void Transaction::AddRecurring(RecurringType recurring_)
{
	recurring = recurring_;
}

void Transaction::AddRecurranceEndDate(tm endDate)
{
	recurranceEndDate = endDate;
}

void Transaction::IncrementTransactionID()
{
	transactionID++;
}

void Transaction::SetTransactionType(TransactionType newTransactionType)
{
	transactionType=newTransactionType;
}

void Transaction::SetDate(tm newDate_)
{
	date=newDate_;
}

void Transaction::SetAmount(double newAmount)
{
	amount = newAmount;
}

void Transaction::SetCategory(Category* newCategory)
{
	category = newCategory;
}

void Transaction::PrintTransaction()
{
	CommonFunctions::PrintDateTime(date);
	std::cout << std::endl;
	std::cout<<"Transaction Type: ";
	switch (transactionType)
	{
	case 0:
		std::cout << "Income";
		break;
	case 1:
		std::cout << "Expense";
		break;	
	default:
		break;
	}
	std::cout << std::endl;
	std::cout<<"Amount: " << amount << std::endl;
	if (note != "")
	{
		std::cout << note << std::endl;
	}
	if (recurring != 0) {
		std::cout << "Repeats ";
		switch (recurring)
		{
		case 1:
			std::cout << "annually ";
			break;
		case 2:
			std::cout << "monthly ";
			break;	
		case 3:
			std::cout << "weekly ";
			break;	
		case 4:
			std::cout << "daily ";
			break;	
		default:
			break;
		}
		std::cout << "till ";
		CommonFunctions::PrintDateTime(recurranceEndDate);
		std::cout << std::endl;
	}	
}

int Transaction::GetTransactionID()
{
	return transactionID;
}

TransactionType Transaction::GetTransactionType()
{
	return transactionType;
}

tm Transaction::GetDate()
{
	return date;
}

double Transaction::GetAmount()
{
	return amount;
}

std::string Transaction::GetNote()
{
	return note;
}

RecurringType Transaction::GetRecurring()
{
	return recurring;
}

tm Transaction::GetRecurranceEndDate()
{
	return recurranceEndDate;
}

Category* Transaction::GetCategory()
{
	return category;
}

bool Transaction::IsTransactionOlder(Transaction& anotherTransaction){
	return mktime(&date) < mktime(&anotherTransaction.GetDate());
}//predicate for use in TransactionLog when adding Transactions to the list chronologically

bool Transaction::IsTransactionOlder(tm& time){
    return mktime(&date) < mktime(&time);
}