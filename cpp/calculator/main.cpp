#include <iostream>
#include <string>

void calculatorDisplay() {
    std::cout << "Welcome to Calculator\n"
    << "Choose one operation:\n" 
    << "1. Add\n" 
    << "2. Subtract\n"
    << "3. Exit\n";
}

int addition(int a, int b){
    return a + b;
}

int subtraction(int a, int b){
    return a - b;
}


void user_input(int &a, int &b){
    std::cout << "Please provide two numbers on seperate lines:\n";
    std::cin >> a >> b;
}

std::string calculator_function(int userChoice){
    int a, b;
    if (userChoice == 1) {
        user_input(a, b);
        int output = addition(a,b);
        return "The sum is " + std::to_string(output);
    }else if (userChoice == 2){
        user_input(a, b);
        int output = subtraction(a,b);
        return "The difference is " + std::to_string(output);
    }else{
        return "Exiting...";
    }
}

int main() {
    while (true){
        
        calculatorDisplay();
        int userChoice {};
        std::cin >> userChoice;

        std::string result = calculator_function(userChoice);
        std::cout << result << '\n';

        if (result == "Exiting..."){
            break;
        }
    }
    



    return 0;
}