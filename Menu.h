#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "std::string.h"

class Menu
{
public:
	void EnterTrasactionWizard();

	void ViewTransactionsWizard();

	void EditTransaction();

	void DeleteTransaction();

	void ViewCategories();

	void AddNewCategory(std::string newCategory);

	void EnterBudgetWizard();

	void PrintBudgetStatus();

};
#endif
