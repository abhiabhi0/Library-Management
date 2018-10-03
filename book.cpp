#include <iostream>
#include <iomanip>
#include <fstream>
#include "book.h"

namespace Book
{
    std::string book_num, book_name, author_name;
    void new_entry()
    {
        std::cin.ignore();
        std::cout << "Enter Book Number : ";
        std::getline(std::cin, book_num);
        std::cout << "\nEnter Book Name : ";
        std::getline(std::cin, book_name);
        std::cout << "\nEnter Author Name : ";
        std::getline(std::cin, author_name);

        std::fstream fp;
        fp.open("Books.dat", std::ios::out | std::ios::app);
        if (fp)
        {
            fp << book_num << " " << book_name << " " << author_name << '\n';
        }
        fp.close();
        std::cout << "Entry Successfull!!\n";
    }

      void show_book(std::string& b_num, std::string& b_name, std::string& a_name)
      {
          std::cout << "Book Number :" << std::setw(10) << b_num << '\n';
          std::cout << "Book Name :  " << std::setw(10) << b_name << '\n';
          std::cout << "Author Name :" << std::setw(10) << a_name << '\n';
      }

      void show_record()
      {
          std::fstream fp;
          std::string record;
          fp.open("Books.dat", std::ios::in);
          if (!fp)
          {
              std::cerr << "File could not be opened\n";
              return;
          }
          else
          {
              while (fp >> book_num >> book_name >> author_name)
              {
                  if (fp.eof())
                  {
                      break;
                  }
                  else
                  {
                      std::cout << book_num << std::setw(50) << book_name << std::setw(50) << author_name << '\n';
                  }
              }
          }
          fp.close();
      }
}
