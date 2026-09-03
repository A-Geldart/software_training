#include "file_handler.h"

std::ifstream read;
std::ofstream write;

std::string HEADER {"ID,Surname,Name,DOB,Student Email,Degree,Score (%)"};

int check_ID(){
    read.open("id.txt");
    int ID;

    if (!read.fail()){
        read >> ID;
    } else {
        ID = 0;
        write.open("id.txt");
        write << ID;
        write.close();
    }
    read.close();
    return ID;
}

void create_record_file(){
    //Add header if not in there
    read.open("records.txt");
    if (read.fail()){
        read.close();
        write.open("records.txt");
        write << HEADER;
        write.close();
    }
}

void add_record(std::string line, int ID){
    write.open("records.txt", std::ios::app); //Opening in append mode
    write << '\n' << ID << ',' << line;
    write.close();

    //Update ID
    write.open("id.txt");
    write << ID;
    write.close();
}

void view_records(){
    read.open("records.txt");
    std::cout << '\n';

    std::string line;
    
    while (std::getline(read, line)){

        std::stringstream ss(line);
        std::string dataField;
        std::vector<std::string> studentData;

        //Read through the line and seperate fields
        while (std::getline(ss, dataField, ',')){
            studentData.push_back(dataField);
        }

        //Print data in user readable format
        for (int i=0; i < studentData.size(); i++){
            std::cout << studentData[i] << '\t';
        }

        //Cleanup for next line
        std::cout << '\n';
        studentData.clear();
    }
    read.close();
}

void update_record(){
    //Choose student by ID
    int updateRecordID { search_by_ID() };
    read.open("records.txt");
    write.open("temp.txt");
    write << HEADER;

    //Init user choice variables
    char confirmUpdate;
    int updateField;
    std::string newData;

    std::cout << "Do you wish to update this record? y/n:\t";
    std::cin >> confirmUpdate;

    while (confirmUpdate == 'y'){
        std::cout << "What would you like to update?\n\t1. Degree\n\t2. Score\n";
        std::cin >> updateField;

        
        std::string line;
        std::string newLine;

        //Remove file header
        std::getline(read, line);
        
        while (std::getline(read, line)){

            std::stringstream ss(line);
            std::string dataField;
            std::vector<std::string> studentData;
            
            //Read through the line and seperate fields
            while (std::getline(ss, dataField, ',')){
                studentData.push_back(dataField);
            }
            
            if (std::stoi(studentData[0]) != updateRecordID){
                write << '\n' << line;
            }else {
                switch (updateField){
                    case 1: {
                        std::cout << "Please enter the new Degree:\t";
                        std::cin.get();
                        getline(std::cin, newData);
                        studentData[5] = newData;
                        break;
                    }
                    case 2: {
                        std::cout << "please enter the new Score:\t";
                        std::cin.get();
                        getline(std::cin, newData);
                        studentData[6] = newData;
                        break;
                    }
                }

                //Recreate the line that's updating
                newLine = studentData[1] + 
                            ',' + studentData[2] +
                            ',' + studentData[3] +
                            ',' + studentData[4] +
                            ',' + studentData[5] +
                            ',' + studentData[6];

                //Write updated line to temp file
                write << '\n' << updateRecordID << ',' << newLine;
            }

            //Cleanup for next line
            std::cout << '\n';
            studentData.clear();
        }

        std::cout << "Would you like to update anything else? y/n:\t";
        std::cin >> confirmUpdate;
    }
    read.close();
    write.close();
    remove("records.txt");
    rename("temp.txt", "records.txt");
    std::cout << "Record successfully updated!\n";
}

void delete_record(){
    int deleteID { search_by_ID() };
    char ch;

    std::cout << "Do you wish to remove this student? y/n:\t";
    std::cin >> ch;

    if (ch == 'y') {

        read.open("records.txt");
        write.open("temp.txt");
        write << HEADER;

        //Remove header
        std::string line;
        std::getline(read, line);

        while (std::getline(read, line)){
            std::stringstream ss(line);
            std::string dataField;
            std::vector<std::string> studentData;

            //Read through the line and seperate fields
            while (std::getline(ss, dataField, ',')){
                studentData.push_back(dataField);
            }

            if (std::stoi(studentData[0]) != deleteID){
                write << '\n' << line;
            }
        }
  
        read.close();
        write.close();
        remove("records.txt");
        rename("temp.txt", "records.txt");
        std::cout << "Student Record Removed!\n";
    }
}

int search_by_name(){
    read.open("records.txt");

    //Get student name
    std::cout << "Please provide the student name: ";
    std::string searchName;
    std::cin.get();
    getline(std::cin, searchName);

    std::string line;
    
    while (std::getline(read, line)){
        std::stringstream ss(line);
        std::string dataField;
        std::vector<std::string> studentData;

        //Read through the line and seperate fields
        while (std::getline(ss, dataField, ',')){
            studentData.push_back(dataField);
        }

        std::string fullName = studentData[2] + ' ' + studentData[1];

        if (searchName == fullName || searchName == studentData[1] || searchName == studentData[2]){

            //Print data in user readable format
            for (int i=0; i < studentData.size(); i++){
                std::cout << studentData[i] << '\t';
            }
            std::cout << '\n';
            read.close();
            return std::stoi(studentData[0]);
        }
    }
    std::cout << "No student found, please try another name\n";
    return 0;
}

int search_by_ID(){
    read.open("records.txt");

    //Get student ID
    std::cout << "Please provide the student ID: ";
    std::string searchID;
    std::cin >> searchID;

    std::string line;
    
    while (std::getline(read, line)){
        std::stringstream ss(line);
        std::string dataField;
        std::vector<std::string> studentData;

        //Read through the line and seperate fields
        while (std::getline(ss, dataField, ',')){
            studentData.push_back(dataField);
        }

        if (searchID == studentData[0]){

            for (int i=0; i < studentData.size(); i++){
                std::cout << studentData[i] << '\t';
            }
            std::cout << '\n';
            read.close();
            return std::stoi(studentData[0]);
        }
    }
    std::cout << "No student found, please try another ID\n";
    return 0;
}

void display_statistics(){
    read.open("records.txt");
    std::cout << '\n';
    
    std::string line;
    
    //Remove header
    std::getline(read,line);
    
    //Statistic variables
    int numStudents {0};
    float avgScore {0.0};
    int lowestScore {100};
    int highestScore {0};
    std::string lowestStudent;
    std::string highestStudent;

    while (std::getline(read, line)){
        numStudents++;

        std::stringstream ss(line);
        std::string dataField;
        std::vector<std::string> studentData;

        //Read through the line and seperate fields
        while (std::getline(ss, dataField, ',')){
            studentData.push_back(dataField);
        }

        //Check for lowest score
        if (std::stoi(studentData[6]) < lowestScore){
            lowestScore = std::stoi(studentData[6]);
            lowestStudent = studentData[2] + ' ' + studentData[1];
        }
        
        //Check for highest score
        if (std::stoi(studentData[6]) > highestScore){
            highestScore = std::stoi(studentData[6]);
            highestStudent = studentData[2] + ' ' + studentData[1];
        }
        avgScore += std::stof(studentData[6]);

        //Cleanup for next line
        studentData.clear();
    }
    read.close();

    if (numStudents == 0){
        std::cout << "No records to provide statistics, please add students\n";
        return;
    }
    avgScore /= numStudents;
    std::cout << "No. Students:\t" << numStudents << '\n';
    std::cout << "Average Score:\t" << avgScore << "%\n";
    std::cout << "Highest Score:\t" << highestScore << "%\t(" << highestStudent << ")\n";
    std::cout << "Lowest Score:\t" << lowestScore << "%\t(" << lowestStudent << ")\n";
}