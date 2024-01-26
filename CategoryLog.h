#ifndef CATEGORY_LOG_H
#define CATEGORY_LOG_H

#include <string>
#include <list>

#include "Category.h"


// Singleton class for the log of categories (contains a std::list of pointers to objects of the Category class)
class CategoryLog
{
private:
	static CategoryLog* instance;

	std::list<Category*> categoryList;

	static int numberOfCategories;

	// Private constructor to enforce the singleton pattern
    CategoryLog();

    // Avoid copy construction and assignment
    CategoryLog(const CategoryLog& categoryLog) = delete;
    CategoryLog& operator=(const CategoryLog& other) = delete;

public:
	static CategoryLog* GetCategoryLog();

	std::list<Category*> GetListOfCategories();

	void AddCategory(Category* newCategory);

	void DeleteCategory(Category* category);

	/*
	 // Explicitly deleted copy constructor and copy assignment to enforce Singleton pattern
    CategoryLog(const CategoryLog& other) = delete;
    CategoryLog& operator=(const CategoryLog& other) = delete;

    //  create a copy constructor
    CategoryLog(const CategoryLog& other);
	
	*/

	// Destructor declaration
    ~CategoryLog();

};
#endif