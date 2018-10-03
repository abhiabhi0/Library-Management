#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp> //case insensitive compare
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include "library.h"
#include "book.h"
#include "student.h"

void Library::enter_book()
{
    char choice;
    do
    {
        Book::new_entry();
        std::cout << "Do you want to add more records? (Y/N)\n";
        std::cin >> choice;
    }while(choice == 'y' || choice == 'Y');
    fp.close();
}

void Library::enter_stu()
{
    char choice;
    do
    {
        Student::new_entry();
        std::cout << "Do you want to add more records? (Y/N)\n";
        std::cin >> choice;
    }while(choice == 'y' || choice == 'Y');
    fp.close();
}

void Library::display_book(const std::string& num)
{
    std::cout << "---------------Book Details-------------\n";
    bool exist = false;
    std::string b_num, b_name, a_name;
    fp.open("Books.dat", std::ios::in);
    while(fp >> b_num >> b_name >> a_name)
    {
        if (boost::iequals(b_num, num))
        {
            Book::show_book(b_num, b_name, a_name);
            exist = true;
        }
    }
    fp.close();

    if (!exist)
    {
        std::cerr << "Book does not exist\n";
    }
}

void Library::display_stu(const std::string& num)
{
    std::cout << "--------------Student Details-----------------\n";
    bool exist = false;
    std::string r_num, s_name, issued_b_num;
    std::string line, str;
    unsigned int tkn;
    fp.open("Students.dat", std::ios::in);
    while(std::getline(fp, line))
    {
         std::stringstream ss(line);
         ss >> r_num >> s_name >> tkn >> issued_b_num;
         std::getline(ss, str);
        if (boost::iequals(r_num, num))
        {
            Student::show_stu(r_num, s_name, tkn, issued_b_num);
            exist = true;
        }
      }
      fp.close();

      if (!exist)
      {
          std::cerr << "Student does not exist\n";
      }
}

void Library::delete_book()
{
    std::string num;
    std::cout << "Delete Book\n";
    std::cout << "Enter number of the book you want to delete : ";
    std::cin.ignore();
    std::getline(std::cin, num);
    std::cout << '\n';
    fp.open("Books.dat", std::ios::in | std::ios::out);
    std::fstream fp1;
    fp1.open("Temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);

    std::string b_num, b_name, a_name;

    while(fp >> b_num >> b_name >> a_name)
    {
        if (!boost::iequals(b_num, num))
        {
            fp1 << b_num << " " << b_name << " " << a_name << '\n';
        }
    }
    fp1.close();
    fp.close();
    std::remove("Books.dat");
    std::rename("Temp.dat", "Books.dat");
}

void Library::delete_stu(std::string& num)
{
    fp.open("Students.dat", std::ios::in | std::ios::out);
    std::fstream fp1;
    fp1.open("Temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    std::string r_num, s_name, issued_b_num;
    int tkn;
    while(fp >> r_num >> s_name >> tkn >> issued_b_num)
    {
        if (!boost::iequals(r_num, num))
        {
            fp1 << r_num << " " << s_name << " " << " " << tkn << " " << issued_b_num << '\n';
        }
    }
    fp1.close();
    fp.close();
    std::remove("Students.dat");
    std::rename("Temp.dat", "Students.dat");
}

void Library::display_all_stu()
{
    std::cout << " ---------------Students List ----------------\n";
    std::cout << "Roll No." << "\t" << "Name" << "\t\t\t" << "Book Issued" << "\t\t\t" << "Issued Book No.\n";
    Student::show_record();
    fp.close();
}

void Library::display_all_book()
{
    std::cout << "-----------------Books List------------------\n";
    std::cout << "Book No." << std::setw(50) << "Name" << std::setw(50) << "Author\n";
    Book::show_record();
}

void Library::book_issue()
{
    std::string r_num, b_num; // roll num and book num
    std::string roll_n, s_name, issued_b_num;
    std::string book_n, b_name, a_name;
    unsigned int tkn;
    std::string line, str;
    std::fstream fp1;
    bool found_stu = false;
    bool found_book = false;
    std::cout << "-----------------Book Issue--------------------\n";
    std::cout << "Enter student's roll no. : ";
    std::cin.ignore();
    std::getline(std::cin, r_num);
    std::cout << '\n';
    fp.open("Students.dat", std::ios::in | std::ios::out);
    fp1.open("Books.dat", std::ios::in | std::ios::out);
    while (!found_stu)
    {
        int oldPos = fp.tellg();
        std::getline(fp, line);
        std::stringstream ss(line);
        ss >> roll_n >> s_name >> tkn >> issued_b_num;
        std::getline(ss, line);
        if (boost::iequals(roll_n, r_num))
        {
            found_stu = true;
            if (tkn == 0)
            {
                std::cout << "Enter Book No. : ";
                std::getline(std::cin, b_num);
                while (fp1 >> book_n >> b_name >> a_name && !found_book)
                {
                    if (boost::iequals(book_n, b_num))
                    {
                        Book::show_book(book_n, b_name, a_name);
                        found_book = true;
                        tkn = 1;
                        issued_b_num = book_n;
                        fp.seekp(oldPos);
                        fp << roll_n << " " << s_name << " " << tkn << " " << issued_b_num << '\n';
                        std::cout << "Book Issued Successfully\n";
                        break;
                    }
                }
                if (!found_book)
                {
                    std::cerr << "Book does not exist\n";
                }
            }
        }
    }
    if (!found_stu)
    {
        std::cout << "Student record does not exist\n";
    }
    fp.close();
    fp1.close();
}

void Library::book_deposit()
{
    std::string r_num, b_num; // roll num and book num
    std::string roll_n, s_name, issued_b_num;
    std::string book_n, b_name, a_name;
    unsigned int tkn;
    std::string line, str;
    std::fstream fp1;
    int days, fine;
    bool found_stu = false;
    bool found_book = false;
    std::cout << "-----------------Book Deposit---------------------\n";
    std::cout << "Enter student's roll no. : ";
    std::cin.ignore();
    std::getline(std::cin, r_num);
    std::cout << '\n';
    fp.open("Students.dat", std::ios::in | std::ios::out);
    fp1.open("Books.dat", std::ios::in | std::ios::out);

    while (!found_stu)
    {
        int oldPos = fp.tellg();
        std::getline(fp, line);
        std::stringstream ss(line);
        ss >> roll_n >> s_name >> tkn >> issued_b_num;
        std::cout << "IBN " << issued_b_num << '\n';
        std::getline(ss, line);
        if (boost::iequals(roll_n, r_num))
        {
            found_stu = true;
            if (tkn == 1)
            {
                while (fp1 >> book_n >> b_name >> a_name && !found_book)
                {
                    if (boost::iequals(book_n, issued_b_num))
                    {
                        Book::show_book(book_n, b_name, a_name);
                        found_book = true;
                        std::cout << "Book deposited in no. of days : ";
                        std::cin >> days;
                        if (days > 15)
                        {
                            fine = days - 15;
                            std::cout << "Fine has to be deposited : " << fine << '\n';
                        }
                        tkn = 0;
                        issued_b_num = "No  ";
                        fp.seekp(oldPos);
                        fp << roll_n << " " << s_name << " " << tkn << " " << issued_b_num << '\n';
                        std::cout << "Book Deposited Successfully\n";
                    }
                }
                if (!found_book)
                {
                    std::cerr << "Book does not exist\n";
                }
            }
        }
    }
    if (!found_stu)
    {
        std::cout << "Student record does not exist\n";
    }
    fp.close();
    fp1.close();
}

void Library::menu()
{
    int choice;
    std::cout << "Menu\n";
    std::cout << "1. Create Student Record\n";
    std::cout << "2. Display all Students Record\n";
    std::cout << "3. Display Specific Student Record\n";
    std::cout << "4. Delete Student Record\n";

    std::cout << "5. Enter Book Record\n";
    std::cout << "6. Display all Books\n";
    std::cout << "7. Display Specific Book\n";
    std::cout << "8. Delete Book\n";

    std::cout << "9. Back to Main Menu\n";
    std::cout << "Enter your choice\n";
    std::cin >> choice;

    switch(choice)
    {
        case 1: enter_stu();
                break;

        case 2: display_all_stu();
                break;

        case 3: {
                    std::string num;
                    std::cout << "Enter Roll No.\n";
                    std::cin.ignore();
                    std::getline(std::cin, num);
                    display_stu(num);
                }
                break;

        case 4: {
                    std::string num;
                    std::cout << "Delete Student\n";
                    std::cout << "Enter roll number of the student you want to delete : ";
                    std::cin.ignore();
                    std::getline(std::cin, num);
                    delete_stu(num);
                }
                break;

        case 5: enter_book();
                break;

        case 6: display_all_book();
                break;

        case 7: {
                    std::string num;
                    std::cout << "Enter Book No.\n";
                    std::cin.ignore();
                    std::getline(std::cin, num);
                    display_book(num);
                }
                break;

        case 8: delete_book();
                break;

        case 10: return;

        default: std::cout << "Please enter any of these choices\n";
                 break;
    }
}
