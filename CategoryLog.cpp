#include <string>
#include <list>

#include "CategoryLog.h"

CategoryLog* CategoryLog::instance = nullptr;
// int CategoryLog::numberOfCategories;

CategoryLog::CategoryLog()
{
	numberOfCategories = 0;
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
	instance->categoryList.push_back(newCategory);
    instance->numberOfCategories++;
}

void CategoryLog::DeleteCategory(Category* category)
{
	instance->categoryList.remove(category);
    delete category;
    instance->numberOfCategories--;
}

// impletementation of the constrcutor 
/*
CategoryLog::CategoryLog(const CategoryLog& other)
{
    numberOfCategories = other.numberOfCategories;

    for (const auto& category : other.categoryList)
    {
        Category* newCategory = new Category(*category);
        categoryList.push_back(newCategory);
    }
}
*/
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
