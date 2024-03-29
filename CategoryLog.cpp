#include <string>
#include <list>

#include "CategoryLog.h"

//initialize static members
CategoryLog* CategoryLog::instance = nullptr;
int CategoryLog::numberOfCategories = 0;

CategoryLog::CategoryLog()
{
}


CategoryLog* CategoryLog::GetCategoryLog()
{
	if (!instance)
    {
        instance = new CategoryLog();
    }
    return instance;
}


std::list<Category*> CategoryLog::GetListOfCategories()
{
    return instance->categoryList;
}

void CategoryLog::AddCategory(Category* newCategory)
{
	categoryList.push_back(newCategory);
    numberOfCategories++;
}

void CategoryLog::DeleteCategory(Category* category)
{
	instance->categoryList.remove(category);
    delete category;
    numberOfCategories--;
}


// Destructor implementation
CategoryLog::~CategoryLog()
{

    for (auto& category : categoryList)
    {
        delete category;
    }

    // Clear the list
    categoryList.clear();
}
