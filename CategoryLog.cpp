#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CategoryLog.h"

CategoryLog* CategoryLog::instance;
int CategoryLog::numberOfCategories;

CategoryLog::CategoryList()
{
}

CategoryLog::CategoryList(CategoryLog& categoryList)
{
}

CategoryLog* CategoryLog::GetCategoryLog()
{
	return 0;
}

stdListOfPointersToCategoryObjects CategoryLog::GetListOfCategories()
{
	return 0;
}

void CategoryLog::AddCategory(Category* newCategory)
{
}

void CategoryLog::DeleteCategory(Category* category)
{
}
