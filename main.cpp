#include <iostream>
#include "Menu.h"
#include "Category.h"
#include "TransactionType.h"
#include "CategoryLog.h"


int main()
{ 
    Menu menu;

    int choice;



    /*PRELOADED DATA*/
    CategoryLog* categoryLog = CategoryLog::GetCategoryLog();

    // Create some categories
    Category* category1 = new Category(TransactionType::expense, "Groceries");
    Category* category2 = new Category(TransactionType::expense, "Utilities");
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
    categoryLog->AddCategory(category5);
    categoryLog->AddCategory(category7);    
    categoryLog->AddCategory(category4);
    categoryLog->AddCategory(category6);
    categoryLog->AddCategory(category8);


    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Create some transactions
    tm date1 = {1, 1, 0, 10, 1, 121}; // 2021-02-10 
    tm date2 = {2, 2, 0, 15, 2, 121}; // 2021-03-15 
    tm date3 = {3, 3, 0, 20, 3, 121}; // 2021-04-20 
    tm date4 = {4, 4, 0, 5, 4, 121};  // 2021-05-05 
    tm date5 = {5, 5, 0, 10, 5, 121}; // 2021-06-10 
    tm date6 = {6, 6, 0, 15, 6, 121}; // 2021-07-15 
    tm date7 = {7, 7, 0, 20, 7, 121}; // 2021-08-20 
    tm date8 = {8, 8, 0, 25, 8, 121}; // 2021-09-25 
    tm date9 = {9, 9, 0, 30, 9, 121}; // 2021-10-30 
    tm date10 = {10, 10, 0, 5, 10, 121};  // 2021-11-05 
    tm date11 = {11, 11, 0, 10, 11, 121}; // 2021-12-10 
    tm date12 = {12, 12, 0, 15, 11, 121}; // 2021-12-15 
    tm date13 = {13, 13, 1, 20, 1, 122};   // 2022-02-20 
    tm date14 = {14, 14, 2, 25, 2, 122};   // 2022-03-25 
    tm date15 = {15, 15, 3, 1, 3, 122};    // 2022-04-01 
    tm date16 = {15, 15, 3, 20, 11, 123};   // 2023-12-20 
    tm date17 = {15, 15, 3, 29, 11, 123};   // 2023-12-29 
    tm date18 = {15, 15, 3, 1, 0, 124};    // 2024-01-01 

    Transaction* transaction1 = new Transaction(TransactionType::expense, date1, 50.0, category1);
    Transaction* transaction2= new Transaction(TransactionType::income, date2, 100.0, category2);
    Transaction* transaction3= new Transaction(TransactionType::expense, date3, 30.0, category3);
    Transaction* transaction4= new Transaction(TransactionType::income, date4, 80.0, category4);
    Transaction* transaction5= new Transaction(TransactionType::expense, date5, 25.0, category5);
    Transaction* transaction6= new Transaction(TransactionType::income, date6, 120.0, category6);
    Transaction* transaction7= new Transaction(TransactionType::expense, date7, 40.0, category7);
    Transaction* transaction8= new Transaction(TransactionType::income, date8, 90.0, category8);
    Transaction* transaction9= new Transaction(TransactionType::expense, date9, 60.0, category1);
    Transaction* transaction10= new Transaction(TransactionType::income, date10, 110.0, category2);
    Transaction* transaction11= new Transaction(TransactionType::expense, date11, 35.0, category3);
    Transaction* transaction12= new Transaction(TransactionType::income, date12, 70.0, category4);
    Transaction* transaction13= new Transaction(TransactionType::expense, date13, 45.0, category5);
    Transaction* transaction14= new Transaction(TransactionType::income, date14, 130.0, category6);
    Transaction* transaction15= new Transaction(TransactionType::expense, date15, 55.0, category7);
    Transaction* transaction16= new Transaction(TransactionType::expense, date16, 123.0, category7);
    Transaction* transaction17= new Transaction(TransactionType::expense, date17, 456.0, category7);
    Transaction* transaction18= new Transaction(TransactionType::expense, date18, 789.0, category7);

    // Add transactions to the log
    transactionLog->AddTransaction(*transaction1);
    transactionLog->AddTransaction(*transaction2);
    transactionLog->AddTransaction(*transaction3);
    transactionLog->AddTransaction(*transaction4);
    transactionLog->AddTransaction(*transaction5);
    transactionLog->AddTransaction(*transaction6);
    transactionLog->AddTransaction(*transaction7);
    transactionLog->AddTransaction(*transaction8);
    transactionLog->AddTransaction(*transaction9);
    transactionLog->AddTransaction(*transaction10);
    transactionLog->AddTransaction(*transaction11);
    transactionLog->AddTransaction(*transaction12);
    transactionLog->AddTransaction(*transaction13);
    transactionLog->AddTransaction(*transaction14);
    transactionLog->AddTransaction(*transaction15);
    transactionLog->AddTransaction(*transaction16);
    transactionLog->AddTransaction(*transaction17);
    transactionLog->AddTransaction(*transaction18);
   



    /*Display CLI for User*/
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
        std::cout << std::endl;
        

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
            menu.AddNewCategory();
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



    /*Clean up memory*/
    std::list<Transaction*> transactionList = transactionLog->GetListOfTransactions();
    for (Transaction* t : transactionList){
        delete t;
    }
    std::list<Category*> categoryList = categoryLog->GetListOfCategories();
    for (Category* c : categoryList){
        delete c;
    }

    return 0;
}
