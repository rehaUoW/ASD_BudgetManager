#ifndef RECURRING_TYPE_H
#define RECURRING_TYPE_H

enum RecurringType { none, annual, monthly, weekly, daily };

#endif

// switch-case template for common use:
/*
switch (recurring)
{
case 0:
    std::cout << "none ";
    break;
case 1:
    std::cout << "annually ";
    break;
case 2:
    std::cout << "monthly ";
    break;	
case 3:
    std::cout << "weekly ";
    break;	
case 4:
    std::cout << "daily ";
    break;	
default:
    break;
}
*/