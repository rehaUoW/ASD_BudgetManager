#include <string>
#include <list>
#include <iostream>


#include "Category.h"

// Constructor for the Category Class 
Category::Category(TransactionType transactionType_, std::string name_)
{
	transactionType = transactionType_;
	name = name_;	
	budget = 0;
}


// Getters 
std::string Category::GetName()
{
	return name;
}

TransactionType Category::GetTransactionType()
{
	return transactionType;
}

double Category::GetBudget()
{
	return budget;
}






// Setters 

void Category::SetName(std::string newName)
{
	name = newName;
}

void Category::SetBudget(double value)
{
	budget = value;
}