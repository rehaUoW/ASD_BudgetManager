#include <iostream>
#include <ctime>


namespace CommonFunctions{
    void PrintDateTime (tm datetime) {
        std::cout << 1900+datetime.tm_year << "-" << 1+datetime.tm_mon << "-" << datetime.tm_mday << " " << datetime.tm_hour << ":" << datetime.tm_min;
    }
}//Prints to console like this example: 2023-01-23 17:54