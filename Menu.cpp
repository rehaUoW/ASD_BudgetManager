#include <iostream>

#include "Menu.h"

using namespace std;

Category* Menu::ChooseCategory(const std::list<Category*>& categories, TransactionType transactionType)
{
    std::vector<Category*> validCategories;

    for (const auto& category : categories)
    {
        if (category->GetTransactionType() == transactionType)
        {
            validCategories.push_back(category);
        }
    }

    // Display the list of valid categories
    if (validCategories.empty())
    {
        std::cout << "No valid categories available for the specified transaction type.\n";
        return nullptr;
    }

    while (true)
    {
        std::cout << "Choose a category:\n";
        std::cout << "----------------------------" << std::endl;
        for (size_t i = 0; i < validCategories.size(); ++i)
        {
            std::cout << i + 1 << ". " << validCategories[i]->GetName() << '\n';
        }
        std::cout << "----------------------------" << std::endl;
        // Get user input for category choice
        int choice;
        std::cout << "Enter the number corresponding to the category: ";
        std::cin >> choice;
        //std::cout << "----------------------------" << std::endl;
        // Validate the user's choice
        if (choice >= 1 && choice <= static_cast<int>(validCategories.size()))
        {
            return validCategories[choice - 1];
        }
        else
        {
            std::cout << "Invalid choice. Please enter a valid category number.\n";
        }
    }
}



void Menu::EnterTrasactionWizard()
{
    TransactionType transactionType_;
    tm date_;
    double amount_;
    string note_;
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "Enter the transaction details:\n";
    cout << "----------------------------\n";
    
    // Get transaction type
    cout << "Enter the transaction type (0 for income, 1 for expense): ";
    int userInput;
    //cout << "----------------------------" << endl;
    // Loop until valid input is provided
    while (!(cin >> userInput) || (userInput != 0 && userInput != 1)) {
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "Invalid input. Please enter 0 for income or 1 for expense: ";
    }
    
    transactionType_ = static_cast<TransactionType>(userInput);

    // Clear the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Assuming you have a CategoryLog instance
    CategoryLog* categoryLog = CategoryLog::GetCategoryLog();
    cout << endl;
    // Display the list of categories or implement a method to choose a category
    list<Category*> categories = categoryLog->GetListOfCategories();

    // Call the ChooseCategory function to get the user's choice
    Category* chosenCategory = ChooseCategory(categories, transactionType_);

    cout << endl;
    // Get transaction date
    //cout << "Enter the transaction date (YYYY MM DD HH MM): ";
    date_ = getUserInputDate("transaction");

    cout << endl;
    // Get transaction amount
    cout << "Enter the transaction amount: ";
    cin >> amount_;


    Transaction* newTransaction = new Transaction(transactionType_, date_, amount_, chosenCategory);
 
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    transactionLog->AddTransaction(*newTransaction);
    cout << endl;
    cout << "Enter the Note: ";
    cin.ignore();
    getline(cin, note_);
    newTransaction->AddNote(note_);

    //viewLastNTransactions(transactionLog, 10);
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "Transaction added successfully!\n";
    cout << "----------------------------\n";
    newTransaction->PrintTransaction();
    cout << "----------------------------" << endl;
    cout << endl;
    //PrintAllTransactions(transactionLog);

    cout << "Choose an option to proceed:" << endl;
    cout << "1. Exit wizard"<< endl;
    cout << "2. Recur transaction"<< endl;
    int choice;
    cin >> choice;
    switch (choice){
        case 2:
            cout << "Choose recurring frequency:" << endl;
            cout << "1. Annually"<< endl;
            cout << "2. Monthly"<< endl;
            cout << "3. Weekly"<< endl;
            cout << "4. Daily"<< endl;
            int rf;
            cin >> rf;
            switch (rf)
            {
            case 1:
                newTransaction->AddRecurring(RecurringType::annual);
                break;
            case 2:
                newTransaction->AddRecurring(RecurringType::monthly);
                break;	
            case 3:
                newTransaction->AddRecurring(RecurringType::weekly);
                break;	
            case 4:
                newTransaction->AddRecurring(RecurringType::daily);
                break;	
            default:
                break;
            }
            if ((rf >= 1) && (rf <=4)){ //if valid recurring frequency has been entered
                tm rEnd = getUserInputDate("recurring end");
                newTransaction->AddRecurranceEndDate(rEnd);
                transactionLog->AddRecurringTransactions(*newTransaction,rEnd);
                cout << "Recurring transactions added successfully." <<endl;
            }else{
                cout << "Invalid entry" <<endl;
            }


            break;
        default:
            break;
    }
}

void Menu::ViewTransactionsWizard()
{
    // Display options to the user
    cout << "Choose an option to view transactions:\n";
    cout << "1. Last month transactions\n";
    cout << "2. Current month transactions\n";
    cout << "3. Last 10 transactions\n";
    cout << "4. Custom date range\n";
    cout << "5. Specific number of transactions\n";
    cout << "Enter your choice: ";
    cout << endl << "----------------------------" << endl;
    int choice;
    cin >> choice;

    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Handle user choice
    switch (choice)
    {
    case 1:
        // Last month transactions
        viewTransactionsByDateRange(transactionLog, DateRangeType::LastMonth);
        break;

    case 2:
        // Current month transactions
        viewTransactionsByDateRange(transactionLog, DateRangeType::CurrentMonth);
        break;

    case 3:
        // Last 10 transactions
        viewLastNTransactions(transactionLog, 10);
        //cout << "-------------" << endl;
        //PrintAllTransactions(transactionLog);
        break;

    case 4:
        // Custom date range
        viewTransactionsByDateRange(transactionLog, DateRangeType::Custom);
        break;

    case 5:
    {
        // Specific number of transactions
        int viewNumTransactions;
        int numberOfTransactions = transactionLog->GetNumberOfTransactions();

        do {
            cout << "Enter the number of transactions to view (up to " << numberOfTransactions << "): ";
            cin >> viewNumTransactions;

            if (viewNumTransactions <= numberOfTransactions) {
                viewLastNTransactions(transactionLog, viewNumTransactions);
                break;
            } else {
                cout << "Invalid input. Number of transactions to view exceeds the total number of transactions.\n";
            }
        }while (viewNumTransactions > numberOfTransactions);

        break;

    }
    default:
        cout << "Invalid choice\n";
        break;
    }
}


void Menu::viewTransactionsByDateRange(TransactionLog* transactionLog, DateRangeType rangeType)
{
    
    // Get the current date
    time_t currentTime = time(nullptr);
    tm* currentDate = localtime(&currentTime);

    tm startDate;
    tm endDate;

    // Set the appropriate start and end dates based on the selected rangeType
    if (rangeType == DateRangeType::LastMonth)
    {
        startDate = calculateLastMonthStartDate(*currentDate);
        endDate = calculateLastMonthEndDate(*currentDate);
    }
    else if (rangeType == DateRangeType::CurrentMonth)
    {
        startDate = calculateCurrentMonthStartDate(*currentDate);
        endDate = *currentDate;
    }
    else if (rangeType == DateRangeType::Custom)
    {
        startDate = getUserInputDate("start");
        endDate = getUserInputDate("end");

        /*
        // Get start date from the user
        
        std::cout << "Enter the start date (YYYY MM DD HH MM): ";
        std::cin >> startDate.tm_year >> startDate.tm_mon >> startDate.tm_mday >> startDate.tm_hour >> startDate.tm_min;
        
        // Get end date from the user
        std::cout << "Enter the end date (YYYY MM DD HH MM): ";
        std::cin >> endDate.tm_year >> endDate.tm_mon >> endDate.tm_mday >> endDate.tm_hour >> endDate.tm_min;
        */

    }

    cout << "----------------------------" << endl;
    std::cout << "Start Date: " << formatDate(startDate) << std::endl;
    std::cout << "End Date: " << formatDate(endDate) << std::endl;
    cout << "----------------------------" << endl;

    // Retrieve and display transactions within the custom date range
    std::list<Transaction*> transactions = transactionLog->RetrieveTransactions(startDate, endDate);
    displayTransactions(transactions);
    //delete[] transactions; // Note: This is not needed if you are using std::list or smart pointers for memory management
}

tm Menu::calculateLastMonthStartDate(const tm& currentDate)
{
    tm lastMonthStartDate = currentDate;
    lastMonthStartDate.tm_mon -= 1;
    if (lastMonthStartDate.tm_mon < 0)
    {
        lastMonthStartDate.tm_mon += 12;
        lastMonthStartDate.tm_year -= 1;
    }

    lastMonthStartDate.tm_mday = 1; // Set to the 1st day of the month
    lastMonthStartDate.tm_hour = 0;
    lastMonthStartDate.tm_min = 0;
    lastMonthStartDate.tm_sec = 0;
    return lastMonthStartDate;

}

tm Menu::calculateLastMonthEndDate(const tm& currentDate)
{

    tm lastMonthEndDate = currentDate;
    lastMonthEndDate.tm_mday = 1; // Set to the first day of the current month
    lastMonthEndDate.tm_hour = 0;
    lastMonthEndDate.tm_min = 0;
    lastMonthEndDate.tm_sec = 0;

    // Subtract 1 second to get the last second of the last day of the previous month
    time_t lastMonthEndTimestamp = mktime(&lastMonthEndDate);
    lastMonthEndTimestamp -= 1;
    lastMonthEndDate = *localtime(&lastMonthEndTimestamp);

    return lastMonthEndDate;

}

tm Menu::calculateCurrentMonthStartDate(const tm& currentDate)
{
    tm currentMonthStartDate = currentDate;
    currentMonthStartDate.tm_mday = 1; // Set to the 1st day of the month
    currentMonthStartDate.tm_hour = 0;
    currentMonthStartDate.tm_min = 0;
    currentMonthStartDate.tm_sec = 0;
    return currentMonthStartDate;
}

std::string Menu::formatDate(const tm& date)
{
    return std::to_string(date.tm_year + 1900) + "-" +
           std::to_string(date.tm_mon + 1) + "-" +
           std::to_string(date.tm_mday) + " " +
           std::to_string(date.tm_hour) + ":" +
           std::to_string(date.tm_min) + ":" +
           std::to_string(date.tm_sec);
}



void Menu::viewLastNTransactions(TransactionLog* transactionLog, int viewNumTransactions)
{
    int numberOfTransactions = transactionLog->GetNumberOfTransactions();
    int start = 1;
    //int start = max(1, min(numberOfTransactions - viewNumTransactions + 1, numberOfTransactions - 1));

    int end = viewNumTransactions;
    cout << "----------------------------" << endl;
    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;
    cout << "----------------------------" << endl;
    // Retrieve and display the last N transactions
    list<Transaction*> transactionsList = transactionLog->RetrieveTransactions(start, end);

    displayTransactions(transactionsList);
}




void Menu::displayTransactions(const std::list<Transaction*>& transactions)
{
    // Check if the list is empty
    if (transactions.empty())
    {
        cout << "----------------------------" << endl;
        cout << "No transactions to display." << endl;
        cout << "----------------------------" << endl;
        return;
    }

    // Display the transactions
    cout << "----------------------------" << endl;
    cout << "List of Transactions:\n";
    cout << "----------------------------" << endl;
    for (const auto& transaction : transactions)
    {
        cout << endl;
        transaction->PrintTransaction();
        cout << endl;
        cout << "----------------------------" << endl;
    }

    cout << "----------------------------" << endl;
    cout << endl;

    // Display the total number of transactions
    cout << "Length of transactions: " << transactions.size() << endl;
    int totalTransactions = TransactionLog::GetTransactionLog()->GetNumberOfTransactions();
    cout << "Total number of transactions: " << totalTransactions << endl;
    cout << endl;
    cout << "----------------------------" << endl;
}






/*
void Menu::displayTransactionsList(const list<Transaction*>& transactions)
{
    if (transactions.empty())
    {
        cout << "No transactions to display.\n";
        return;
    }

    cout << "Transaction List:\n";
    for (const auto& transaction : transactions)
    {
        cout << "ID: " << transaction->GetTransactionID() << "\n";
        transaction->PrintTransaction();
        cout << "-------------------------------\n";
    }
}
*/


void Menu::EditTransaction()
{
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Display transactions for user to choose from
    cout << "Choose a transaction to edit:\n";

    // Display transactions
    displayTransactions(transactionLog->GetListOfTransactions());

    int transactionID;
    cout << "Enter the transaction ID to edit: ";
    cin >> transactionID;

    // Retrieve the transaction to edit
    Transaction* transactionToEdit = transactionLog->FindTransactionByID(transactionID);

    if (transactionToEdit == nullptr)
    {
        cout << "Transaction not found.\n";
        return;
    }

    // Display current details of the transaction
    cout << "Current details of the transaction:\n";
    transactionToEdit->PrintTransaction();

    // Ask the user which attribute to edit
    cout << "Choose the attribute to edit:\n"
                 "1. Amount\n"
                 "2. Note\n"
                 "3. Append Note\n"
                 "4. Transaction Type and/or Category\n"
                 "5. Date\n"
                 "6. Cancel\n";

    int choice;
    cin >> choice;

    string newNote;
    switch (choice)
    {
        case 1:
            // Edit amount
            cout << "Enter the new amount: ";
            double newAmount;
            cin >> newAmount;
            transactionToEdit->SetAmount(newAmount);
            break;
        case 2:
            // Edit note
            cout << "Enter the new note: ";
            cin.ignore(); // Clear the newline character from the buffer
            getline(cin, newNote);
            transactionToEdit->AddNote(newNote);
            break;
        case 3:
            // Append note
            cout << "Enter text to append: ";
            cin.ignore(); // Clear the newline character from the buffer
            getline(cin, newNote);
            transactionToEdit->AppendNote(newNote);
            break;
        case 4:
            {
            //Edit Transaction Type and Category

            // Clear the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the transaction type (0 for income, 1 for expense): ";
            int userInput;
            while (!(cin >> userInput) || (userInput != 0 && userInput != 1)) {
                cin.clear();  // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                cout << "Invalid input. Please enter 0 for income or 1 for expense: ";
            }
            
            TransactionType tt = static_cast<TransactionType>(userInput);
            transactionToEdit->SetTransactionType(tt);

            // Clear the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            CategoryLog* categoryLog = CategoryLog::GetCategoryLog();
            cout << endl;
            // Display the list of categories or implement a method to choose a category
            list<Category*> categories__ = categoryLog->GetListOfCategories();

            // Call the ChooseCategory function to get the user's choice
            Category* chosenCategory = ChooseCategory(categories__, tt);
            transactionToEdit->SetCategory(chosenCategory);
            
            break;
            }
        case 5:
            //Edit date
            tm newDate;
            cout << "Enter the new year YYYY: ";
            int year;
            cin >> year;
            year = year - 1900;
            newDate.tm_year = year;
            cout << "Enter the new month MM: ";
            int month;
            cin >> month;
            month = month - 1;
            newDate.tm_mon = month;
            cout << "Enter the remaining parameters (DD HH MM): ";
            cin >>  newDate.tm_mday >> newDate.tm_hour >> newDate.tm_min;
            transactionToEdit->SetDate(newDate);
            break;
        case 6:
            //cancel
            cout << "Cancelled!\n";
            return;
        default:
            cout << "Invalid choice. No changes made.\n";
            return;
    }

    

    cout << "Transaction edited successfully!\n";
}


void Menu::DeleteTransaction()
{
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Display transactions for user to choose from
    cout << "Choose a transaction to delete:\n";

    // Display transactions
    displayTransactions(transactionLog->GetListOfTransactions());

    int transactionID;
    cout << "Enter the transaction ID to delete: ";
    cin >> transactionID;

    // Retrieve the transaction to delete
    Transaction* transactionToDelete = transactionLog->FindTransactionByID(transactionID);

    if (transactionToDelete == nullptr)
    {
        cout << "Transaction not found.\n";
        return;
    }

    // Confirm deletion
    char confirm;
    cout << "Are you sure you want to delete this transaction? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y')
    {
        // Delete the transaction
        transactionLog->DeleteTransaction(transactionToDelete);
        cout << "Transaction deleted!\n";
    }
    else
    {
        cout << "Transaction deletion cancelled.\n";
    }
}


void Menu::ViewCategories()
{
    // Get the list of categories from CategoryLog
    std::list<Category*> categories = CategoryLog::GetCategoryLog()->GetListOfCategories();

    if (categories.empty()) {
        cout << "No categories available.\n";
        return;
    }


    std::cout << "Available Categories:\n";
    std::cout << std::endl;
    for (Category* categoryPtr : CategoryLog::GetCategoryLog()->GetListOfCategories()) {
        Category& category = *categoryPtr;
 
        if (categoryPtr) {
            // Using GetName and GetBudget methods to retrieve category information
            std::cout << "---------------" << std::endl;
            if (categoryPtr->GetTransactionType() == 0){
                std::cout << "Type: Income" << std::endl;
            }else{
                std::cout << "Type: Expense" << std::endl;
            }
            std::cout << "Name: " << categoryPtr->GetName() << std::endl;
            std::cout <<"Budget: " << categoryPtr->GetBudget() << std::endl;
            std::cout << "---------------" << std::endl;
            std::cout <<  std::endl;
        }
        else {
            std::cout << "Invalid category detected.\n";
        }

    }
}


void Menu::AddNewCategory() {
    std::string name;
    int typeInput;
    TransactionType type;

    // Clear the newline character left in the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the name of the new category: "<<std::endl;
    std::getline(std::cin,name);
    std::cout << std::endl;

    cout << "Select the transaction type (0 for EXPENSE, 1 for INCOME, ...): ";
    cin >> typeInput;



    // Clear the newline character left in the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (typeInput == 0) {
        type = TransactionType::expense;
    }
    else if (typeInput == 1) {
        type = TransactionType::income;
    }
    else {
        cout << "Invalid transaction type selected. Aborting operation.\n";
        return;
    }

    // Creating a new category dynamically
    Category* newCategory = new Category(type, name);

    // Adding the new category to CategoryLog
    CategoryLog::GetCategoryLog()->AddCategory(newCategory);

    std::cout << "New category '" << name << "' added successfully.\n";

}

void Menu::EnterBudgetWizard()
{
    
    for (Category* categoryPtr : CategoryLog::GetCategoryLog()->GetListOfCategories()) {
        Category& category = *categoryPtr;
        double budget;
        std::cout << "Enter the budget for " << category.GetName() << ": ";
        while (!(std::cin >> budget)) {
            std::cout << "Invalid input. Please enter a number for " << category.GetName() << ": ";
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the incorrect input
        }
        category.SetBudget(budget);
        std::cout << "Budget set for " << category.GetName() << ": LKR " << budget << std::endl;
    }
    

}

void Menu::PrintBudgetStatus()
{
    for (Category* categoryPtr : CategoryLog::GetCategoryLog()->GetListOfCategories()) {
        Category& category = *categoryPtr;
        std::cout << "Budget set for " << category.GetName() << ": LKR " << category.GetBudget() << std::endl;
    }

}


void Menu::PrintAllTransactions(TransactionLog* transactionLog)
{
    // Assuming you have an instance of TransactionLog named 'transactionLog'
    list<Transaction*> transactions = transactionLog->GetListOfTransactions();

    // Iterate through the list and print each transaction
    for (const auto& transaction : transactions)
    {
        transaction->PrintTransaction();
        cout << endl;
    }
}



tm Menu::getUserInputDate(const std::string& prompt)
{
    tm inputDate = {};
    bool validInput = false;

    do
    {
        // Get user input for the date
        std::cout << "Enter the " << prompt << " date (YYYY MM DD HH MM): ";
        if (!(std::cin >> inputDate.tm_year >> inputDate.tm_mon >> inputDate.tm_mday >> inputDate.tm_hour >> inputDate.tm_min))
        {
            std::cerr << "Invalid input for date." << std::endl;
            // Clear the error state and ignore the rest of the line
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Prompt the user again
        }

        // Adjust the tm structure
        inputDate.tm_year -= 1900; // Adjust the year
        inputDate.tm_mon -= 1;    // Adjust the month

        // Validate the adjusted date
        if (inputDate.tm_mon < 0 || inputDate.tm_mon > 11 ||
            inputDate.tm_mday < 1 || inputDate.tm_mday > 31 ||
            inputDate.tm_hour < 0 || inputDate.tm_hour > 23 ||
            inputDate.tm_min < 0 || inputDate.tm_min > 59)
        {
            std::cerr << "Invalid date values. Please check the range of each field." << std::endl;
            continue; // Prompt the user again
        }

        // Check for months with 30 days
        if ((inputDate.tm_mon == 3 || inputDate.tm_mon == 5 || inputDate.tm_mon == 8 || inputDate.tm_mon == 10) &&
            (inputDate.tm_mday > 30))
        {
            std::cerr << "Invalid date values. This month can only have 30 days." << std::endl;
            continue; // Prompt the user again
        }

        // Check for February and leap years
        if (inputDate.tm_mon == 1)
        {
            bool isLeapYear = ((inputDate.tm_year % 4 == 0) && (inputDate.tm_year % 100 != 0)) || (inputDate.tm_year % 400 == 0);
            if (inputDate.tm_mday > (isLeapYear ? 29 : 28))
            {
                std::cerr << "Invalid date values. February can have " << (isLeapYear ? 29 : 28) << " days." << std::endl;
                continue; // Prompt the user again
            }
        }

        // If all checks passed, set validInput to true
        validInput = true;

    } while (!validInput);

    return inputDate;
}
