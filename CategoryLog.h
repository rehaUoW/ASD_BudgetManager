#ifndef CATEGORY_LOG_H
#define CATEGORY_LOG_H

#include <string>
#include <list>
#include <iostream>

#include "Category.h"
// #include "stdListOfPointersToCategoryObjects.h"

// Singleton class for the log of categories (contains a std::list of pointers to objects of the Category class)

class CategoryLog
{
private:
	static CategoryLog* instance;
	std::list<Category*> categoryList;

	static int numberOfCategories;

	// Category categoryList[];
	// Category* catList[];

	// Private constructor to enforce the singleton pattern
    CategoryLog();

    // Avoid copy construction and assignment
    CategoryLog(const CategoryLog& categoryLog) = delete;
    CategoryLog& operator=(const CategoryLog& other) = delete;

public:
	static CategoryLog* GetCategoryLog();

	// static stdListOfPointersToCategoryObjects GetListOfCategories();

	std::list<Category*> GetListOfCategories();

	static void AddCategory(Category* newCategory);

	static void DeleteCategory(Category* category);

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