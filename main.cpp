#include <iostream>
#include <stdlib.h>
#include "library.h"

int main()
{
    Library lib;
    char choice;
    do
    {
        std::cout << "1. Book Issue\n";
        std::cout << "2. Book Deposit\n";
        std::cout << "3. Menu\n";
        std::cout << "4. Exit\n";

        std::cout << "Enter your option\n";
        std::cin >> choice;
        switch(choice)
        {
            case '1': lib.book_issue();
                      break;

            case '2': lib.book_deposit();
                      break;

            case '3': lib.menu();
                      break;

            case '4': exit(0) ;

            default: std::cout << "Enter one of these choice\n";
        }
    } while(choice != '4');

}
