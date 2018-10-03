#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "student.h"

namespace Student
{
    std::string roll_num;
    std::string stu_name;
    std::string issued_book_num;
    unsigned int token;

    void new_entry()
    {
        std::cin.ignore();
        std::cout << "Enter Roll Number : ";
        std::getline(std::cin, roll_num);
        std::cout << "\nEnter Student Name : ";
        std::getline(std::cin, stu_name);
        token = 0;
        issued_book_num = "No  ";

        std::fstream fp;
        fp.open("Students.dat", std::ios::out | std::ios::app);
        if (fp)
        {
            fp << roll_num << " " << stu_name << " " << token << " " << issued_book_num << '\n';
        }
        fp.close();
        std::cout << "Entry Successfull!!\n";
    }

    void show_stu(std::string& r_num, std::string& s_name, unsigned int tkn, std::string& issued_b_num)
    {
        std::cout << "Roll Number : " << std::setw(10) << r_num << '\n';
        std::cout << "Student Name :" << std::setw(10) << s_name << '\n';
        std::cout << "Books issued :" << std::setw(10) << tkn << '\n';
        if (tkn == 1)
        {
            std::cout << "Book Number :" << std::setw(10) << issued_b_num << '\n';
        }
        std::cout << '\n';
    }

    void show_record()
    {
        std::fstream fp;
        std::string record;
        fp.open("Students.dat", std::ios::in);
        if (!fp)
        {
            std::cerr << "File could not be opened\n";
            return;
        }
        else
        {
            std::string line;
            while (std::getline(fp, line))
            {
                std::stringstream ss(line);
                ss >> roll_num >> stu_name >> token >> issued_book_num;
                std::getline(ss, line);
                if (fp.eof())
                {
                    break;
                }
                else
                {
                    std::cout << roll_num << "\t" << stu_name << "\t\t\t" << token << "\t\t\t" << issued_book_num << '\n';
                }
            }
        }
        fp.close();
    }
}
