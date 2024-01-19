#include <string>
#include <list>
#include <iostream>


#include "Category.h"

// Constructor for the Catogary Class 
Category::Category(TransactionType transactionType_, std::string name_)
{
	transactionType = transactionType_;
	name = name_;	
}


// Getters 
std::string Category::GetName()
{
	return name;
}

double Category::GetBudget()
{
	return budget;
}

TransactionType Category::GetTransactionType() {
	return transactionType;
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