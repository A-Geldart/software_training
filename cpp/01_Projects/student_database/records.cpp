#include <iostream>
#include <string>
#include "file_handler.h"

using namespace std;

struct record{
    int ID;
    string FirstName;
    string Surname;
    string Email;
    string DOB;
    string Degree;
    string Score;
};

int ID;

string generate_student_email(string first, string last){
    string email;
    
    email += char(tolower(first[0]));
    email += '.';
    email += char(tolower(last[0]));
    email += last.substr(1,last.size());
    email += "@galatic.com";

    return email;
}

void add_student(){
    record student;
    
    //Get student info
    cout << "Enter students name:\t";
    cin >> student.FirstName >> student.Surname;

    student.Email = generate_student_email(student.FirstName, student.Surname);
    
    cout << "Enter student DOB (DD/MM/YYYY):\t";
    cin >> student.DOB;

    cout << "Enter student degree:\t";
    cin.get();
    getline(cin, student.Degree);
    ID++;

    student.Score = "N/A";

    string studentData = student.Surname + 
                            ',' + student.FirstName +
                            ',' + student.DOB +
                            ',' + student.Email +
                            ',' + student.Degree +
                            ',' + student.Score;

    add_record(studentData, ID);
    cout << "Record added!\n";
}

void homescreen(){
    cout << "-----------------------------------Student Records-----------------------------------\n";
    cout << "\t1. Add a new student\n";
    cout << "\t2. View records\n";
    cout << "\t3. Search student by name\n";
    cout << "\t4. Search student by ID\n";
    cout << "\t5. Update record\n";
    cout << "\t6. Statistics\n";
    cout << "\t9. Delete record\n";
    cout << "\t0. Quit\n";
}

void testing_debug(){
    string student1 { "Fett,Boba,80,example@gmail.com,Bounty Hunter,80" };
    string student2 { "Fett,Jango,80,example@gmail.com,Bounty Hunter,100" };
    string student3 { "Kenobi,Obi-Wan,80,example@gmail.com,Master,99" };
    string student4 { "Organa,Leia,80,example@gmail.com,General,90" };
    string student5 { "Bane,Cad,80,example@gmail.com,Bounty Hunter,99" };

    add_record(student1, 1);
    add_record(student2, 2);
    add_record(student3, 3);
    add_record(student4, 4);
    add_record(student5, 5);

}

int main() {
    create_record_file();

   int ID { check_ID() };
   int choice;

   while (true) {
        homescreen();
        cin >> choice;

        switch (choice) {
            case -1: {
                testing_debug();
                break;
            }
            case 0: {
                return 0;
            }
            case 1: {
                add_student();
                break;
            }
            case 2: {
                view_records();
                break;
            }
            case 3: {
                search_by_name();
                break;
            }
            case 4: {
                search_by_ID();
                break;
            }
            case 5: {
                update_record();
                break;
            }
            case 6: {
                display_statistics();
                break;
            }
            case 9: {
                delete_record();
                break;
            }
            default: {
                cout << "Invalid input\n";
                homescreen();
                break;
            }
        }
    }
    return 0;
}