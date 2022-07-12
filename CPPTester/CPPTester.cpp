// CPPTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> from_vector(10);
    std::iota(from_vector.begin(), from_vector.end(), 0);

    std::vector<int> to_vector;
    std::copy(from_vector.begin(), from_vector.end(),
        std::back_inserter(to_vector));

    std::copy(from_vector.begin(), from_vector.end(),
        std::back_inserter(to_vector));
    // or, alternatively,
      //std::vector<int> to_vector(from_vector.size());
      std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
    // either way is equivalent to
    //to_vector = from_vector;

    std::cout << "to_vector contains: ";

    std::copy(to_vector.begin(), to_vector.end(),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
