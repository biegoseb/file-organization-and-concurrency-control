#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <sstream>
#include <algorithm>
#include "../sequential-file/animal-record.hpp"

using std::string;
using std::vector;
using std::function;
using std::fstream;
using std::stringstream;
using std::stoll;
using std::ios;

class Parser {
    vector<AnimalRecord>* animal_records;
    //
    AnimalRecord* create_animal_record(const string& info);
public:
    Parser(const string& file_name);
    ~Parser();
    vector<AnimalRecord>* get_animal_records() const;
    //
    
};

AnimalRecord* Parser::create_animal_record(const string& info) {
    vector<string> fields;
    stringstream ss(info);
    string field;
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    AnimalRecord* animal_record;
    if (fields.size() == 10) {
        string country_area = fields[0];
        string year = fields[1];
        long long int comm_code = stoll(fields[2]);
        string commodity = fields[3];
        string flow = fields[4];
        long long int trade_usd = stoll(fields[5]);
        long long int weight_kg = stoll(fields[6]);
        string quantity_name = fields[7];
        long long int quantity = stoll(fields[8]);
        string category = fields[9];
        
        animal_record = new AnimalRecord(country_area, year, comm_code, 
                                commodity, flow, trade_usd, weight_kg, 
                                quantity_name, quantity, category);
    }
    return animal_record;
}

Parser::Parser(const string& file_name) { 
    animal_records = new vector<AnimalRecord>();

    fstream* file = new fstream(file_name, ios::in);
    string line;
    getline(*file, line);
    if (file){
        while (getline(*file, line)){
            AnimalRecord* rec_temp = create_animal_record(line);
            animal_records->push_back(*rec_temp);
        }
        file->close();
    }
    delete file;
}

Parser::~Parser() {
    delete animal_records;
    //
}

vector<AnimalRecord>* Parser::get_animal_records() const {
    return animal_records;
}

#endif // PARSER_HPP