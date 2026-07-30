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


int main() {
    int num1 { readNumber() };
    int num2 { readNumber() };

    writeAnswer(num1 + num2);

    return 0;
}