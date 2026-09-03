#include<iostream>
#include <limits> // Required for std::numeric_limits
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;


void clearInputBuffer() {
    cin.clear(); // Resets error flags so cin can read again
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the buffer
}

class Product{
    private:
        int ID;
        string name;
        string category;
        double price;
        int quantity;

    public:
        Product(int ID, string name, string category, double price, int quantity){
            this->ID = ID;
            this->name = name;
            this->category = category;
            this->price = price;
            this->quantity = quantity;
        }
        int getID() const{
            return ID;
        }
        void setID(int newID){
            if (newID > 0){
                this->ID = newID;
            }
        }
        string getName() const{
            return name;
        }
        void setName(string newName){
            this->name = newName;
        }
        string getCategory() const{
            return category;
        }
        void setCategory(string newCategory){
            this->category = newCategory;
        }
        double getPrice() const{
            return price;
        }
        void setPrice(double newPrice){
            if (newPrice > 0.00){
                this->price = newPrice;
            }
        }
        int getQuantity() const{
            return quantity;
        }
        void setQuantity(int newQuantity){
            if (newQuantity >= 0){
                this->quantity = newQuantity;
            }
        }
};

class Inventory{
    private:
        vector<Product> products;

    public:
        void add(Product product){
            bool found = false;

            for (auto& p : products){
                if (p.getID() == product.getID()){
                    cout << "\n---------- Product already exists ----------\n";
                    found = true;
                    break;
                }
            }

            if (!found){
                products.push_back(product);
                cout << "\n-------- Added product to inventory --------\n";

            }

        }
        void remove(int ID){
            bool found = false;

            for (auto i = products.begin(); i != products.end(); i++){
                if (i->getID() == ID){
                    products.erase(i);
                    cout << "\n------------- Product removed! -------------\n";
                    found = true;
                }
            }

            if (!found){
                cout << "\n---------- Product does not exist ----------\n";
            }
        }
        Product* find(int ID){
            for (auto i = products.begin(); i != products.end(); i++){
                if (i->getID() == ID){
                    return &(*i);
                }
            }

            return nullptr;

        }
        void update(int ID, string name, string category, double price, int quantity){
            bool found = false;

            for (auto i = products.begin(); i != products.end(); i++){
                if (i->getID() == ID){
                    i->setName(name);
                    i->setCategory(category);
                    i->setPrice(price);
                    i->setQuantity(quantity);
                    found = true;
                    break;
                }
            }

            if (!found){
                cout << "\n------------ ID does not exist! ------------\n";
            }
        }
        void view() const{
            for (auto i = products.begin(); i != products.end(); i++){
                cout << "ID: " << i->getID() << '\n';
                cout << "Name: " << i->getName() << '\n';
                cout << "Category: " << i->getCategory() << '\n';
                cout << "Price: $" << i->getPrice() << '\n';
                cout << "Quantity: " << i->getQuantity() << '\n';
            }

        }
        void saveToFile(string fileName){
            ofstream write;
            write.open(fileName);

            for (int i =0; i < products.size(); i++){
                Product p = products[i];
                write << p.getID() << ',' << p.getName() << ',' << p.getCategory() << ',' << p.getPrice() << ',' << p.getQuantity() << endl;
            }
            write.close();
        }
        void loadFromFile(string fileName){
            ifstream read;
            read.open(fileName);
            string line;

            if (read.is_open()){
                while (getline(read, line)){
                    stringstream ss(line);
                    string idStr, name, category, priceStr, quantityStr;
    
                    getline(ss, idStr, ',');
                    getline(ss, name, ',');
                    getline(ss, category, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, quantityStr, ',');
    
                    int ID = stoi(idStr);
                    double price = stod(priceStr);
                    int quantity = stoi(quantityStr);
    
                    Product p(ID, name, category, price, quantity);
                    products.push_back(p);
                    read.close();
                }

            }else {
                cout << "Could not open file: " << fileName << '\n';
            }

            
        }
};

void printOptions(){
    cout << '\n';
    cout << "--------------------------------------------\n";
    cout << "--------- Inventory Manager System ---------\n";
    cout << "--------------------------------------------\n";
    cout << "Please choose an option:\n\n";
    cout << "\t1. Add a product\n";
    cout << "\t2. Remove a product\n";
    cout << "\t3. Find a product\n";
    cout << "\t4. Update a product\n";
    cout << "\t5. View current products\n";
    cout << "\t6. Save Invetory to a file\n";
    cout << "\t7. Load invetory from a file\n";
    cout << "\t8. Exit\n";
    cout << "--------------------------------------------\n";
    cout << '\n';
}

int main() {
    int choice;
    Inventory inventory;
    
    do {
        printOptions();
        std::cin >> choice;
        switch(choice){
            case 1: {
                int ID;
                string name, category;
                double price;
                int quantity;

                cout << "Please enter the product information:\n";
                cout << "ID:  ";
                cin >> ID;
                cout << "Name:  ";
                cin >> name;
                cout << "Category:  ";
                cin >> category;
                cout << "Price ($):  ";
                cin >> price;
                cout << "Quantity:  ";
                cin >> quantity;
                Product product(ID, name, category, price, quantity);
                inventory.add(product);
                break;
            }
            case 2:{
                int ID;
                cout << "Please enter product ID:";
                cin >> ID;
                inventory.remove(ID);
                break;
            }
            case 3:{
                int ID;
                cout << "Please enter product ID:";
                cin >> ID;
                Product* product = inventory.find(ID);

                if (product){
                    cout << "ID: " << product->getID() << '\n';
                    cout << "Name: " << product->getName() << '\n';
                    cout << "Category: " << product->getCategory() << '\n';
                    cout << "Price: $" << product->getPrice() << '\n';
                    cout << "Quantity: " << product->getQuantity() << '\n';
                    cout << "--------------------------------------------\n";
                }else {
                    cout << "----------- Product not found! -------------\n";
                }

                break;
            }
            case 4:{
                int ID;
                string name, category;
                double price;
                int quantity;

                cout << "Please enter the product information:\n";
                cout << "ID:  ";
                cin >> ID;
                cout << "Name:  ";
                cin >> name;
                cout << "Category:  ";
                cin >> category;
                cout << "Price ($):  ";
                cin >> price;
                cout << "Quantity:  ";
                cin >> quantity;

                inventory.update(ID, name, category, price, quantity);
                break;
            }
            case 5:{
                inventory.view();
                break;
            }
            case 6:{
                inventory.saveToFile("inventory.csv");
                break;
            }
            case 7:{
                inventory.loadFromFile("inventory.csv");
                break;
            }
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option\n";
                clearInputBuffer();
                break;
        }

    }while(choice != 8);

}