#include <iostream>
#include "Menu.h"
#include "Category.h"
#include "TransactionType.h"
// #include "CommonFunctions.h"

int main()
{ 
    Menu menu;

    int choice;

    //Reha area
    

    //Vishwa area

    // Assume you have a CategoryLog instance
CategoryLog* categoryLog = CategoryLog::GetCategoryLog();

// Create some categories
Category* category1 = new Category(TransactionType::expense, "Groceries");
Category* category2 = new Category(TransactionType::income, "Utilities");
Category* category3 = new Category(TransactionType::expense, "Entertainment");
Category* category4 = new Category(TransactionType::income, "Salary");
Category* category5 = new Category(TransactionType::expense, "Dining Out");
Category* category6 = new Category(TransactionType::income, "Bonus");
Category* category7 = new Category(TransactionType::expense, "Shopping");
Category* category8 = new Category(TransactionType::income, "Investments");

// Add categories to the log
categoryLog->AddCategory(category1);
categoryLog->AddCategory(category2);
categoryLog->AddCategory(category3);
categoryLog->AddCategory(category4);
categoryLog->AddCategory(category5);
categoryLog->AddCategory(category6);
categoryLog->AddCategory(category7);
categoryLog->AddCategory(category8);

// Assume you have a TransactionLog instance
TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

// Create some transactions
tm date1 = {1, 1, 0, 10, 1, 121}; // 2021-01-10 00:00:00
tm date2 = {2, 2, 0, 15, 2, 121}; // 2021-02-15 00:00:00
tm date3 = {3, 3, 0, 20, 3, 121}; // 2021-03-20 00:00:00
tm date4 = {4, 4, 0, 5, 4, 121};  // 2021-04-05 00:00:00
tm date5 = {5, 5, 0, 10, 5, 121}; // 2021-05-10 00:00:00
tm date6 = {6, 6, 0, 15, 6, 121}; // 2021-06-15 00:00:00
tm date7 = {7, 7, 0, 20, 7, 121}; // 2021-07-20 00:00:00
tm date8 = {8, 8, 0, 25, 8, 121}; // 2021-08-25 00:00:00
tm date9 = {9, 9, 0, 30, 9, 121}; // 2021-09-30 00:00:00
tm date10 = {10, 10, 0, 5, 10, 121};  // 2021-10-05 00:00:00
tm date11 = {11, 11, 0, 10, 11, 121}; // 2021-11-10 00:00:00
tm date12 = {12, 12, 0, 15, 12, 121}; // 2021-12-15 00:00:00
tm date13 = {13, 13, 1, 20, 1, 122};   // 2022-01-20 00:00:00
tm date14 = {14, 14, 2, 25, 2, 122};   // 2022-02-25 00:00:00
tm date15 = {15, 15, 3, 1, 3, 122};    // 2022-03-01 00:00:00

Transaction transaction1(TransactionType::expense, date1, 50.0, category1);
Transaction transaction2(TransactionType::income, date2, 100.0, category2);
Transaction transaction3(TransactionType::expense, date3, 30.0, category3);
Transaction transaction4(TransactionType::income, date4, 80.0, category4);
Transaction transaction5(TransactionType::expense, date5, 25.0, category5);
Transaction transaction6(TransactionType::income, date6, 120.0, category6);
Transaction transaction7(TransactionType::expense, date7, 40.0, category7);
Transaction transaction8(TransactionType::income, date8, 90.0, category8);
Transaction transaction9(TransactionType::expense, date9, 60.0, category1);
Transaction transaction10(TransactionType::income, date10, 110.0, category2);
Transaction transaction11(TransactionType::expense, date11, 35.0, category3);
Transaction transaction12(TransactionType::income, date12, 70.0, category4);
Transaction transaction13(TransactionType::expense, date13, 45.0, category5);
Transaction transaction14(TransactionType::income, date14, 130.0, category6);
Transaction transaction15(TransactionType::expense, date15, 55.0, category7);

// Add transactions to the log
transactionLog->AddTransaction(transaction1);
transactionLog->AddTransaction(transaction2);
transactionLog->AddTransaction(transaction3);
transactionLog->AddTransaction(transaction4);
transactionLog->AddTransaction(transaction5);
transactionLog->AddTransaction(transaction6);
transactionLog->AddTransaction(transaction7);
transactionLog->AddTransaction(transaction8);
transactionLog->AddTransaction(transaction9);
transactionLog->AddTransaction(transaction10);
transactionLog->AddTransaction(transaction11);
transactionLog->AddTransaction(transaction12);
transactionLog->AddTransaction(transaction13);
transactionLog->AddTransaction(transaction14);
transactionLog->AddTransaction(transaction15);




    //Ninujan area

    //Ruvin area




    do
    {
        std::cout << "\nMenu Options:\n";
        std::cout << "1. Enter Transaction\n";
        std::cout << "2. View Transactions\n";
        std::cout << "3. Edit Transaction\n";
        std::cout << "4. Delete Transaction\n";
        std::cout << "5. View Categories\n";
        std::cout << "6. Add New Category\n";
        std::cout << "7. Enter Budget\n";
        std::cout << "8. Print Budget Status\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        

        switch (choice)
        {
        case 1:
            menu.EnterTrasactionWizard();
            break;
        case 2:
            menu.ViewTransactionsWizard();
            break;
        case 3:
            menu.EditTransaction();
            break;
        case 4:
            menu.DeleteTransaction();
            break;
        case 5:
            menu.ViewCategories();
            break;
        case 6:
            {
                TransactionType transactionType_;
                std::string name_;

                // Get the name of the Category
                std::cout << "Enter the name of the Category: ";
                std::getline(std::cin, name_);

                // Get the TransactionType as an integer
                int transactionTypeInt;
                std::cout << "Enter the TransactionType (0 for income, 1 for expense): ";
                std::cin >> transactionTypeInt;

                // Cast the integer to TransactionType
                transactionType_ = static_cast<TransactionType>(transactionTypeInt);

                // Create a new Category
                Category newCategory = Category(transactionType_, name_);

                // Add the new category to the menu
                menu.AddNewCategory(newCategory);

            }
            break;
        case 7:
            menu.EnterBudgetWizard();
            break;
        case 8:
            menu.PrintBudgetStatus();
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 0);



    //Reha area

    //Vishwa area

    //Ninujan area

    //Ruvin area

    return 0;
}
