#ifndef CATEGORY_LOG_H
#define CATEGORY_LOG_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Category.h"
#include "stdListOfPointersToCategoryObjects.h"

/**
 * Singleton class for the log of categories (contains a std::list of pointers to objects of the Category class)
 */
class CategoryLog
{
private:
	static CategoryLog* instance;

	static int numberOfCategories;

	Category* catList[];

private:
	CategoryList();

	CategoryList(CategoryLog& categoryList);

public:
	static CategoryLog* GetCategoryLog();

	static stdListOfPointersToCategoryObjects GetListOfCategories();

	static void AddCategory(Category* newCategory);

	static void DeleteCategory(Category* category);

};
#endif
