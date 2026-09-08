#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib/json.hpp"

using json = nlohmann::json;
using namespace std;

string strUpper(string str) {
    string upper;

    for (int i = 0; i < str.length(); i++){
        upper += toupper(str[i]);
    }
    return upper;
}

string strLower(string str) {
    string lower;

    for (int i = 0; i < str.length(); i++){
        lower += tolower(str[i]);
    }
    return lower;
}

class Currency{
    private:
        json currencyData;

    public:
        string CurrentNamesArray[150];

    public:
        Currency(){
            string fileContent, line;

            ifstream file1("data/currencies.json");
            while(getline(file1, line)){
                fileContent += line;
            }

            currencyData = json::parse(fileContent);
            fileContent = "";
            file1.close();

            ifstream file2("data/currencyNames.json");
            while(getline(file2, line)){
                fileContent += line;
            }
            file2.close();

            json CurrencyNames = json::parse(fileContent);
            int i = 0;
            for (const auto& item : CurrencyNames.items()){
                CurrentNamesArray[i] = item.key();
                i++;
            }
        }

        float getCurrencyRate(string baseCurr, string convCurr, float baseCurrValue){

            if (baseCurr == convCurr){
                return baseCurrValue;
            }

            try
            {
                return baseCurrValue * float(this->currencyData[baseCurr][convCurr]);
            }
            catch(const json::type_error e)
            {
                cout << "Key or index not found: " << e.what() << '\n';
                return -1;
            }
        }

        void printCurrencyNames(){
            for (int i=0; i < size(CurrentNamesArray); i++){
                cout << strUpper(CurrentNamesArray[i]);
                if ((i+1) % 10 == 0){
                    cout << '\n';
                }else {
                    cout << '\t';
                }
            }
            cout << '\n';
            
        }
        
        bool checkCurrencyName(string name){
            for (int i = 0; i < size(CurrentNamesArray);i++){
                if (name == CurrentNamesArray[i]){
                    return true;
                }
            }
            return false;
            
        }
    };
    
Currency CurrencyObj;


string printBaseCurrencyMenu(){
    system("clear");
    string input;
    
    CurrencyObj.printCurrencyNames();
    cout << "\nType base currency:\t";
    cin >> input;
    input = strLower(input);

    if (CurrencyObj.checkCurrencyName(input)){
        return input;
    }else {
        return printBaseCurrencyMenu();
    }
}

string printConvertedCurrencyMenu(){
    system("clear");
    string input;

    CurrencyObj.printCurrencyNames();
    cout << "Type converted currency:\t";
    cin >> input;
    input = strLower(input);

    if (CurrencyObj.checkCurrencyName(input)){
        return input;
    }else {
        return printConvertedCurrencyMenu();
    }
}

float printConversionAmount(string baseCurr, string convCurr){
    system("clear");
    float input;

    cout << "Converting " << strUpper(baseCurr) << " to " << strUpper(convCurr) << '\n';
    cout << "---------------------\n";
    cout << "\n1 " << strUpper(baseCurr) << " = " << CurrencyObj.getCurrencyRate(baseCurr, convCurr, 1) << ' ' << strUpper(convCurr) << '\n';
    cout << "\nEnter an amount in " << strUpper(baseCurr) << ": ";
    cin >> input;
    return input;
}

void saveConversion(string output){
    ofstream write;
    write.open("data/userConversions.txt", ios::app);

    write << output << '\n';

}

void printConvertedMenu(string baseCurr, string convCurr, float baseCurrVal){
    system("clear");

    string output;
    output = to_string(baseCurrVal) + ' ' + strUpper(baseCurr) + " = " + to_string(CurrencyObj.getCurrencyRate(baseCurr, convCurr, baseCurrVal)) + ' ' + strUpper(convCurr);
    cout << output;
    saveConversion(output);
    cout << "\nPress ENTER to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void printPreviousConversions(){
    ifstream oldConversions;
    oldConversions.open("data/userConversions.txt");
    system("clear");

    string line;
    while(getline(oldConversions, line)){
        cout << line << '\n';
    }

    cout << "\nPress ENTER to continue...";
    cin.ignore(1000, '\n');
    cin.get();
    

}

void printMainMenu(){
    system("clear");

    cout << "***** Welcome to currency converter! *****\n";
    cout << "------------------------------------------\n";
    cout << "1. Perform conversion\n";
    cout << "2. View previous conversions\n";
    cout << "3. Exit\n";
    cout << "------------------------------------------\n";
}

int main(){
    string baseCurr, convCurr;
    int input;
    float baseCurrVal;

    do{
        printMainMenu();
        cin >> input;

        switch (input){
        case 1:{
            baseCurr = printBaseCurrencyMenu();
            convCurr = printConvertedCurrencyMenu();
            baseCurrVal = printConversionAmount(baseCurr, convCurr);
            printConvertedMenu(baseCurr, convCurr, baseCurrVal);
            break;
        }
        case 2: {
            printPreviousConversions();
            break;
        }
        }
    } while (input != 3);

    system("clear");
    cout << "Thank you for visiting!\n";
    return 0;
}