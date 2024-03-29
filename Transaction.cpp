
#include "Transaction.h"
#include "CommonFunctions.h"

/*Constructors*/
Transaction::Transaction(TransactionType transactionType_, tm date_, double amount_, Category* category_)
{
	transactionID = 0; //just to initialize
	recurringID = 0; //only used if transaction is recurring
	transactionType = transactionType_;
	date = date_;
	amount = amount_;
	note = "";
	recurring = RecurringType::none;
	category = category_;
}

Transaction::Transaction(Transaction& t){
	transactionID = t.transactionID;
	recurringID = t.recurringID;
	transactionType = t.transactionType;
	date = t.date;
	amount = t.amount;
	note = t.note;
	recurring = t.recurring;
	recurranceEndDate = t.recurranceEndDate;
	category = t.category;
} // copy constructor



/*Setters*/
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

void Transaction::SetTransactionID(int ID)
{
	transactionID = ID;
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

void Transaction::SetRecurringID(int id){
	recurringID = id;
}



/*Getters*/
void Transaction::PrintTransaction()
{
	std::cout<<"Transaction ID: " << transactionID << std::endl;;
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
	std::cout<<"Category: ";
	std::cout<< category->GetName();
	std::cout << std::endl;
	std::cout<<"Amount: " << amount << std::endl;
	if (note != "")
	{
		std::cout << "Note: " << note << std::endl;
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



/*Predicates*/
bool Transaction::IsTransactionOlderThan(Transaction& anotherTransaction){
	tm anotherDate = anotherTransaction.GetDate();
	return mktime(&date) < mktime(&anotherDate);
}//for use in TransactionLog when adding Transactions to the list chronologically

bool Transaction::IsTransactionOlderThan(tm& time){
    return mktime(&date) < mktime(&time);
}

