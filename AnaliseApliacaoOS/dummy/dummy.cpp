// just for research porpouse
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdarg> // for variable argument lists

int main()
{
    std::shared_ptr<void()> ee(); // safe pointer from std::memory

    // arrays
    int x;
    int y;
    int array[8][8]; // Declares an array like a chessboard

    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
            array[x][y] = x * y; // Set each element to a value
    }

    // really simple in out manipulation
    char string[256];

    std::cout << "Please enter a long string: ";
    std::cin.getline(string, 256, '\n');
    std::cout << "Your long string was: " << string << std::endl;
    std::cin.get();

    // file read
    std::ifstream fin("text.txt");
    std::string line;
    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        std::vector<char> row;
        char c;
        while (iss >> c)
        {
            row.push_back(c);
        }
    }
    fin.close();

    // argument lists
    // this computes the average of 13.2, 22.3 and 4.5 (3 indicates the number of values to average)
    std::cout << average(3, 12.2, 22.3, 4.5) << std::endl;
    std::cout << average(5, 3.3, 2.2, 1.1, 5.5, 3.3) << std::endl;
}

double average(int num, ...)
{
    va_list arguments; // A place to store the list of arguments
    double sum = 0;

    va_start(arguments, num);             // Initializing arguments to store all values after num
    for (int x = 0; x < num; x++)         // Loop until all numbers are added
        sum += va_arg(arguments, double); // Adds the next value in argument list to sum.
    va_end(arguments);                    // Cleans up the list

    return sum / num;
}