#include "io.h"
#include <iostream>



int readNumber() {

    std::cout << "Please provide a number: ";
    int num {};
    std::cin >> num;
    return num;
}

void writeAnswer(int number) {

    std::cout << "Your answer is: " << number << '\n';
}