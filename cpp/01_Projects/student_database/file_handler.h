#ifndef FILE_HANDLER
#define FILE_HANDLER
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

int check_ID();

void create_record_file();

void add_record(std::string line, int ID);

void view_records();

void update_record();

void delete_record();

int search_by_name();

int search_by_ID();

void display_statistics();

#endif