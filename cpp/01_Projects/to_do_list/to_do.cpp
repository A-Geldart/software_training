#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

int ID;

struct todo {
    int id;
    string task;
    string due;
};

void add_task(){
    todo list;
    cout << "Enter your new task: ";
    cin.get();
    getline(cin, list.task);

    cout << "Enter a due date (DD/MM): ";
    cin >> list.due;
    ID++;

    //Write task to todo.txt file
    ofstream write;
    write.open("todo.txt", ios::app);
    write << "\n" << ID << '\t' << list.due << '\t' << list.task;
    write.close();

    write.open("id.txt");
    write << ID;
    write.close();

    char ch;
    cout << "Do you want to add another task? y/n\t" ;
    cin >> ch;

    if (ch == 'y'){
        add_task();
    } else {
        cout << "Returning to main menu...\n";
    }
}

void update_task(){
    cout << "Update task\n";
}

int search_list(){
    int id;
    cout << "Please enter a task ID:\t";
    cin >> id;

    todo list;
    ifstream read;
    read.open("todo.txt");

    while (! read.eof()){
        read >> list.id;
        read.ignore();
        getline(read, list.task);

        if (list.id == id){
            cout << "Task: " << list.task << '\n';
            return id;
        }
    }
}

void delete_task(){
    int id {search_list()};
    char ch;

    cout << "Do you want to delete this task? y/n\t";
    cin >> ch;

    if (ch == 'y') {
        todo list;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");

        while (! read.eof()){
            read >> list.id;
            read.ignore();
            getline(read, list.task);
            if (list.id != id){
                tempFile << "\n" << list.id;
                tempFile << "\n" << list.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "Done!\n";

    } else {
        cout << "Returning to main menu...\n";
    }
}

void view_tasks(){
    todo list;
    ifstream read;
    read.open("todo.txt");
    cout << "\t\t\t-------------CURRENT  TASKS-------------"<<endl;

    while (!read.eof()){
        read >> list.id;
        read.ignore();
        getline(read, list.task);
        cout << list.id <<": " << list.task << '\n';
    }
    read.close();
}

void user_options(){  
    cout <<"\t1. Add a new task"<<endl;
    cout <<"\t2. Update a task"<<endl;
    cout <<"\t3. View tasks"<<endl;
    cout <<"\t4. Delete a task"<<endl;
    cout <<"\t5. Quit"<<endl;
}

int main(){
    cout <<"\t\t\t****************************************"<<endl;
    cout <<"\t\t\t*                                      *"<<endl;
    cout <<"\t\t\t*     WELCOME TO YOUR TASK MANAGER     *"<<endl;
    cout <<"\t\t\t*                                      *"<<endl;
    cout <<"\t\t\t****************************************"<<endl;
    user_options();

    ifstream read;
    read.open("id.txt");
    if (!read.fail()){
        read >> ID;
    } else {
        ID = 0;
    }
    read.close();

    while (true){
        cout << "Please choose an option or enter '0' to show options again\n";
        
        int choice {};
        cin >> choice;

        switch (choice){
            case 1:
                add_task();
                break;

            case 2:
                update_task();
                break;

            case 3:
                view_tasks();
                break;
            
            case 4:
                delete_task();
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid option.\n";
                user_options();
                break;
        }
        
    }
    return 0;
}