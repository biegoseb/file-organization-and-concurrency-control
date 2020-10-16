#ifndef ANIMAL_RECORD_HPP
#define ANIMAL_RECORD_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"    
#define GREEN   "\033[32m"

struct AnimalRecord {
    char country_area[30];
    char year[4];
    long long int comm_code;
    char commodity[50];
    char flow[6];
    long long int trade_usd;
    long long int weight_kg;
    char quantity_name[15];
    long long int quantity;
    char category[50];

    int pos;
    char page;
    int next;
    int next_del;

    AnimalRecord();
    AnimalRecord(char[], char[], long long int, char[], char[], long long int, 
            long long int, char[], long long int, char[]);
    AnimalRecord(string, string, long long int, string, string, long long int, 
            long long int, string, long long int, string);
    void print_headers();
    void print_info(int, char);
};

AnimalRecord::AnimalRecord() { }
AnimalRecord::AnimalRecord(char country_area[30], char year[4], long long int comm_code, 
    char commodity[50], char flow[6], long long int trade_usd, 
    long long int weight_kg, char quantity_name[15], 
    long long int quantity, char category[50]) {
        strcpy(this->country_area, country_area);
        strcpy(this->year, year);
        this->comm_code = comm_code;
        strcpy(this->commodity, commodity);
        strcpy(this->flow, flow);
        this->trade_usd = trade_usd;
        this->weight_kg = weight_kg;
        strcpy(this->quantity_name, quantity_name);
        this->quantity = quantity;
        strcpy(this->category, category);
        next_del = 0;
    }

AnimalRecord::AnimalRecord(string country_area, string year, long long int comm_code, 
    string commodity, string flow, long long int trade_usd, 
        long long int weight_kg, string quantity_name, 
        long long int quantity, string category) {
            strcpy(this->country_area, country_area.c_str());
            strcpy(this->year, year.c_str());
            this->comm_code = comm_code;
            strcpy(this->commodity, commodity.c_str());
            strcpy(this->flow, flow.c_str());
            this->trade_usd = trade_usd;
            this->weight_kg = weight_kg;
            strcpy(this->quantity_name, quantity_name.c_str());
            this->quantity = quantity;
            strcpy(this->category, category.c_str());
            next_del = 0;
        }


void AnimalRecord::print_headers() {
    cout << GREEN <<"i\tCOUNTRY\t\tYEAR";
    cout << GREEN << "\tFLOW\tTRADE_USD\tWEIGHT_KG\tQUANTITY_NAME\t";
    cout << GREEN << "\tQUANTITY\tNEXT\tNEXTDEL" << RESET << endl;
}

void AnimalRecord::print_info(int count, char page) {
    cout << count << page << "\t"
         << left << setw(15) << country_area << "\t"
         << left << setw(4) << year << "\t"
         << left << setw(7) << comm_code << "\t"
         //<< left << setw(50) << commodity << " \t"
         //<< left << setw(8) << flow << "\t"   
         << left << setw(10) << trade_usd << "\t"
         << left << setw(10) << weight_kg << "\t"
         << left << setw(16) << quantity_name << "\t"
         << left << setw(10) << quantity << "\t"
         //<< left << setw(15) << category << "\t"
         << next << page << "\t"
         << next_del << page << endl;
}

#endif // ANIMAL_RECORD_HPP