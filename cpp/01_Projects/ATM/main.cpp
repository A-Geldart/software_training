#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <unistd.h> //For linux; For Windows: windows.h

class ATM{
    private:
        long int account_No;
        std::string name;
        int pin;
        double balance;
        std::string mobile_No;
        std::vector<std::string> transactionHistory;
        bool isLocked = false;
        int pinAttemps = 0;

    public:
    ATM(long int account_No, std::string name, int pin, double balance){
        this->account_No = account_No;
        this->name = name;
        this->pin = pin;
        this->balance = balance;
    }

    long int getAccountNo() { return account_No; }
    std::string getName() { return name; }
    int getPin() { return pin; }
    double getBalance() { return balance; }
    std::string getMobile() { return mobile_No; }
    std::vector<std::string> getTransactionHistory() { return transactionHistory; }
    bool getLockStatus() { return isLocked; }

    void withdrawMoney(double amount){
        std::string transaction = "Withdrew:\t$" + std::to_string(amount);
        if (amount > balance){
            std::cout << " ________________________________________\n";
            std::cout << "|*****      INSUFFICIENT FUNDS      *****|\n";
            std::cout << "|________________________________________|\n";
        }else if (amount <= 0.00){
            std::cout << " ________________________________________\n";
            std::cout << "|*****        INVALID AMOUNT        *****|\n";
            std::cout << "|________________________________________|\n";
        }else {
            this->balance -= amount;
            transactionHistory.push_back(transaction);
        }
    }

    void depositMoney(double amount) {
        std::string transaction = "Deposited:\t$" + std::to_string(amount);
        if (amount <= 0.00){
            std::cout << " ________________________________________\n";
            std::cout << "|*****        INVALID AMOUNT        *****|\n";
            std::cout << "|________________________________________|\n";
        }else {
            this->balance += amount;
            transactionHistory.push_back(transaction);
        }

    }

    void lockAccount(){
        isLocked = true;
        std::cout << " _______________________________________\n";
        std::cout << "|**********  ACCOUNT  LOCKED  **********|\n";
        std::cout << "|_______________________________________|\n";
    }

    void trackLoginAttempts(){
        pinAttemps++;

        if (pinAttemps >= 3){
            lockAccount();
        }

    }
    void resetAccLock() {
        isLocked = false;
    }
    void resetPinAttempts(){
        pinAttemps = 0;
    }
    void setMobileNo(std::string oldNumber, std::string newNumber){
        if (mobile_No.empty()){
            mobile_No = newNumber;
        }else if ((oldNumber == mobile_No) && (newNumber.size() >=10)){
            mobile_No = newNumber;
        }else {
            std::cout << " ________________________________________\n";
            std::cout << "|*****   OLD NUMBER DOESN'T MATCH   *****|\n";
            std::cout << "|________________________________________|\n";
        }
        
    }
};

void clearInputBuffer();
void userOptions();
ATM generateTestUser();

int main(){
    system("clear");
    ATM user1 = generateTestUser();
    
    char choice;
    int enterPin;
    long int enterAccNo;
    bool testvar = true;
    
    std::cout << " ________________________________________\n";
    std::cout << "|                                        |\n";
    std::cout << "|********** WELCOME TO THE ATM **********|\n";
    std::cout << "|________________________________________|\n";
    std::cout << "|  Please enter your account number: ";
    std::cin >> enterAccNo;
    
    do {
        std::cout << "|  Please enter your PIN: ";
        std::cin >> enterPin;

        if ((enterAccNo == user1.getAccountNo()) && (enterPin == user1.getPin())){
            user1.resetPinAttempts();
            system("clear");
            
            do {
                if (user1.getLockStatus()){
                    break;
                }

                userOptions();
                std::cin >> choice;
                system("clear");

                switch(std::toupper(choice)){
                    case '1': {
                        std::cout << "|  Your current balance is: $" << std::fixed << std::setprecision(2) << user1.getBalance() << '\n';
                        break;
                    }
                    case '2': {
                        double amount;
                        std::cout << "|  Please enter an amount to withdraw: $";
                        std::cin >> amount;
                        user1.withdrawMoney(amount);
                        std::cout << "|  Your new balance is: $" << std::fixed << std::setprecision(2) << user1.getBalance() << '\n';
                        break;
                    }
                    case '3': {
                        double amount;
                        std::cout << "| Please enter an amount to deposit: $";
                        std::cin >> amount;
                        user1.depositMoney(amount);
                        std::cout << "|  Your current balance is: $" << std::fixed << std::setprecision(2) << user1.getBalance() << '\n';
                        break;
                        
                    }
                    case '4': {
                        std::cout << " _______________________________________\n";
                        std::cout << "|*****       ACCOUNT DETAILS       *****\n";
                        std::cout << "|  ACC: " << user1.getAccountNo() << '\n';
                        std::cout << "|  Name: " << user1.getName() << '\n';
                        std::cout << "|  Balance: $" << std::fixed << std::setprecision(2) << user1.getBalance() << '\n';
                        std::cout << "|  Mobile: " << user1.getMobile() << '\n';
                        std::cout << "|_______________________________________\n";
                        break;

                    }
                    case '5': {
                        std::string oldMobile, newMobile;                        std::cout << "update mobile\n";
                        std::cout << "|  Please enter your old number: ";
                        std::cin >> oldMobile;
                        std::cout << "|  Please enter your new number: ";
                        std::cin >> newMobile;
                        user1.setMobileNo(oldMobile, newMobile);
                        std::cout << "|*****        New Number Set        *****|\n";
                        break;
                    }
                    case '6': {
                        std::vector<std::string> transactions = user1.getTransactionHistory();
                        std::cout << " ________________________________________\n";
                        std::cout << "|*****     TRANSACTION  HISTORY     *****|\n";

                        for (const std::string& transaction : transactions){
                            std::cout << "|  " << transaction << '\n';
                        }
                        break;
                    }
                    case '7': {
                        user1.lockAccount();
                        break;
                    }
                    case 'Q': {
                            std::cout << " ________________________________________\n";
                            std::cout << "|                                        |\n";
                            std::cout << "|********** THANK YOU, GOODBYE **********|\n";
                            std::cout << "|________________________________________|\n";
                            return 0;
                    }

                }

            }while(true);
            
        }else{
            user1.trackLoginAttempts();

            if (user1.getLockStatus()){
                char retryLogin;
                std::cout << "|  Would you like to try again? y/n: ";
                std::cin >> retryLogin;

                if (std::tolower(retryLogin) == 'y'){
                    std::cout << "|  Please wait 10sec\n";
                    sleep(10);
                    user1.resetAccLock();
                    continue;
                }else{
                    break;
                }
            }            
        }
    }while(true);   
    return 0;
}

void userOptions(){
    std::cout << " ________________________________________\n";
    std::cout << "|                                        |\n";
    std::cout << "|********** WELCOME TO THE ATM **********|\n";
    std::cout << "|________________________________________|\n";
    std::cout << "|                                        |\n";
    std::cout << "|  1. Check Balance                      |\n";
    std::cout << "|  2. Withdraw Money                     |\n";
    std::cout << "|  3. Deposit Money                      |\n";
    std::cout << "|  4. Check Details                      |\n";
    std::cout << "|  5. Update Mobile Number               |\n";
    std::cout << "|  6. Transaction History                |\n";
    std::cout << "|  7. Lock Account (Safety Precaution)   |\n";
    std::cout << "|  Q. Quit                               |\n";
    std::cout << "|________________________________________|\n";
}

ATM generateTestUser(){
    ATM testUser(123456789, "Daniel LaRusso", 1234, 5000.00);
    return testUser;
}

void clearInputBuffer() {
    std::cin.clear(); // Resets error flags so cin can read again
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the buffer
}