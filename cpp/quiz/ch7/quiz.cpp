#include <iostream>

int getInteger(){
    //value is in scope here
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;
    return value;
} //value is destroyed here


int main(){
    std::cout << "Provide a smaller number, then a lrger number.\n";
    
    //smaller an larger goes in scope here
    int smaller { getInteger() };
    int larger { getInteger() };

    if (smaller > larger) {
        //temp is in scope here
        int temp {smaller};
        smaller = larger;
        larger = temp;
        std::cout << "Swapping the values\n";
    }  //temp is destoryed here


    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The larger value is " << larger << '\n';
    return 0;
} //smaller and larger are destroyed here