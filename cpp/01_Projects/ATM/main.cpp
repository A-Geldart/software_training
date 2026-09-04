#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>

class Account{
    private:
        std::string name;
        std::string mobile;
        double balance;

    public:
    Account(std::string name, std::string mobile, double balance){
            this->name = name;
            this->mobile = mobile;
            this->balance = balance;
        }

        //Getters
        std::string getName() const{
            return name;
        }
        std::string getMobile() const{
            return mobile;
        }
        double getBalance() const{
            return balance;
        }

        //Setters
        void setName(std::string name){
            this->name = name;

        }
        void setMobile(std::string mobile){
            if (mobile.size() != 10){
                std::cout << "Enter 9 digits without spaces for valid number\n";
            }else{
                this->mobile = mobile;
            }

        }
        void setBalance(double balance){

        }
        void deposit(double deposit){
            if (deposit <= 0.00){
                std::cout << "Nothing to deposit\n";
            }else{
                this->balance += deposit;
            }

        }
        void withdraw(double withdraw){
            if ((withdraw > balance) or (withdraw <= 0.00)){
                std::cout << "Insufficient funds\n";
            }else{
                this->balance -= withdraw;
            }

        } 
        
};

void clearInputBuffer();
void userOptions();
Account generateTestUser();

int main(){
    char choice;
    Account user = generateTestUser();

    do{
        userOptions();
        
        std::cin >> choice;
        
        switch(choice){
            case '1':{
                std::cout << "Your balance is: $" << std::fixed << std::setprecision(2) << user.getBalance() << '\n';
                break;
                
            }
            case '2':{
                std::cout << "Please enter an amount to withdraw: $";
                double amount;
                std::cin >> amount;
                user.withdraw(amount);
                std::cout << "Your new balance is: $" << std::fixed << std::setprecision(2) << user.getBalance() << '\n';
                break;
            }
            case '3':{
                std::cout << "Please enter an amount to deposit: $";
                double amount;
                std::cin >> amount;
                user.deposit(amount);
                std::cout << "Your new balance is: $" << std::fixed << std::setprecision(2) << user.getBalance() << '\n';
                break;
            }
            case '4':{
                std::cout << "Account Name: " << user.getName() << '\n';
                std::cout << "Mobile Number: " << user.getMobile() << '\n';
                break;
            }
            case '5':{
                std::cout << "What is the new mobile number?: ";
                std::string mobile;
                std::cin >> mobile;
                user.setMobile(mobile);
                break;
            }
        }
        clearInputBuffer();

    }while(std::toupper(choice) != 'Q');

    return 0;
}

void userOptions(){
    std::cout << "------------------------------------------\n";
    std::cout << "|---------- WELCOME TO THE ATM ----------|\n";
    std::cout << "|----------------------------------------|\n";
    std::cout << "|  1. Check Balance                      |\n";
    std::cout << "|  2. Withdraw Money                     |\n";
    std::cout << "|  3. Deposit Money                      |\n";
    std::cout << "|  4. Check Details                      |\n";
    std::cout << "|  5. Update Mobile Number               |\n";
    std::cout << "|  Q. Quit                               |\n";
    std::cout << "------------------------------------------\n";
}

Account generateTestUser(){
    Account testUser("Daniel LaRusso", "0415678142", 5000.00);
    return testUser;
}

void clearInputBuffer() {
    std::cin.clear(); // Resets error flags so cin can read again
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the buffer
}