using namespace std;

#include "Menu.h"

Category* Menu::ChooseCategory(std::list<Category*>& categories)
{
    int choice;

    while (true)
    {
        cout << "Choose a category:\n";

        // Display the list of categories with corresponding indices
        int index = 1;
        for (const auto& category : categories)
        {
            cout << index << ". " << category->GetName() << endl;
            ++index;
        }

        // Get user input for category choice
        cout << "Enter the number corresponding to the category: ";
        cin >> choice;

        // Validate the user's choice
        if (choice >= 1 && choice <= index - 1)
        {
            auto iter = categories.begin();
            advance(iter, choice - 1);
            return *iter;
        }
        else
        {
            cout << "Invalid choice. Please enter a valid category number.\n";
        }
    }
}

void Menu::EnterTrasactionWizard()
{
    TransactionType transactionType_;
    tm date_;
    double amount_;

    cout << "Enter the transaction details:\n";

    // Get transaction type
    cout << "Enter the transaction type (0 for income, 1 for expense): ";
    int userInput;

    // Loop until valid input is provided
    while (!(cin >> userInput) || (userInput != 0 && userInput != 1)) {
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "Invalid input. Please enter 0 for income or 1 for expense: ";
    }

    transactionType_ = static_cast<TransactionType>(userInput);


    // Clear the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get transaction date
    cout << "Enter the transaction date (YYYY MM DD HH MM): ";
    cin >> date_.tm_year >> date_.tm_mon >> date_.tm_mday >> date_.tm_hour >> date_.tm_min;

    // Get transaction amount
    cout << "Enter the transaction amount: ";
    cin >> amount_;

    // Assuming you have a CategoryLog instance
    CategoryLog* categoryLog = CategoryLog::GetCategoryLog();

    // Display the list of categories or implement a method to choose a category
    list<Category*> categories = categoryLog->GetListOfCategories();

    // Call the ChooseCategory function to get the user's choice
    Category* chosenCategory = ChooseCategory(categories);

    Transaction newTransaction(transactionType_, date_, amount_, chosenCategory);

    // Assuming transactionLog is an instance of TransactionLog
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();
    transactionLog->AddTransaction(newTransaction);

    cout << "Transaction added successfully!\n";
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

    int choice;
    cin >> choice;

    // Assuming you have a TransactionLog instance
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Handle user choice
    switch (choice)
    {
    case 1:
        // Last month transactions
        viewTransactionsLastMonth(transactionLog);
        break;

    case 2:
        // Current month transactions
        viewTransactionsCurrentMonth(transactionLog);
        break;

    case 3:
        // Last 10 transactions
        viewLastNTransactions(transactionLog, 10);
        break;

    case 4:
        // Custom date range
        viewCustomDateRange(transactionLog);
        break;

    case 5:
        // Specific number of transactions
        int numTransactions;
        cout << "Enter the number of transactions to view: ";
        cin >> numTransactions;
        viewLastNTransactions(transactionLog, numTransactions);
        break;

    default:
        cout << "Invalid choice\n";
        break;
    }
}

void Menu::viewTransactionsLastMonth(TransactionLog* transactionLog)
{
    /*
    // Get the current date
    time_t currentTime = time(nullptr);
    tm* currentDate = localtime(&currentTime);

    // Calculate the start date for last month
    tm lastMonthStartDate = *currentDate;
    lastMonthStartDate.tm_mon -= 1;
    if (lastMonthStartDate.tm_mon < 0)
    {
        lastMonthStartDate.tm_mon += 12;
        lastMonthStartDate.tm_year -= 1;
    }

    // Retrieve and display transactions for last month
    Transaction** transactions = transactionLog->RetrieveTransactions(lastMonthStartDate, *currentDate);
    displayTransactions(transactions);
    delete[] transactions;
    */
}

void Menu::viewTransactionsCurrentMonth(TransactionLog* transactionLog)
{
    /*
    // Get the current date
    time_t currentTime = time(nullptr);
    tm* currentDate = localtime(&currentTime);

    // Set the start date for the current month
    tm currentMonthStartDate = *currentDate;
    currentMonthStartDate.tm_mday = 1;

    // Retrieve and display transactions for the current month
    Transaction** transactions = transactionLog->RetrieveTransactions(currentMonthStartDate, *currentDate);
    displayTransactions(transactions);
    delete[] transactions;
    */
}

void Menu::viewLastNTransactions(TransactionLog* transactionLog, int numTransactions)
{
    int start = max(1, transactionLog->GetNumberOfTransactions() - numTransactions + 1);
    int end = transactionLog->GetNumberOfTransactions();

    // Retrieve and display the last N transactions
    Transaction** transactions = transactionLog->RetrieveTransactions(start, end);
    displayTransactions(transactions);
    delete[] transactions;
}


void Menu::viewCustomDateRange(TransactionLog* transactionLog)
{
    // Get start date from the user
    tm startDate;
    cout << "Enter the start date (YYYY MM DD HH MM): ";
    cin >> startDate.tm_year >> startDate.tm_mon >> startDate.tm_mday >> startDate.tm_hour >> startDate.tm_min;

    // Get end date from the user
    tm endDate;
    cout << "Enter the end date (YYYY MM DD HH MM): ";
    cin >> endDate.tm_year >> endDate.tm_mon >> endDate.tm_mday >> endDate.tm_hour >> endDate.tm_min;

    // Retrieve and display transactions within the custom date range
    Transaction** transactions = transactionLog->RetrieveTransactions(startDate, endDate);
    displayTransactions(transactions);
    delete[] transactions;
}

void Menu::displayTransactions(Transaction** transactions)
{
    // Display the transactions
    cout << "List of Transactions:\n";
    for (int i = 0; transactions[i] != nullptr; ++i)
    {
        transactions[i]->PrintTransaction();
        cout << endl;
    }

    // Display the total number of transactions
    int totalTransactions = TransactionLog::GetTransactionLog()->GetNumberOfTransactions();
    cout << "Total number of transactions: " << totalTransactions << endl;
}


// Assuming you have a PrintTransaction method in the Transaction class
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
        cout << "-----------------------\n";
    }
}



void Menu::EditTransaction()
{
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Display transactions for user to choose from
    cout << "Choose a transaction to edit:\n";

    // Display transactions
    displayTransactionsList(transactionLog->GetListOfTransactions());

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
                 "2. Note\n";

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
        default:
            cout << "Invalid choice. No changes made.\n";
            return;
    }

    

    cout << "Transaction edited successfully!\n";
}


void Menu::DeleteTransaction()
{
    /*
    TransactionLog* transactionLog = TransactionLog::GetTransactionLog();

    // Display transactions for user to choose from
    cout << "Choose a transaction to delete:\n";

    // Display transactions
    displayTransactionsList(transactionLog->GetListOfTransactions());

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
        bool success = transactionLog->DeleteTransaction(transactionID);

        if (success)
        {
            cout << "Transaction deleted successfully.\n";
        }
        else
        {
            cout << "Failed to delete transaction.\n";
        }
    }
    else
    {
        cout << "Transaction deletion cancelled.\n";
    }
    */
}


void Menu::ViewCategories()
{
    // Get the list of categories from CategoryLog
    std::list<Category*> categories = CategoryLog::GetCategoryLog()->GetListOfCategories();

    if (categories.empty()) {
        std::cout << "No categories available.\n";
        return;
    }

    std::cout << "Available Categories:\n";
    for (Category* categoryPtr : CategoryLog::GetCategoryLog()->GetListOfCategories()) {
        Category& category = *categoryPtr;
 
        if (categoryPtr) {
            // Using GetName and GetBudget methods to retrieve category information
            std::cout << "Name: " << categoryPtr->GetName() << ", Transaction Type: " << categoryPtr->GetTransactionType() << ", Budget: " << categoryPtr->GetBudget() << "\n";
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

    std::cout << "Enter the name of the new category: ";
    std::cin >> name;

    std::cout << "Select the transaction type (0 for EXPENSE, 1 for INCOME, ...): ";
    std::cin >> typeInput;



    // Clear the newline character left in the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (typeInput == 0) {
        type = TransactionType::expense;
    }
    else if (typeInput == 1) {
        type = TransactionType::income;
    }
    else {
        std::cout << "Invalid transaction type selected. Aborting operation.\n";
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
        std::cout << "Budget set for " << category.GetName() << ": LKR" << budget << std::endl;
    }
    

}

void Menu::PrintBudgetStatus()
{
    for (Category* categoryPtr : CategoryLog::GetCategoryLog()->GetListOfCategories()) {
        Category& category = *categoryPtr;
        std::cout << "Budget set for " << category.GetName() << ": LKR" << category.GetBudget() << std::endl;
    }

}
