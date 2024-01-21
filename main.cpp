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
    Category c1(TransactionType::income,"testCategory");
    time_t now_ = time(0);
    time_t* now = &now_;
    tm time = *localtime(now);
    Transaction* t1 = new Transaction(TransactionType::income,time,123,&c1);
    Transaction* t2 = new Transaction(TransactionType::income,time,456,&c1);
    Transaction* t3 = new Transaction(TransactionType::income,time,789,&c1);

    (TransactionLog::GetTransactionLog())->AddTransaction(*t1);
    (TransactionLog::GetTransactionLog())->AddTransaction(*t2);
    (TransactionLog::GetTransactionLog())->AddTransaction(*t3);

    //Vishwa area

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
    std::list<Transaction*> list = (TransactionLog::GetTransactionLog())->GetListOfTransactions();
    std::cout << "LIST AS OF END OF PROGRAM" << std::endl;
    for (std::list<Transaction*>::iterator iter = list.begin();iter!=list.end();iter++) {
        (*iter)->PrintTransaction();
        std::cout << std::endl;
    }

    //Vishwa area

    //Ninujan area

    //Ruvin area

    return 0;
}
