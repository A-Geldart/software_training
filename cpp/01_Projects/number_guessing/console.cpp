#include "console.h"

int readInput(){

    std::cout << "Please provide a number: \n";
    int guess {};
    std::cin >> guess;
    return guess;
}

void giveHint(int guess, int secretNumber){
    const int farThreshold {10};
    const int closeThreshold {5};
    if (guess == secretNumber){
        std::cout << "You got it!\n";
    } else if (abs(guess - secretNumber) < closeThreshold){
        std::cout << "Very Hot\n";
    } else if (abs(guess - secretNumber) < farThreshold) {
        std::cout << "Hot\n";
    } else{
        std::cout << "cold\n";
    }
}