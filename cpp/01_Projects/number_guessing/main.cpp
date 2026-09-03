#include "console.h"
#include <iostream>
#include <random>
#include <ctime>

int genRandNum(){
    int min {1};
    int max {100};

    srand(time(0));
    return rand() % (max - min + 1) + min;
}


int main(){
    int secretNumber {genRandNum()};

    int guess {};

    while (guess != secretNumber){
        guess = readInput();
        giveHint(guess, secretNumber);
        // std::cout <<secretNumber << '\n';
    }

    return 0;
}